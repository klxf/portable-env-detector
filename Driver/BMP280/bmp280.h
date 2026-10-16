#ifndef __BMP280_H
#define __BMP280_H

#include <stdint.h>

#ifndef BMP280_ADDR
#define BMP280_ADDR  0x76
#endif

uint8_t BMP280_Init(void);
uint8_t BMP280_Read(float *temperature, float *pressure);

#endif
