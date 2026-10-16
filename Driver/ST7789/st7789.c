#include "st7789.h"

static void ST7789_GPIO_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOC, ENABLE);

    /* PA5:SCK, PA7:MOSI -> 复用推挽 */
    GPIO_InitStructure.GPIO_Pin   = ST7789_SCK_PIN | ST7789_MOSI_PIN;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    /* PA4:CS -> 普通推挽输出（关键修复！） */
    GPIO_InitStructure.GPIO_Pin   = ST7789_CS_PIN;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    /* PC4:DC, PC5:RST -> 推挽输出 */
    GPIO_InitStructure.GPIO_Pin   = ST7789_DC_PIN | ST7789_RST_PIN;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;
    GPIO_Init(GPIOC, &GPIO_InitStructure);

    ST7789_CS_HIGH();
    ST7789_DC_DATA();
    ST7789_RST_HIGH();
}

static void ST7789_SPI_Init(void)
{
    SPI_InitTypeDef SPI_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);

    SPI_InitStructure.SPI_Direction         = SPI_Direction_2Lines_FullDuplex;
    SPI_InitStructure.SPI_Mode              = SPI_Mode_Master;
    SPI_InitStructure.SPI_DataSize          = SPI_DataSize_8b;
    SPI_InitStructure.SPI_CPOL              = SPI_CPOL_Low;
    SPI_InitStructure.SPI_CPHA              = SPI_CPHA_1Edge;
    SPI_InitStructure.SPI_NSS               = SPI_NSS_Soft;
    SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_2;
    SPI_InitStructure.SPI_FirstBit          = SPI_FirstBit_MSB;
    SPI_InitStructure.SPI_CRCPolynomial     = 7;
    SPI_Init(SPI1, &SPI_InitStructure);

    SPI_Cmd(SPI1, ENABLE);
}

static void ST7789_Reset(void)
{
    ST7789_RST_HIGH();
    Delay_Ms(10);
    ST7789_RST_LOW();
    Delay_Ms(10);
    ST7789_RST_HIGH();
    Delay_Ms(120);          /* ST7789 要求复位后等待 >120ms */
}

void ST7789_SPI_SendByte(uint8_t byte)
{
    uint16_t timeout = 0xFFFF;

    while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET) {
        if(--timeout == 0) return;
    }
    SPI_I2S_SendData(SPI1, byte);

    timeout = 0xFFFF;
    while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == RESET) {
        if(--timeout == 0) return;
    }
    (void)SPI_I2S_ReceiveData(SPI1);
}

void ST7789_WriteCommand(uint8_t cmd)
{
    ST7789_DC_CMD();
    ST7789_CS_LOW();
    ST7789_SPI_SendByte(cmd);
    ST7789_CS_HIGH();
}

void ST7789_WriteData(uint8_t data)
{
    ST7789_DC_DATA();
    ST7789_CS_LOW();
    ST7789_SPI_SendByte(data);
    ST7789_CS_HIGH();
}

void ST7789_SetWindow(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2)
{
    /* CASET: Column Address Set */
    ST7789_WriteCommand(0x2A);
    ST7789_WriteData(x1 >> 8);
    ST7789_WriteData(x1 & 0xFF);
    ST7789_WriteData(x2 >> 8);
    ST7789_WriteData(x2 & 0xFF);

    /* RASET: Row Address Set */
    ST7789_WriteCommand(0x2B);
    ST7789_WriteData(y1 >> 8);
    ST7789_WriteData(y1 & 0xFF);
    ST7789_WriteData(y2 >> 8);
    ST7789_WriteData(y2 & 0xFF);

    /* RAMWR: Memory Write */
    ST7789_WriteCommand(0x2C);
}

void ST7789_Fill(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color)
{
    ST7789_SetWindow(x1, y1, x2, y2);

    uint8_t high  = color >> 8;
    uint8_t low   = color & 0xFF;
    uint32_t cnt  = (uint32_t)(x2 - x1 + 1) * (y2 - y1 + 1);

    ST7789_DC_DATA();
    ST7789_CS_LOW();
    for(uint32_t i = 0; i < cnt; i++) {
        ST7789_SPI_SendByte(high);
        ST7789_SPI_SendByte(low);
    }
    ST7789_CS_HIGH();
}

void ST7789_Init(void)
{
    ST7789_GPIO_Init();
    ST7789_SPI_Init();
    ST7789_Reset();

    /* ---- 初始化序列 ---- */
    ST7789_WriteCommand(0x11);      /* Sleep Out */
    Delay_Ms(120);

    ST7789_WriteCommand(0x36);      /* MADCTL */
    // ST7789_WriteData(0x00);         /* 正常方向，RGB */
    ST7789_WriteData(0xC0);         /* MY=1, MX=1, 180° 硬件旋转 */

    ST7789_WriteCommand(0x3A);      /* COLMOD */
    ST7789_WriteData(0x55);         /* 16 bit/pixel */

    ST7789_WriteCommand(0xB2);      /* Porch Setting */
    ST7789_WriteData(0x0C);
    ST7789_WriteData(0x0C);
    ST7789_WriteData(0x00);
    ST7789_WriteData(0x33);
    ST7789_WriteData(0x33);

    ST7789_WriteCommand(0xB7);      /* Gate Control */
    ST7789_WriteData(0x35);

    ST7789_WriteCommand(0xBB);      /* VCOMS */
    ST7789_WriteData(0x19);

    ST7789_WriteCommand(0xC0);      /* LCM Control */
    ST7789_WriteData(0x2C);

    ST7789_WriteCommand(0xC2);      /* VDV VRH Enable */
    ST7789_WriteData(0x01);

    ST7789_WriteCommand(0xC3);      /* VRH Set */
    ST7789_WriteData(0x12);

    ST7789_WriteCommand(0xC4);      /* VDV Set */
    ST7789_WriteData(0x20);

    ST7789_WriteCommand(0xC6);      /* Frame Rate */
    ST7789_WriteData(0x0F);

    ST7789_WriteCommand(0xD0);      /* Power Control */
    ST7789_WriteData(0xA4);
    ST7789_WriteData(0xA1);

    /* Positive Gamma */
    ST7789_WriteCommand(0xE0);
    ST7789_WriteData(0xD0);
    ST7789_WriteData(0x04);
    ST7789_WriteData(0x0D);
    ST7789_WriteData(0x11);
    ST7789_WriteData(0x13);
    ST7789_WriteData(0x2B);
    ST7789_WriteData(0x3F);
    ST7789_WriteData(0x54);
    ST7789_WriteData(0x4C);
    ST7789_WriteData(0x18);
    ST7789_WriteData(0x0D);
    ST7789_WriteData(0x0B);
    ST7789_WriteData(0x1F);
    ST7789_WriteData(0x23);

    /* Negative Gamma */
    ST7789_WriteCommand(0xE1);
    ST7789_WriteData(0xD0);
    ST7789_WriteData(0x04);
    ST7789_WriteData(0x0C);
    ST7789_WriteData(0x11);
    ST7789_WriteData(0x13);
    ST7789_WriteData(0x2C);
    ST7789_WriteData(0x3F);
    ST7789_WriteData(0x44);
    ST7789_WriteData(0x51);
    ST7789_WriteData(0x2F);
    ST7789_WriteData(0x1F);
    ST7789_WriteData(0x1F);
    ST7789_WriteData(0x20);
    ST7789_WriteData(0x23);

    ST7789_WriteCommand(0x21);      /* Display Inversion On */
    Delay_Ms(10);

    ST7789_WriteCommand(0x29);      /* Display On */
    Delay_Ms(120);
}

/**
 * @brief 设置写入窗口并发送 RAMWR，CS 全程保持低，等待 DMA 数据
 */
void ST7789_PrepareDMAWrite(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2)
{
    ST7789_CS_LOW();

    /* CASET */
    ST7789_DC_CMD();
    ST7789_SPI_SendByte(0x2A);
    ST7789_DC_DATA();
    ST7789_SPI_SendByte(x1 >> 8);
    ST7789_SPI_SendByte(x1 & 0xFF);
    ST7789_SPI_SendByte(x2 >> 8);
    ST7789_SPI_SendByte(x2 & 0xFF);

    /* RASET */
    ST7789_DC_CMD();
    ST7789_SPI_SendByte(0x2B);
    ST7789_DC_DATA();
    ST7789_SPI_SendByte(y1 >> 8);
    ST7789_SPI_SendByte(y1 & 0xFF);
    ST7789_SPI_SendByte(y2 >> 8);
    ST7789_SPI_SendByte(y2 & 0xFF);

    /* RAMWR：命令后 DC=DATA，CS 保持低 */
    ST7789_DC_CMD();
    ST7789_SPI_SendByte(0x2C);
    ST7789_DC_DATA();
}

/* ==================== 背光 PWM 控制 ==================== */
/**
 * @brief 初始化 TIM2_CH4 (PA3) PWM，频率约 20kHz（无频闪）
 * @note  基于系统主频 144MHz。若主频不同，请自行调整 ARR。
 */
void ST7789_Backlight_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
    TIM_OCInitTypeDef TIM_OCInitStructure;

    /* 使能时钟 */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

    /* PA3 复用为 TIM2_CH4 推挽输出 */
    GPIO_InitStructure.GPIO_Pin   = ST7789_BL_PIN;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(ST7789_BL_PORT, &GPIO_InitStructure);

    /* TIM2 时基：144MHz / 7200 = 20kHz */
    TIM_TimeBaseStructure.TIM_Period        = 7199;
    TIM_TimeBaseStructure.TIM_Prescaler     = 0;
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseStructure.TIM_CounterMode   = TIM_CounterMode_Up;
    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);

    /* PWM1 模式，高电平有效（对应 N-MOS 高电平导通） */
    TIM_OCInitStructure.TIM_OCMode       = TIM_OCMode_PWM1;
    TIM_OCInitStructure.TIM_OutputState  = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_Pulse        = 7200;          /* 默认 100% 亮度 */
    TIM_OCInitStructure.TIM_OCPolarity   = TIM_OCPolarity_High;
    TIM_OC4Init(TIM2, &TIM_OCInitStructure);

    TIM_OC4PreloadConfig(TIM2, TIM_OCPreload_Enable);
    TIM_ARRPreloadConfig(TIM2, ENABLE);
    TIM_Cmd(TIM2, ENABLE);
}

/**
 * @brief 设置背光亮度
 * @param brightness 0~100
 */
void ST7789_Backlight_Set(uint8_t brightness)
{
    if(brightness > 100) brightness = 100;
    uint16_t pulse = (uint16_t)(((uint32_t)brightness * 7200) / 100);
    TIM_SetCompare4(TIM2, pulse);
}

void ST7789_Backlight_On(void)
{
    ST7789_Backlight_Set(100);
}

void ST7789_Backlight_Off(void)
{
    ST7789_Backlight_Set(0);
}
