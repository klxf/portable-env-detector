#include "sgp41.h"
#include "I2C1_Bus/i2c1_soft.h"
#include "ch32v30x.h"
#include "sensirion_gas_index_algorithm.h"

/* SGP41 命令定义 */
#define SGP41_CMD_MEASURE_RAW       0x2619   /* 0x26 0x19: 测量 VOC+NOx */
#define SGP41_CMD_EXECUTE_SELF_TEST 0x280E   /* 0x28 0x0E: 自检 */
#define SGP41_CMD_TURN_HEATER_ON    0x3611   /* 0x36 0x11: 加热器开启 */

static GasIndexAlgorithmParams voc_params;
static GasIndexAlgorithmParams nox_params;
static uint8_t algorithm_initialized = 0;

void SGP41_Algorithm_Init(void)
{
    GasIndexAlgorithm_init(&voc_params, GasIndexAlgorithm_ALGORITHM_TYPE_VOC);
    GasIndexAlgorithm_init(&nox_params, GasIndexAlgorithm_ALGORITHM_TYPE_NOX);
    algorithm_initialized = 1;
}

void SGP41_ProcessIndex(uint16_t sraw_voc, uint16_t sraw_nox,
                        int32_t *voc_index, int32_t *nox_index,
                        float humidity, float temperature)
{
    if(!algorithm_initialized) {
        SGP41_Algorithm_Init();
    }

    /* 算法库直接处理原始值，内部会自动做温湿度补偿 */
    GasIndexAlgorithm_process(&voc_params, (int32_t)sraw_voc, voc_index);
    GasIndexAlgorithm_process(&nox_params, (int32_t)sraw_nox, nox_index);
}

/* CRC8 多项式: x^8 + x^5 + x^4 + 1 = 0x31 */
static uint8_t sgp41_crc8(uint8_t *data, uint8_t len)
{
    uint8_t crc = 0xFF;
    for(uint8_t i = 0; i < len; i++) {
        crc ^= data[i];
        for(uint8_t j = 0; j < 8; j++) {
            if(crc & 0x80) crc = (crc << 1) ^ 0x31;
            else           crc = (crc << 1);
        }
    }
    return crc;
}

/* 发送 16 位命令 + 参数（带 CRC） */
static uint8_t sgp41_send_cmd(uint16_t cmd, uint16_t *params, uint8_t param_count)
{
    uint8_t buf[8];
    uint8_t idx = 0;

    buf[idx++] = cmd >> 8;
    buf[idx++] = cmd & 0xFF;

    for(uint8_t i = 0; i < param_count; i++) {
        buf[idx++] = params[i] >> 8;
        buf[idx++] = params[i] & 0xFF;
        buf[idx++] = sgp41_crc8((uint8_t*)&params[i], 2);
    }

    return I2C1_Soft_Write(SGP41_ADDR, buf, idx);
}

/* 读取 6 字节数据（2×(MSB+LSB+CRC)） */
static uint8_t sgp41_read_data(uint8_t *buf6)
{
    uint8_t err = I2C1_Soft_Read(SGP41_ADDR, buf6, 6);
    if(err != 0) return err;

    /* 验证 CRC */
    uint8_t crc0 = sgp41_crc8(&buf6[0], 2);
    uint8_t crc1 = sgp41_crc8(&buf6[3], 2);
    if(crc0 != buf6[2] || crc1 != buf6[5]) return 3;

    return 0;
}

uint8_t SGP41_Init(void)
{
    uint8_t err;
    uint16_t sraw_voc, sraw_nox;

    /* 上电后等待 >10ms */
    Delay_Ms(20);

    /* 执行一次测量，让传感器进入工作状态 */
    err = SGP41_MeasureRaw(&sraw_voc, &sraw_nox);
    if(err != 0) return err;

    /* 传感器需要预热约 60s 才能达到最佳精度，这里只初始化 */
    return 0;
}

uint8_t SGP41_MeasureRaw(uint16_t *sraw_voc, uint16_t *sraw_nox)
{
    uint8_t err;
    uint8_t buf[6];
    uint16_t params[2];

    /* 默认补偿参数：湿度=0x8000 (50% RH), 温度=0x6666 (25°C) */
    /* 如需精确补偿，传入 AHT20 的温湿度值 */
    params[0] = 0x8000;   /* 默认湿度补偿 */
    params[1] = 0x6666;   /* 默认温度补偿 */

    /* 发送测量命令 */
    err = sgp41_send_cmd(SGP41_CMD_MEASURE_RAW, params, 2);
    if(err != 0) return 1;

    /* 等待 60ms 转换完成 */
    Delay_Ms(60);

    /* 读取结果 */
    err = sgp41_read_data(buf);
    if(err != 0) return 2;

    *sraw_voc = ((uint16_t)buf[0] << 8) | buf[1];
    *sraw_nox = ((uint16_t)buf[3] << 8) | buf[4];

    return 0;
}

uint8_t SGP41_ExecuteSelfTest(void)
{
    uint8_t err;
    uint8_t buf[6];

    err = sgp41_send_cmd(SGP41_CMD_EXECUTE_SELF_TEST, NULL, 0);
    if(err != 0) return 1;

    /* 自检需要 320ms */
    Delay_Ms(350);

    err = sgp41_read_data(buf);
    if(err != 0) return 2;

    /* 结果：buf[0]<<8|buf[1] = 0xD400 表示通过 */
    uint16_t result = ((uint16_t)buf[0] << 8) | buf[1];
    if(result != 0xD400) return 3;

    return 0;
}

uint8_t SGP41_TurnHeaterOn(void)
{
    uint8_t err = sgp41_send_cmd(SGP41_CMD_TURN_HEATER_ON, NULL, 0);
    if(err != 0) return 1;

    /* 加热器运行 10s 后自动关闭 */
    Delay_Ms(10000);
    return 0;
}
