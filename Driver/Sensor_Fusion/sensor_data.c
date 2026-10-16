#include "sensor_data.h"
#include "I2C1_Bus/i2c1_soft.h"
#include "AHT20/aht20.h"
#include "BMP280/bmp280.h"
#include "SGP41/sgp41.h"
#include "JED1xx/jed1xx.h"
#include "ch32v30x.h"

volatile Sensor_Pack_t g_sensor_pack = {0};
volatile uint8_t g_sensor_collect_flag = 0;
volatile uint8_t g_sensor_ui_update_flag = 0;

static void Sensor_ReadJed1xx(uint8_t addr8, volatile uint16_t *dest, volatile uint8_t *valid)
{
    uint16_t value = 0;

    if(JED1xx_Read(addr8, &value) == 0) {
        *dest = value;
        *valid = 1;
    } else {
        *valid = 0;
    }
}

void Sensor_Fusion_Init(void)
{
    I2C1_Soft_Init();
    AHT20_Soft_Init();
    BMP280_Init();
    SGP41_Init();
    SGP41_Algorithm_Init();
}

void Sensor_Collect_All(void)
{
    /* AHT20 */
    if(AHT20_Soft_Read(&g_sensor_pack.aht20_temp, &g_sensor_pack.aht20_hum) == 0) {
        g_sensor_pack.aht20_valid = 1;
    } else {
        g_sensor_pack.aht20_valid = 0;
    }

    /* BMP280 */
    if(BMP280_Read(&g_sensor_pack.bmp280_temp, &g_sensor_pack.bmp280_press) == 0) {
        g_sensor_pack.bmp280_valid = 1;
    } else {
        g_sensor_pack.bmp280_valid = 0;
    }

    /* JED1xx */
    Sensor_ReadJed1xx(JED104_CO_ADDR8, &g_sensor_pack.jed104_co, &g_sensor_pack.jed104_valid);
    Sensor_ReadJed1xx(JED105_NH3_ADDR8, &g_sensor_pack.jed105_nh3, &g_sensor_pack.jed105_valid);
    Sensor_ReadJed1xx(JED116_HCHO_ADDR8, &g_sensor_pack.jed116_hcho, &g_sensor_pack.jed116_valid);
    

    /* SGP41 */
    if(g_sensor_pack.aht20_valid && SGP41_MeasureRaw(&g_sensor_pack.sgp41_voc_sraw, &g_sensor_pack.sgp41_nox_sraw))
    {
        SGP41_ProcessIndex(g_sensor_pack.sgp41_voc_sraw, g_sensor_pack.sgp41_nox_sraw, &g_sensor_pack.sgp41_voc_index, &g_sensor_pack.sgp41_nox_index, g_sensor_pack.aht20_temp, g_sensor_pack.aht20_hum);
        g_sensor_pack.sgp41_valid = 1;
    }
    else {
        g_sensor_pack.sgp41_valid = 0;
    }

    g_sensor_ui_update_flag = 1;
}
