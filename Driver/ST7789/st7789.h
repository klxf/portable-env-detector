#ifndef __ST7789_H
#define __ST7789_H

#include "ch32v30x.h"

#define ST7789_WIDTH    240
#define ST7789_HEIGHT   240
#define ST7789_Y_OFFSET 80

/* 引脚定义 */
#define ST7789_CS_PIN     GPIO_Pin_4
#define ST7789_CS_PORT    GPIOA

#define ST7789_DC_PIN     GPIO_Pin_4
#define ST7789_DC_PORT    GPIOC

#define ST7789_RST_PIN    GPIO_Pin_5
#define ST7789_RST_PORT   GPIOC

#define ST7789_SCK_PIN    GPIO_Pin_5
#define ST7789_SCK_PORT   GPIOA

#define ST7789_MOSI_PIN   GPIO_Pin_7
#define ST7789_MOSI_PORT  GPIOA

#define ST7789_BL_PIN       GPIO_Pin_3
#define ST7789_BL_PORT      GPIOA

/* 快捷宏 */
#define ST7789_CS_LOW()   GPIO_ResetBits(ST7789_CS_PORT, ST7789_CS_PIN)
#define ST7789_CS_HIGH()  GPIO_SetBits(ST7789_CS_PORT, ST7789_CS_PIN)
#define ST7789_DC_CMD()   GPIO_ResetBits(ST7789_DC_PORT, ST7789_DC_PIN)
#define ST7789_DC_DATA()  GPIO_SetBits(ST7789_DC_PORT, ST7789_DC_PIN)
#define ST7789_RST_LOW()  GPIO_ResetBits(ST7789_RST_PORT, ST7789_RST_PIN)
#define ST7789_RST_HIGH() GPIO_SetBits(ST7789_RST_PORT, ST7789_RST_PIN)

/* 常用 RGB565 颜色 */
#define ST7789_BLACK    0x0000
#define ST7789_WHITE    0xFFFF
#define ST7789_RED      0xF800
#define ST7789_GREEN    0x07E0
#define ST7789_BLUE     0x001F
#define ST7789_YELLOW   0xFFE0
#define ST7789_CYAN     0x07FF
#define ST7789_MAGENTA  0xF81F

/* 函数声明 */
void ST7789_Init(void);
void ST7789_Fill(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color);
void ST7789_SetWindow(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2);
void ST7789_WriteCommand(uint8_t cmd);
void ST7789_WriteData(uint8_t data);
void ST7789_SPI_SendByte(uint8_t byte);
void ST7789_PrepareDMAWrite(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2);

void ST7789_Backlight_Init(void);
void ST7789_Backlight_On(void);
void ST7789_Backlight_Off(void);
void ST7789_Backlight_Set(uint8_t brightness);

#endif
