#ifndef __SGP41_H
#define __SGP41_H

#include <stdint.h>

#ifndef SGP41_ADDR
#define SGP41_ADDR  0x59
#endif

uint8_t SGP41_Init(void);
uint8_t SGP41_MeasureRaw(uint16_t *sraw_voc, uint16_t *sraw_nox);
uint8_t SGP41_ExecuteSelfTest(void);
uint8_t SGP41_TurnHeaterOn(void);

void SGP41_Algorithm_Init(void);
void SGP41_ProcessIndex(uint16_t sraw_voc, uint16_t sraw_nox,
                        int32_t *voc_index, int32_t *nox_index,
                        float humidity, float temperature);

#endif