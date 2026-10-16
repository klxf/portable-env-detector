#include "aht20.h"
#include "I2C1_Bus/i2c1_soft.h"
#include "ch32v30x.h"

#define AHT20_ADDR  0x38

uint8_t AHT20_Soft_Init(void)
{
    uint8_t cmd[3];
    uint8_t status;
    uint16_t timeout;

    /* 上电等待 >40ms */
    Delay_Ms(50);

    /* 软复位 0xBA */
    cmd[0] = 0xBA;
    I2C1_Soft_Write(AHT20_ADDR, cmd, 1);
    Delay_Ms(20);

    /* 初始化命令：0xBE 0x08 0x00 */
    cmd[0] = 0xBE;
    cmd[1] = 0x08;
    cmd[2] = 0x00;
    if(I2C1_Soft_Write(AHT20_ADDR, cmd, 3) != 0) return 1;

    /* 等待校准完成（状态寄存器 bit3=1） */
    timeout = 100;
    while(timeout--) {
        Delay_Ms(10);
        if(I2C1_Soft_Read(AHT20_ADDR, &status, 1) != 0) continue;
        if((status & 0x08) != 0) break;
    }
    if(timeout == 0) return 2;

    return 0;
}

uint8_t AHT20_Soft_Read(float *temperature, float *humidity)
{
    uint8_t cmd[3];
    uint8_t data[6];
    uint16_t timeout;
    uint32_t raw_hum, raw_temp;

    /* 触发测量：0xAC 0x33 0x00 */
    cmd[0] = 0xAC;
    cmd[1] = 0x33;
    cmd[2] = 0x00;
    if(I2C1_Soft_Write(AHT20_ADDR, cmd, 3) != 0) return 1;

    /* 等待测量完成（状态寄存器 bit7=0） */
    timeout = 100;
    while(timeout--) {
        Delay_Ms(10);
        if(I2C1_Soft_Read(AHT20_ADDR, data, 1) != 0) continue;
        if((data[0] & 0x80) == 0) break;
    }
    if(timeout == 0) return 2;

    /* 读取 6 字节结果 */
    if(I2C1_Soft_Read(AHT20_ADDR, data, 6) != 0) return 3;

    /* 解析：20bit 湿度 + 20bit 温度 */
    raw_hum  = ((uint32_t)data[1] << 12) | ((uint32_t)data[2] << 4) | (data[3] >> 4);
    raw_temp = (((uint32_t)(data[3] & 0x0F)) << 16) | ((uint32_t)data[4] << 8) | data[5];

    *humidity    = (float)raw_hum  * 100.0f / 1048576.0f;
    *temperature = (float)raw_temp * 200.0f / 1048576.0f - 50.0f;

    return 0;
}