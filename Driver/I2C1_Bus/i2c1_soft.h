#ifndef __I2C1_SOFT_H
#define __I2C1_SOFT_H

#include "ch32v30x.h"

void I2C1_Soft_Init(void);

void    I2C1_Soft_Start(void);
void    I2C1_Soft_Stop(void);
uint8_t I2C1_Soft_WaitAck(void);
void    I2C1_Soft_SendByte(uint8_t byte);
uint8_t I2C1_Soft_ReadByte(uint8_t ack);

uint8_t I2C1_Soft_Write(uint8_t devAddr7bit, uint8_t *data, uint8_t len);
uint8_t I2C1_Soft_Read(uint8_t devAddr7bit, uint8_t *buf, uint8_t len);

uint8_t I2C1_Soft_Scan(uint8_t addr7bit);

#endif