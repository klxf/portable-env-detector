#ifndef __SENSOR_DATA_H
#define __SENSOR_DATA_H

#include <stdint.h>

typedef struct {
    /* AHT20 */
    float    aht20_temp;        /* C */
    float    aht20_hum;         /* %RH */
    uint8_t  aht20_valid;

    /* BMP280 */
    float    bmp280_temp;       /* °„C */
    float    bmp280_press;      /* hPa */
    uint8_t  bmp280_valid;

    /* JED1xx */
    uint16_t jed104_co;         /* CO ppm */
    uint16_t jed105_nh3;        /* NH3 ppm */
    uint16_t jed116_hcho;       /* HCHO ppm */
    uint8_t  jed104_valid;
    uint8_t  jed105_valid;
    uint8_t  jed116_valid;

    /* SGP41 */
    int32_t  sgp41_voc_sraw;
    int32_t  sgp41_voc_index;
    int32_t  sgp41_nox_sraw;
    int32_t  sgp41_nox_index;
    uint8_t  sgp41_valid;

} Sensor_Pack_t;

extern volatile Sensor_Pack_t g_sensor_pack;
extern volatile uint8_t g_sensor_collect_flag;
extern volatile uint8_t g_sensor_ui_update_flag;

void Sensor_Fusion_Init(void);
void Sensor_Collect_All(void);

#endif
