#ifndef __BAT_H
#define __BAT_H

#include "ch32v30x.h"

#define BAT_ADC_CHANNEL     ADC_Channel_10
#define BAT_ADC_GPIO        GPIOC
#define BAT_ADC_PIN         GPIO_Pin_0

#define VOLTAGE_DIV_RATIO   2.0f
#define ADC_VREF            3.3f
#define ADC_RESOLUTION      4096

#define BAT_VREFINT_MV      1200.0f

#define BAT_SAMPLE_COUNT       16u
#define BAT_VREF_SAMPLE_COUNT  8u
#define BAT_ADC_TIMEOUT        0x10000u

#define BAT_SOC_EMA_ALPHA          0.15f
#define BAT_SOC_DOWN_HYSTERESIS    1.0f
#define BAT_SOC_UP_HYSTERESIS      2.0f

#define BAT_VOLTAGE_FULL    4.2f
#define BAT_VOLTAGE_EMPTY   3.0f

void BAT_ADC_Init(void);
uint16_t BAT_GetRawValue(void);
float BAT_GetVoltage(void);
uint8_t BAT_GetPercentage(void);
float BAT_GetCachedVoltage(void);

#endif
