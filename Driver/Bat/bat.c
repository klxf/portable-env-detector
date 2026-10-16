#include "bat.h"

typedef struct {
    float voltage;
    float percent;
} BatSocPoint;

static const BatSocPoint BAT_SOC_CURVE[] = {
    { 4.20f, 100.0f },
    { 4.08f,  85.0f },
    { 3.99f,  60.0f },
    { 3.92f,  40.0f },
    { 3.84f,  25.0f },
    { 3.74f,  12.0f },
    { 3.65f,   5.0f },
    { 3.55f,   1.0f },
    { 3.30f,   0.0f }
};

static float filtered_soc = -1.0f;
static uint8_t reported_soc = 0xFFu;
static float cached_voltage = 0.0f;
static uint8_t voltage_cached = 0u;

float BAT_GetCachedVoltage(void)
{
    return cached_voltage;
}

static uint16_t BAT_ReadChannel(uint8_t channel)
{
    uint32_t timeout = BAT_ADC_TIMEOUT;

    ADC_ClearFlag(ADC1, ADC_FLAG_EOC);
    ADC_RegularChannelConfig(ADC1, channel, 1, ADC_SampleTime_239Cycles5);
    ADC_SoftwareStartConvCmd(ADC1, ENABLE);

    while(ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) == RESET) {
        if(--timeout == 0) return 0;
    }

    return ADC_GetConversionValue(ADC1);
}

static float BAT_FilterChannel(uint8_t channel, uint8_t count)
{
    uint16_t samples[32];
    uint8_t used = 0;
    uint8_t start;
    uint8_t end;
    uint32_t sum = 0;

    if(count > sizeof(samples) / sizeof(samples[0])) {
        count = sizeof(samples) / sizeof(samples[0]);
    }

    for(uint8_t i = 0; i < count; i++) {
        uint16_t raw = BAT_ReadChannel(channel);

        if(raw != 0) {
            samples[used++] = raw;
        }
    }

    if(used == 0) return 0.0f;

    for(uint8_t i = 1; i < used; i++) {
        uint16_t value = samples[i];
        uint8_t j = i;

        while(j > 0 && samples[j - 1] > value) {
            samples[j] = samples[j - 1];
            j--;
        }
        samples[j] = value;
    }

    start = used / 4;
    end = used - start;
    for(uint8_t i = start; i < end; i++) {
        sum += samples[i];
    }

    return (float)sum / (float)(end - start);
}

static float BAT_GetVdda(void)
{
    float vref_raw = BAT_FilterChannel(ADC_Channel_Vrefint, BAT_VREF_SAMPLE_COUNT);

    if(vref_raw <= 1.0f) {
        return ADC_VREF;
    }

    return (BAT_VREFINT_MV * ADC_RESOLUTION) / (vref_raw * 1000.0f);
}

static float BAT_VoltageToSoc(float voltage)
{
    const uint8_t point_count = sizeof(BAT_SOC_CURVE) / sizeof(BAT_SOC_CURVE[0]);

    if(voltage >= BAT_SOC_CURVE[0].voltage) {
        return 100.0f;
    }

    for(uint8_t i = 0; i < (point_count - 1); i++) {
        float high_voltage = BAT_SOC_CURVE[i].voltage;
        float low_voltage = BAT_SOC_CURVE[i + 1].voltage;

        if(voltage <= high_voltage && voltage >= low_voltage) {
            float ratio = (voltage - low_voltage) / (high_voltage - low_voltage);

            return BAT_SOC_CURVE[i + 1].percent +
                   ratio * (BAT_SOC_CURVE[i].percent - BAT_SOC_CURVE[i + 1].percent);
        }
    }

    return 0.0f;
}

void BAT_ADC_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    ADC_InitTypeDef ADC_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC | RCC_APB2Periph_ADC1, ENABLE);

    GPIO_InitStructure.GPIO_Pin = BAT_ADC_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
    GPIO_Init(BAT_ADC_GPIO, &GPIO_InitStructure);

    RCC_ADCCLKConfig(RCC_PCLK2_Div8);

    ADC_StructInit(&ADC_InitStructure);

    ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
    ADC_InitStructure.ADC_ScanConvMode = DISABLE;
    ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;
    ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
    ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
    ADC_InitStructure.ADC_NbrOfChannel = 1;
    ADC_InitStructure.ADC_OutputBuffer = ADC_OutputBuffer_Enable;
    ADC_InitStructure.ADC_Pga = ADC_Pga_1;
    ADC_Init(ADC1, &ADC_InitStructure);

    ADC_Cmd(ADC1, ENABLE);
    ADC_TempSensorVrefintCmd(ENABLE);

    ADC_ResetCalibration(ADC1);
    while(ADC_GetResetCalibrationStatus(ADC1));
    ADC_StartCalibration(ADC1);
    while(ADC_GetCalibrationStatus(ADC1));
}

uint16_t BAT_GetRawValue(void)
{
    return (uint16_t)(BAT_FilterChannel(BAT_ADC_CHANNEL, BAT_SAMPLE_COUNT) + 0.5f);
}

float BAT_GetVoltage(void)
{
    float raw = BAT_FilterChannel(BAT_ADC_CHANNEL, BAT_SAMPLE_COUNT);
    float vdda = BAT_GetVdda();
    float v_adc;

    if(vdda < 2.8f || vdda > 3.6f) {
        vdda = ADC_VREF;
    }

    v_adc = raw * vdda / ADC_RESOLUTION;

    cached_voltage = v_adc * VOLTAGE_DIV_RATIO;
    voltage_cached = 1u;

    return cached_voltage;
}

uint8_t BAT_GetPercentage(void)
{
    float v_bat;
    uint8_t use_cached_voltage = voltage_cached;

    voltage_cached = 0u;

    if(use_cached_voltage != 0u) {
        v_bat = cached_voltage;
    } else {
        v_bat = BAT_GetVoltage();
    }

    float target_soc = BAT_VoltageToSoc(v_bat);
    uint8_t target_percentage;

    if(filtered_soc < 0.0f) {
        filtered_soc = target_soc;
    } else {
        filtered_soc += BAT_SOC_EMA_ALPHA * (target_soc - filtered_soc);
    }

    if(filtered_soc > 100.0f) filtered_soc = 100.0f;
    if(filtered_soc < 0.0f) filtered_soc = 0.0f;

    target_percentage = (uint8_t)(filtered_soc + 0.5f);

    if(reported_soc == 0xFFu) {
        reported_soc = target_percentage;
    } else if(target_percentage < reported_soc &&
              (reported_soc - target_percentage) >= BAT_SOC_DOWN_HYSTERESIS) {
        reported_soc = target_percentage;
    } else if(target_percentage > reported_soc &&
              (target_percentage - reported_soc) >= BAT_SOC_UP_HYSTERESIS) {
        reported_soc = target_percentage;
    }

    return reported_soc;
}
