#include "i2c1_soft.h"

#define SCL_H()  GPIO_SetBits(GPIOB, GPIO_Pin_6)
#define SCL_L()  GPIO_ResetBits(GPIOB, GPIO_Pin_6)
#define SDA_H()  GPIO_SetBits(GPIOB, GPIO_Pin_7)
#define SDA_L()  GPIO_ResetBits(GPIOB, GPIO_Pin_7)
#define SDA_IN() (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_7))

static void I2C_Delay(void)
{
    for(volatile uint32_t i = 0; i < 960; i++) {
        __NOP();
    }
}

void I2C1_Soft_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

    /* PB6=SCL, PB7=SDA£¬¿ªÂ©Êä³ö */
    GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_6 | GPIO_Pin_7;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_OD;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    SCL_H();
    SDA_H();
}

void I2C1_Soft_Start(void)
{
    SDA_H(); I2C_Delay();
    SCL_H(); I2C_Delay();
    SDA_L(); I2C_Delay();
    SCL_L(); I2C_Delay();
}

void I2C1_Soft_Stop(void)
{
    SDA_L(); I2C_Delay();
    SCL_H(); I2C_Delay();
    SDA_H(); I2C_Delay();
}

uint8_t I2C1_Soft_WaitAck(void)
{
    uint8_t ack = 0;
    uint16_t timeout = 2000;

    SDA_H();
    I2C_Delay();
    SCL_H();
    I2C_Delay();

    while(SDA_IN()) {
        if(--timeout == 0) {
            ack = 1;
            break;
        }
    }

    SCL_L();
    I2C_Delay();
    return ack;
}

void I2C1_Soft_SendByte(uint8_t byte)
{
    for(uint8_t i = 0; i < 8; i++) {
        if(byte & 0x80) SDA_H();
        else            SDA_L();
        byte <<= 1;
        I2C_Delay();
        SCL_H(); I2C_Delay(); SCL_L(); I2C_Delay();
    }
}

uint8_t I2C1_Soft_ReadByte(uint8_t ack)
{
    uint8_t byte = 0;

    SDA_H();
    for(uint8_t i = 0; i < 8; i++) {
        byte <<= 1;
        SCL_H(); I2C_Delay();
        if(SDA_IN()) byte |= 0x01;
        SCL_L(); I2C_Delay();
    }

    if(ack) SDA_H();
    else    SDA_L();
    I2C_Delay();
    SCL_H(); I2C_Delay(); SCL_L(); I2C_Delay();
    SDA_H();

    return byte;
}

uint8_t I2C1_Soft_Write(uint8_t devAddr7bit, uint8_t *data, uint8_t len)
{
    uint8_t addr8bit = (devAddr7bit << 1) | 0x00;

    I2C1_Soft_Start();
    I2C1_Soft_SendByte(addr8bit);
    if(I2C1_Soft_WaitAck() != 0) {
        I2C1_Soft_Stop();
        return 1;
    }

    for(uint8_t i = 0; i < len; i++) {
        I2C1_Soft_SendByte(data[i]);
        if(I2C1_Soft_WaitAck() != 0) {
            I2C1_Soft_Stop();
            return 2;
        }
    }

    I2C1_Soft_Stop();
    return 0;
}

uint8_t I2C1_Soft_Read(uint8_t devAddr7bit, uint8_t *buf, uint8_t len)
{
    uint8_t addr8bit = (devAddr7bit << 1) | 0x01;

    I2C1_Soft_Start();
    I2C1_Soft_SendByte(addr8bit);
    if(I2C1_Soft_WaitAck() != 0) {
        I2C1_Soft_Stop();
        return 1;
    }

    for(uint8_t i = 0; i < len; i++) {
        buf[i] = I2C1_Soft_ReadByte((i == len - 1) ? 1 : 0);
    }

    I2C1_Soft_Stop();
    return 0;
}

uint8_t I2C1_Soft_Scan(uint8_t addr7bit)
{
    uint8_t addr8bit = (addr7bit << 1) | 0x00;
    uint8_t ack;

    I2C1_Soft_Start();
    I2C1_Soft_SendByte(addr8bit);
    ack = I2C1_Soft_WaitAck();
    I2C1_Soft_Stop();

    return ack;
}