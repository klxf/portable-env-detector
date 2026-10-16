#ifndef __AHT20_SOFT_H
#define __AHT20_SOFT_H

#include <stdint.h>

uint8_t AHT20_Soft_Init(void);
uint8_t AHT20_Soft_Read(float *temperature, float *humidity);

#endif