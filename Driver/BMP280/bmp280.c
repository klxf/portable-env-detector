#include "bmp280.h"
#include "I2C1_Bus/i2c1_soft.h"
#include "ch32v30x.h"
#include <stdio.h>

#define BMP280_ADDR  0x76

/* 校准参数 */
static uint16_t dig_T1;
static int16_t  dig_T2, dig_T3;
static uint16_t dig_P1;
static int16_t  dig_P2, dig_P3, dig_P4, dig_P5, dig_P6, dig_P7, dig_P8, dig_P9;
static int32_t  t_fine;

/* 内部 I2C 复合时序 */
static uint8_t bmp280_read_regs(uint8_t reg, uint8_t *buf, uint8_t len)
{
    uint8_t addr_w = (BMP280_ADDR << 1);
    uint8_t addr_r = (BMP280_ADDR << 1) | 0x01;

    I2C1_Soft_Start();
    I2C1_Soft_SendByte(addr_w);
    if(I2C1_Soft_WaitAck() != 0) { I2C1_Soft_Stop(); return 1; }
    I2C1_Soft_SendByte(reg);
    if(I2C1_Soft_WaitAck() != 0) { I2C1_Soft_Stop(); return 2; }

    I2C1_Soft_Start();
    I2C1_Soft_SendByte(addr_r);
    if(I2C1_Soft_WaitAck() != 0) { I2C1_Soft_Stop(); return 3; }

    for(uint8_t i = 0; i < len; i++) {
        buf[i] = I2C1_Soft_ReadByte((i == len - 1) ? 1 : 0);
    }

    I2C1_Soft_Stop();
    return 0;
}

static uint8_t bmp280_write_reg(uint8_t reg, uint8_t val)
{
    uint8_t data[2] = {reg, val};
    return I2C1_Soft_Write(BMP280_ADDR, data, 2);
}

static int32_t bmp280_compensate_T_int32(int32_t adc_T)
{
    int32_t var1, var2, T;
    var1 = ((((adc_T >> 3) - ((int32_t)dig_T1 << 1))) * ((int32_t)dig_T2)) >> 11;
    var2 = (((((adc_T >> 4) - ((int32_t)dig_T1)) *
              ((adc_T >> 4) - ((int32_t)dig_T1))) >> 12) * ((int32_t)dig_T3)) >> 14;
    t_fine = var1 + var2;
    T = (t_fine * 5 + 128) >> 8;
    return T;
}

static uint32_t bmp280_compensate_P_int32(int32_t adc_P)
{
    int32_t var1, var2;
    uint32_t p;

    var1 = (((int32_t)t_fine) >> 1) - (int32_t)64000;
    var2 = (((var1 >> 2) * (var1 >> 2)) >> 11) * ((int32_t)dig_P6);
    var2 = var2 + ((var1 * ((int32_t)dig_P5)) << 1);
    var2 = (var2 >> 2) + (((int32_t)dig_P4) << 16);
    var1 = (((dig_P3 * (((var1 >> 2) * (var1 >> 2)) >> 13)) >> 3) +
            ((((int32_t)dig_P2) * var1) >> 1)) >> 18;
    var1 = ((((32768 + var1)) * ((int32_t)dig_P1)) >> 15);

    if(var1 == 0) return 0;

    p = (((uint32_t)(((int32_t)1048576) - adc_P) - (var2 >> 12))) * 3125;
    if(p < 0x80000000) p = (p << 1) / ((uint32_t)var1);
    else               p = (p / (uint32_t)var1) * 2;

    var1 = (((int32_t)dig_P9) * ((int32_t)(((p >> 3) * (p >> 3)) >> 13))) >> 12;
    var2 = (((int32_t)(p >> 2)) * ((int32_t)dig_P8)) >> 13;
    p = (uint32_t)((int32_t)p + ((var1 + var2 + dig_P7) >> 4));

    return p;
}

uint8_t BMP280_Init(void)
{
    uint8_t id = 0;
    uint8_t calib[24];

    Delay_Ms(10);

    if(bmp280_read_regs(0xD0, &id, 1) != 0) return 1;
    if(id != 0x58) return 2;

    if(bmp280_read_regs(0x88, calib, 24) != 0) return 3;

    dig_T1 = (uint16_t)((calib[1]  << 8) | calib[0]);
    dig_T2 = (int16_t) ((calib[3]  << 8) | calib[2]);
    dig_T3 = (int16_t) ((calib[5]  << 8) | calib[4]);
    dig_P1 = (uint16_t)((calib[7]  << 8) | calib[6]);
    dig_P2 = (int16_t) ((calib[9]  << 8) | calib[8]);
    dig_P3 = (int16_t) ((calib[11] << 8) | calib[10]);
    dig_P4 = (int16_t) ((calib[13] << 8) | calib[12]);
    dig_P5 = (int16_t) ((calib[15] << 8) | calib[14]);
    dig_P6 = (int16_t) ((calib[17] << 8) | calib[16]);
    dig_P7 = (int16_t) ((calib[19] << 8) | calib[18]);
    dig_P8 = (int16_t) ((calib[21] << 8) | calib[20]);
    dig_P9 = (int16_t) ((calib[23] << 8) | calib[22]);

    /* 配置：温度×1 (001), 气压×1 (001), 正常模式 (11) = 0x27 */
    bmp280_write_reg(0xF4, 0x27);
    bmp280_write_reg(0xF5, 0x00);

    return 0;
}

uint8_t BMP280_Read(float *temperature, float *pressure)
{
    uint8_t data[6];
    int32_t adc_P, adc_T;
    int32_t comp_temp;
    uint32_t comp_press;

    if(bmp280_read_regs(0xF7, data, 6) != 0) return 1;

    adc_P = ((int32_t)data[0] << 12) | ((int32_t)data[1] << 4) | ((int32_t)(data[2] >> 4));
    adc_T = ((int32_t)data[3] << 12) | ((int32_t)data[4] << 4) | ((int32_t)(data[5] >> 4));

    comp_temp = bmp280_compensate_T_int32(adc_T);

    comp_press = bmp280_compensate_P_int32(adc_P);

    *temperature = (float)comp_temp / 100.0f;
    *pressure    = (float)comp_press / 100.0f;     /* hPa */

    return 0;
}