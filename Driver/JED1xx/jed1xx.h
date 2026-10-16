#ifndef __JED1XX_H
#define __JED1XX_H

#include <stdint.h>

/* 8-bit I2C write addresses used by the JED1xx family. */
#define JED104_CO_ADDR8    0x58u
#define JED105_NH3_ADDR8   0x54u
#define JED116_HCHO_ADDR8  0x5Cu

uint8_t JED1xx_Read(uint8_t devAddr_8bit, uint16_t *concentration);
uint8_t JED1xx_ZeroCal(uint8_t devAddr_8bit, uint16_t zeroValue);

#endif
