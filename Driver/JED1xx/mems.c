#include "JED1xx/jed1xx.h"
#include "I2C1_Bus/i2c1_soft.h"

#define JED1XX_CMD_READ       0xA1u
#define JED1XX_CMD_ZERO_CAL   0x32u

static uint8_t JED1xx_Addr7(uint8_t devAddr_8bit)
{
    return (uint8_t)(devAddr_8bit >> 1);
}

uint8_t JED1xx_Read(uint8_t devAddr_8bit, uint16_t *concentration)
{
    uint8_t addr7;
    uint8_t value_high;
    uint8_t value_low;

    if(concentration == 0) {
        return 1;
    }

    *concentration = 0;
    addr7 = JED1xx_Addr7(devAddr_8bit);

    I2C1_Soft_Start();
    I2C1_Soft_SendByte((uint8_t)(addr7 << 1));
    if(I2C1_Soft_WaitAck() != 0) {
        I2C1_Soft_Stop();
        return 2;
    }

    I2C1_Soft_SendByte(JED1XX_CMD_READ);
    if(I2C1_Soft_WaitAck() != 0) {
        I2C1_Soft_Stop();
        return 3;
    }

    I2C1_Soft_Start();
    I2C1_Soft_SendByte((uint8_t)((addr7 << 1) | 0x01u));
    if(I2C1_Soft_WaitAck() != 0) {
        I2C1_Soft_Stop();
        return 4;
    }

    value_high = I2C1_Soft_ReadByte(0);
    value_low  = I2C1_Soft_ReadByte(1);
    I2C1_Soft_Stop();

    *concentration = (uint16_t)(((uint16_t)value_high << 8) | value_low);
    return 0;
}

uint8_t JED1xx_ZeroCal(uint8_t devAddr_8bit, uint16_t zeroValue)
{
    uint8_t payload[3];

    payload[0] = JED1XX_CMD_ZERO_CAL;
    payload[1] = (uint8_t)(zeroValue >> 8);
    payload[2] = (uint8_t)zeroValue;

    return I2C1_Soft_Write(JED1xx_Addr7(devAddr_8bit), payload, 3);
}
