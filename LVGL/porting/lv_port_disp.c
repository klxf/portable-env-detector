#include "lv_port_disp.h"
#include "lvgl.h"
#include "ST7789/st7789.h"
#include "ch32v30x.h"

#define MY_DISP_HOR_RES    240
#define MY_DISP_VER_RES    240

/* 单缓冲 */
#define DISP_BUF_SIZE      (MY_DISP_HOR_RES * 20)
static lv_color_t draw_buf[DISP_BUF_SIZE];

/* DMA 发送字节缓冲 */
static uint8_t    dma_tx_buf[DISP_BUF_SIZE * 2];

static lv_disp_drv_t * disp_drv_p = NULL;
static volatile uint8_t dma_busy  = 0;

/* ---------- DMA1_Channel3 (SPI1_TX) 初始化 ---------- */
static void DMA_SPI1_TX_Init(void)
{
    DMA_InitTypeDef DMA_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;

    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
    DMA_DeInit(DMA1_Channel3);

    DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&SPI1->DATAR;
    DMA_InitStructure.DMA_MemoryBaseAddr     = (uint32_t)dma_tx_buf;
    DMA_InitStructure.DMA_DIR                = DMA_DIR_PeripheralDST;
    DMA_InitStructure.DMA_BufferSize         = 0;
    DMA_InitStructure.DMA_PeripheralInc      = DMA_PeripheralInc_Disable;
    DMA_InitStructure.DMA_MemoryInc          = DMA_MemoryInc_Enable;
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
    DMA_InitStructure.DMA_MemoryDataSize     = DMA_MemoryDataSize_Byte;
    DMA_InitStructure.DMA_Mode               = DMA_Mode_Normal;
    DMA_InitStructure.DMA_Priority           = DMA_Priority_High;
    DMA_InitStructure.DMA_M2M                = DMA_M2M_Disable;
    DMA_Init(DMA1_Channel3, &DMA_InitStructure);

    DMA_ITConfig(DMA1_Channel3, DMA_IT_TC, ENABLE);

    NVIC_InitStructure.NVIC_IRQChannel                   = DMA1_Channel3_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority        = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd                = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    SPI_I2S_DMACmd(SPI1, SPI_I2S_DMAReq_Tx, ENABLE);
}

/* ---------- DMA 传输完成中断 ---------- */
void DMA1_Channel3_IRQHandler(void) __attribute__((interrupt("WCH-Interrupt-fast")));
void DMA1_Channel3_IRQHandler(void)
{
    if(DMA_GetITStatus(DMA1_IT_TC3) != RESET)
    {
        DMA_ClearITPendingBit(DMA1_IT_TC3);
        DMA_Cmd(DMA1_Channel3, DISABLE);

        while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);
        while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_BSY) != RESET);

        ST7789_CS_HIGH();
        dma_busy = 0;

        if(disp_drv_p != NULL) {
            lv_disp_flush_ready(disp_drv_p);
        }
    }
}

/* ---------- LVGL 刷新回调（正常顺序，硬件做旋转） ---------- */
static void disp_flush(lv_disp_drv_t *disp_drv, const lv_area_t *area, lv_color_t *color_p)
{
    uint16_t x1 = area->x1;
    uint16_t y1 = area->y1 + ST7789_Y_OFFSET;
    uint16_t x2 = area->x2;
    uint16_t y2 = area->y2 + ST7789_Y_OFFSET;

    uint32_t pixel_count = (uint32_t)(x2 - x1 + 1) * (uint32_t)(y2 - y1 + 1);
    uint16_t dma_size = (uint16_t)(pixel_count * 2);

    while(dma_busy);
    dma_busy = 1;

    /* 字节交换 */
    for(uint32_t i = 0; i < pixel_count; i++) {
        uint16_t color = color_p[i].full;
        dma_tx_buf[i * 2]     = color >> 8;
        dma_tx_buf[i * 2 + 1] = color & 0xFF;
    }

    /* 设置窗口并启动 DMA */
    ST7789_PrepareDMAWrite(x1, y1, x2, y2);

    DMA1_Channel3->CNTR  = dma_size;
    DMA1_Channel3->MADDR = (uint32_t)dma_tx_buf;
    DMA_Cmd(DMA1_Channel3, ENABLE);
}

/* ---------- 显示驱动注册 ---------- */
void lv_port_disp_init(void)
{
    static lv_disp_draw_buf_t disp_buf;
    lv_disp_draw_buf_init(&disp_buf, draw_buf, NULL, DISP_BUF_SIZE);

    static lv_disp_drv_t disp_drv;
    lv_disp_drv_init(&disp_drv);
    disp_drv_p = &disp_drv;

    disp_drv.hor_res  = MY_DISP_HOR_RES;
    disp_drv.ver_res  = MY_DISP_VER_RES;
    disp_drv.flush_cb = disp_flush;
    disp_drv.draw_buf = &disp_buf;

    lv_disp_drv_register(&disp_drv);
    DMA_SPI1_TX_Init();
}
