/********************************** (C) COPYRIGHT *******************************
* File Name          : main.c
* Author             : Fang
* Version            : V1.0.0_261012
* Date               : 2026/10/12
* Description        : Main program body.
*********************************************************************************
* Copyright (c) 2021 Nanjing Qinheng Microelectronics Co., Ltd.
* Attention: This software (modified or not) and binary are used for 
* microcontroller manufactured by Nanjing Qinheng Microelectronics.
*******************************************************************************/

/*
 *@Note
 USART Print debugging routine:
 USART1_Tx(PA9).
 This example demonstrates using USART1(PA9) as a print debug port output.

*/

#include "debug.h"

#include "lvgl.h"
#include "lv_port_disp.h"
#include "gui_guider.h"
#include "events_init.h"

#include "Bat/bat.h"

#include "Settings/settings_store.h"

#include "I2C1_Bus/i2c1_soft.h"
#include "Sensor_Fusion/sensor_data.h"

#include "ST7789/st7789.h"

/* Global typedef */

/* Global define */

/* Global Variable */
volatile uint8_t led_flag = 0;
lv_ui guider_ui;
static lv_group_t * key_group;
static lv_indev_t * keypad_indev;

uint8_t is_settings_scr = 0;
uint8_t is_main_scr = 0;
static volatile uint8_t screen_request = 0;
static uint8_t settings_brightness = 80;
static bool auto_screen_off_enabled = false;
static bool screen_is_off = false;
static uint8_t screen_dimmed = 0;
static uint32_t last_input_tick = 0;
static uint32_t screen_dimmed_tick = 0;
static int8_t settings_focus_index = -1;

#define UI_ANIM_TIME_MS          300
#define UI_ANIM_WAIT_MS          320
#define SCREEN_OFF_TIMEOUT_MS    30000U
#define SCREEN_DIM_TIMEOUT_MS    5000U
#define SCREEN_DIM_BRIGHTNESS    10U
#define BRIGHTNESS_STEP          10
#define BRIGHTNESS_MIN           10

float bat_voltage = 3.7f;
uint8_t bat_percentage = 100;

static void SaveSettings(void);
static void ApplyMainFocusStyles(lv_ui *ui);

static void ApplyBrightness(uint8_t brightness)
{
    if(brightness > 100) brightness = 100;
    if(brightness < BRIGHTNESS_MIN) brightness = BRIGHTNESS_MIN;
    settings_brightness = brightness;

    if(!screen_is_off) {
        screen_dimmed = false;
        ST7789_Backlight_Set(settings_brightness);
    }

    if(guider_ui.settings != NULL && guider_ui.settings_slider_1 != NULL) {
        lv_slider_set_value(guider_ui.settings_slider_1, settings_brightness, LV_ANIM_ON);
    }

    SaveSettings();
}

static void SetAutoScreenOff(bool enabled)
{
    bool changed = auto_screen_off_enabled != enabled;

    auto_screen_off_enabled = enabled;
    if(enabled) {
        last_input_tick = lv_tick_get();
        if(screen_is_off || screen_dimmed) {
            screen_is_off = false;
            screen_dimmed = false;
            ST7789_Backlight_Set(settings_brightness);
        }
    } else {
        screen_dimmed = false;
        if(screen_is_off) {
            screen_is_off = false;
            screen_dimmed = false;
            ST7789_Backlight_Set(settings_brightness);
        }
    }

    if(guider_ui.settings != NULL && guider_ui.settings_sw_1 != NULL) {
        if(enabled) {
            lv_obj_add_state(guider_ui.settings_sw_1, LV_STATE_CHECKED);
        } else {
            lv_obj_clear_state(guider_ui.settings_sw_1, LV_STATE_CHECKED);
        }
    }

    printf("[UI] auto screen off=%d\r\n", auto_screen_off_enabled);

    if(changed) {
        SaveSettings();
    }
}

static void SaveSettings(void)
{
    UserSettings user_settings;

    user_settings.brightness = settings_brightness;
    user_settings.auto_screen_off = auto_screen_off_enabled ? 1u : 0u;

    if(Settings_Store_Save(&user_settings) == 0) {
        printf("[UI] settings saved: brightness=%u auto=%u\r\n",
               settings_brightness, auto_screen_off_enabled);
    } else {
        printf("[UI] settings save failed\r\n");
    }
}

static void UpdateSettingsFocus(uint8_t direction)
{
    lv_obj_t *settings_cards[] = {
        guider_ui.settings_cont_1,
        guider_ui.settings_cont_2
    };
    int8_t next_index;

    if(settings_focus_index < 0) {
        next_index = (direction == 0) ? 1 : 0;
    } else {
        if((direction == 0 && settings_focus_index == 0) ||
           (direction == 1 && settings_focus_index == 1)) {
            lv_group_remove_all_objs(key_group);
            settings_focus_index = -1;
            printf("[UI] settings focus cleared\r\n");
            return;
        }

        next_index = settings_focus_index;
        next_index += (direction == 0) ? -1 : 1;
    }

    lv_group_remove_all_objs(key_group);
    lv_group_add_obj(key_group, settings_cards[next_index]);
    settings_focus_index = next_index;
    printf("[UI] settings focus=%d\r\n", settings_focus_index);
}

static void BindSettingsGroup(void)
{
    lv_group_remove_all_objs(key_group);
    lv_group_focus_freeze(key_group, true);
    lv_group_add_obj(key_group, guider_ui.settings_cont_1);
    lv_group_add_obj(key_group, guider_ui.settings_cont_2);
    lv_group_focus_freeze(key_group, false);
    lv_group_set_wrap(key_group, true);
    lv_indev_set_group(keypad_indev, key_group);
    settings_focus_index = -1;

    /* Keep UI Guider files untouched; apply runtime focus styling here. */
    lv_obj_t *setting_cards[] = {
        guider_ui.settings_cont_1,
        guider_ui.settings_cont_2
    };
    for(uint8_t i = 0; i < sizeof(setting_cards) / sizeof(setting_cards[0]); i++) {
        lv_obj_set_style_bg_color(setting_cards[i], lv_color_hex(0x334155),
                                  LV_PART_MAIN | LV_STATE_FOCUSED);
        lv_obj_set_style_bg_opa(setting_cards[i], 255,
                                LV_PART_MAIN | LV_STATE_FOCUSED);
        lv_obj_set_style_border_color(setting_cards[i], lv_color_hex(0x38bdf8),
                                      LV_PART_MAIN | LV_STATE_FOCUSED);
        lv_obj_set_style_border_width(setting_cards[i], 2,
                                      LV_PART_MAIN | LV_STATE_FOCUSED);
        lv_obj_set_style_border_opa(setting_cards[i], 255,
                                    LV_PART_MAIN | LV_STATE_FOCUSED);
        lv_obj_set_style_outline_width(setting_cards[i], 0,
                                       LV_PART_MAIN | LV_STATE_FOCUSED);
    }
}

static void BindMainGroup(void)
{
    lv_group_remove_all_objs(key_group);
    lv_group_add_obj(key_group, guider_ui.main_cont_temp);
    lv_group_add_obj(key_group, guider_ui.main_cont_humi);
    lv_group_add_obj(key_group, guider_ui.main_cont_pres);
    lv_group_add_obj(key_group, guider_ui.main_cont_hcho);
    lv_group_add_obj(key_group, guider_ui.main_cont_nh3);
    lv_group_add_obj(key_group, guider_ui.main_cont_voc);
    lv_group_add_obj(key_group, guider_ui.main_cont_nox);
    lv_group_add_obj(key_group, guider_ui.main_cont_co);
    lv_group_add_obj(key_group, guider_ui.main_cont_bat);
    lv_group_set_wrap(key_group, true);
    lv_indev_set_group(keypad_indev, key_group);
    ApplyMainFocusStyles(&guider_ui);
}

static void ApplyMainFocusStyles(lv_ui *ui)
{
    lv_obj_t *cards[] = {
        ui->main_cont_temp, ui->main_cont_humi, ui->main_cont_pres,
        ui->main_cont_hcho, ui->main_cont_nh3, ui->main_cont_voc,
        ui->main_cont_nox, ui->main_cont_co, ui->main_cont_bat
    };

    for(uint8_t i = 0; i < sizeof(cards) / sizeof(cards[0]); i++) {
        lv_obj_set_style_bg_color(cards[i], lv_color_hex(0x334155),
                                  LV_PART_MAIN | LV_STATE_FOCUSED);
        lv_obj_set_style_bg_opa(cards[i], 255,
                                LV_PART_MAIN | LV_STATE_FOCUSED);
        lv_obj_set_style_border_color(cards[i], lv_color_hex(0x38bdf8),
                                      LV_PART_MAIN | LV_STATE_FOCUSED);
        lv_obj_set_style_border_width(cards[i], 1,
                                      LV_PART_MAIN | LV_STATE_FOCUSED);
        lv_obj_set_style_border_opa(cards[i], 255,
                                    LV_PART_MAIN | LV_STATE_FOCUSED);
        lv_obj_set_style_outline_width(cards[i], 0,
                                       LV_PART_MAIN | LV_STATE_FOCUSED);
    }
}

static void BootDelay(uint32_t ms)
{
    uint32_t start = lv_tick_get();

    do {
        lv_timer_handler();
        Delay_Ms(2);
    } while((lv_tick_get() - start) < ms);
}

static void ShowSettingsScreen(void)
{
    if(guider_ui.settings == NULL) {
        setup_scr_settings(&guider_ui);
        if(guider_ui.settings == NULL) {
            return;
        }
        guider_ui.settings_del = false;
    }

    is_settings_scr = 1;
    BindSettingsGroup();
    settings_focus_index = -1;
    lv_group_focus_freeze(key_group, true);
    lv_group_focus_freeze(key_group, false);
    lv_slider_set_value(guider_ui.settings_slider_1, settings_brightness, LV_ANIM_OFF);
    if(auto_screen_off_enabled) {
        lv_obj_add_state(guider_ui.settings_sw_1, LV_STATE_CHECKED);
    } else {
        lv_obj_clear_state(guider_ui.settings_sw_1, LV_STATE_CHECKED);
    }

    lv_scr_load_anim(guider_ui.settings, LV_SCR_LOAD_ANIM_MOVE_LEFT,
                     UI_ANIM_TIME_MS, 0, true);
    guider_ui.main = NULL;
    BootDelay(UI_ANIM_WAIT_MS);
}

static void ShowMainScreen(void)
{
    if(guider_ui.main == NULL) {
        setup_scr_main(&guider_ui);
        if(guider_ui.main == NULL) {
            return;
        }
        guider_ui.main_del = false;
    }

    is_settings_scr = 0;
    BindMainGroup();
    settings_focus_index = -1;
    lv_group_focus_obj(guider_ui.main_cont_temp);

    lv_scr_load_anim(guider_ui.main, LV_SCR_LOAD_ANIM_MOVE_RIGHT,
                     UI_ANIM_TIME_MS, 0, true);
    guider_ui.settings = NULL;
    BootDelay(UI_ANIM_WAIT_MS);
    g_sensor_ui_update_flag = 1;
}

static void keypad_read(lv_indev_drv_t * indev_drv, lv_indev_data_t * data)
{
    (void) indev_drv;
    static uint32_t last_key = 0;
    uint32_t key = 0;

    if(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_13) == Bit_RESET) {
        key = LV_KEY_UP;
    }
    else if(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_14) == Bit_RESET) {
        key = LV_KEY_DOWN;
    }
    else if(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_12) == Bit_RESET) {
        key = LV_KEY_ENTER;
    }
    else if(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_15) == Bit_RESET) {
        key = LV_KEY_ESC;
    }
    else if(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0) == Bit_RESET) {
        key = LV_KEY_HOME;  // 弃用
    }

    if(key != 0) {
        data->state = LV_INDEV_STATE_PRESSED;
        data->key   = key;
        last_input_tick = lv_tick_get();

        if(screen_dimmed) {
            screen_dimmed = false;
            ST7789_Backlight_Set(settings_brightness);
        }

        if(screen_is_off) {
            screen_is_off = false;
            ST7789_Backlight_Set(settings_brightness);
            last_key = key;
            data->state = LV_INDEV_STATE_RELEASED;
            data->key = 0;
            return;
        }
        
        if(is_settings_scr && (key == LV_KEY_DOWN || key == LV_KEY_UP) &&
           last_key != key) {
            UpdateSettingsFocus((key == LV_KEY_DOWN) ? 1u : 0u);
        }
        else if(!is_settings_scr && (key == LV_KEY_DOWN || key == LV_KEY_UP) &&
                last_key != key) {
            if(key == LV_KEY_DOWN) {
                lv_group_focus_next(key_group);
            } else {
                lv_group_focus_prev(key_group);
            }
            lv_obj_t * focused = lv_group_get_focused(key_group);
            if(focused) {
                lv_obj_scroll_to_view(focused, LV_ANIM_ON);
            }
        }
        else if(key == LV_KEY_ENTER && last_key != LV_KEY_ENTER && !is_settings_scr && screen_request == 0) {
            is_settings_scr = 1;
            screen_request = 1;
        }
        else if(key == LV_KEY_ENTER && last_key != LV_KEY_ENTER && is_settings_scr) {
            if(settings_focus_index == 0) {
                ApplyBrightness((uint8_t)(settings_brightness + BRIGHTNESS_STEP));
            } else if(settings_focus_index == 1) {
                SetAutoScreenOff(true);
            }
        }
        else if(key == LV_KEY_ESC && last_key != LV_KEY_ESC && is_settings_scr) {
            if(settings_focus_index == 0) {
                ApplyBrightness((uint8_t)((settings_brightness > BRIGHTNESS_STEP) ?
                                          (settings_brightness - BRIGHTNESS_STEP) : 0));
            } else if(settings_focus_index == 1) {
                SetAutoScreenOff(false);
            } else if(screen_request == 0) {
                is_settings_scr = 0;
                screen_request = 2;
            }
        }
        last_key = key;
    } else {
        data->state = LV_INDEV_STATE_RELEASED;
        last_key = 0;
    }
}

void setup_keypad_navigation(lv_ui *ui)
{
    key_group = lv_group_create();

	/*lv_obj_add_flag(ui->main_cont_temp, LV_OBJ_FLAG_CLICK_FOCUSABLE);
    lv_obj_add_flag(ui->main_cont_humi, LV_OBJ_FLAG_CLICK_FOCUSABLE);
    lv_obj_add_flag(ui->main_cont_pres, LV_OBJ_FLAG_CLICK_FOCUSABLE);
    lv_obj_add_flag(ui->main_cont_hcho, LV_OBJ_FLAG_CLICK_FOCUSABLE);
    lv_obj_add_flag(ui->main_cont_nh3, LV_OBJ_FLAG_CLICK_FOCUSABLE);
    lv_obj_add_flag(ui->main_cont_voc, LV_OBJ_FLAG_CLICK_FOCUSABLE);
    lv_obj_add_flag(ui->main_cont_nox, LV_OBJ_FLAG_CLICK_FOCUSABLE);
    lv_obj_add_flag(ui->main_cont_co, LV_OBJ_FLAG_CLICK_FOCUSABLE);
    lv_obj_add_flag(ui->main_cont_bat, LV_OBJ_FLAG_CLICK_FOCUSABLE);*/

    lv_group_add_obj(key_group, ui->main_cont_temp);
    lv_group_add_obj(key_group, ui->main_cont_humi);
    lv_group_add_obj(key_group, ui->main_cont_pres);
    lv_group_add_obj(key_group, ui->main_cont_hcho);
    lv_group_add_obj(key_group, ui->main_cont_nh3);
    lv_group_add_obj(key_group, ui->main_cont_voc);
    lv_group_add_obj(key_group, ui->main_cont_nox);
    lv_group_add_obj(key_group, ui->main_cont_co);
    lv_group_add_obj(key_group, ui->main_cont_bat);

    static lv_indev_drv_t indev_drv;
    lv_indev_drv_init(&indev_drv);
    indev_drv.type    = LV_INDEV_TYPE_KEYPAD;
    indev_drv.read_cb = keypad_read;
    keypad_indev = lv_indev_drv_register(&indev_drv);

    lv_indev_set_group(keypad_indev, key_group);

    ApplyMainFocusStyles(ui);
    lv_group_focus_obj(ui->main_cont_temp);
}

/*********************************************************************
 * @fn      TIM3_LVGL_Tick_Init
 *
 * @brief   1ms 定时器 TIM3 初始化
 *
 * @return  none
 */
void TIM3_LVGL_Tick_Init(void)
{
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
    NVIC_InitTypeDef NVIC_InitStructure;

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);

    TIM_TimeBaseStructure.TIM_Period        = 1000 - 1;
    TIM_TimeBaseStructure.TIM_Prescaler     = 144 - 1;
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseStructure.TIM_CounterMode   = TIM_CounterMode_Up;
    TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);

    TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
    TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);
    TIM_Cmd(TIM3, ENABLE);

    NVIC_InitStructure.NVIC_IRQChannel                   = TIM3_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority        = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd                = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}

/*********************************************************************
 * @fn      TIM3_IRQHandler
 *
 * @brief   TIM3 中断函数
 *
 * @return  none
 */
void TIM3_IRQHandler(void) __attribute__((interrupt("WCH-Interrupt-fast")));
void TIM3_IRQHandler(void)
{
    if(TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET)
    {
        TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
        lv_tick_inc(1);
    }
}

/*********************************************************************
 * @fn      TIM4_Sensor_Init
 *
 * @brief   1s 定时器 TIM4 初始化
 *
 * @return  none
 */
void TIM4_Sensor_Init(void)
{
    TIM_TimeBaseInitTypeDef TIM_InitStruct;
    NVIC_InitTypeDef NVIC_InitStruct;

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);

    TIM_InitStruct.TIM_Period        = 50000 - 1;
    TIM_InitStruct.TIM_Prescaler     = 14400 - 1;
    TIM_InitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_InitStruct.TIM_CounterMode   = TIM_CounterMode_Up;
    TIM_TimeBaseInit(TIM4, &TIM_InitStruct);

    TIM_ITConfig(TIM4, TIM_IT_Update, ENABLE);
    TIM_Cmd(TIM4, ENABLE);

    NVIC_InitStruct.NVIC_IRQChannel                   = TIM4_IRQn;
    NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 2;
    NVIC_InitStruct.NVIC_IRQChannelSubPriority        = 1;
    NVIC_InitStruct.NVIC_IRQChannelCmd                = ENABLE;
    NVIC_Init(&NVIC_InitStruct);
}

/*********************************************************************
 * @fn      TIM4_IRQHandler
 *
 * @brief   TIM4 中断函数
 *
 * @return  none
 */
void TIM4_IRQHandler(void) __attribute__((interrupt("WCH-Interrupt-fast")));
void TIM4_IRQHandler(void)
{
    if(TIM_GetITStatus(TIM4, TIM_IT_Update) != RESET)
    {
        TIM_ClearITPendingBit(TIM4, TIM_IT_Update);
        g_sensor_collect_flag = 1;
    }
}

/*********************************************************************
 * @fn      Key_GPIO_Init
 *
 * @brief   按键初始化
 *
 * @return  none
 */
void Key_GPIO_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB, ENABLE);

    GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IPU;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_0;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
}

/*********************************************************************
 * @fn      LED_PC13_Init
 *
 * @brief   PC13 LED 初始化
 *
 * @return  none
 */
void LED_PC13_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);

    GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_13;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOC, &GPIO_InitStructure);

    GPIO_SetBits(GPIOC, GPIO_Pin_13);
}

/*********************************************************************
 * @fn      update_ui
 *
 * @brief   初始化 UI
 *
 * @return  none
 */
static void update_ui(void)
{
    if(guider_ui.main == NULL) {
        g_sensor_ui_update_flag = 0;
        return;
    }

    if(g_sensor_pack.aht20_valid)
    {
        lv_label_set_text_fmt(guider_ui.main_label_temp_val, "%.2f", g_sensor_pack.aht20_temp);
        lv_label_set_text_fmt(guider_ui.main_label_humi_val, "%.2f", g_sensor_pack.aht20_hum);
    }
    else
    {
        lv_label_set_text(guider_ui.main_label_temp_val, "ERR");
        lv_label_set_text(guider_ui.main_label_hcho_val, "ERR");
    }

    if(g_sensor_pack.bmp280_valid)
        lv_label_set_text_fmt(guider_ui.main_label_pres_val, "%.2f", g_sensor_pack.bmp280_press);
    else
        lv_label_set_text(guider_ui.main_label_pres_val, "ERR");
    
    if(g_sensor_pack.sgp41_valid)
    {
        lv_label_set_text_fmt(guider_ui.main_label_voc_val, "%d", g_sensor_pack.sgp41_voc_index);
        lv_label_set_text_fmt(guider_ui.main_label_nox_val, "%d", g_sensor_pack.sgp41_nox_index);
    }
    else
    {
        lv_label_set_text(guider_ui.main_label_voc_val, "ERR");
        lv_label_set_text(guider_ui.main_label_nox_val, "ERR");
    }

    if(g_sensor_pack.jed104_valid)
        lv_label_set_text_fmt(guider_ui.main_label_co_val, "%d", g_sensor_pack.jed104_co);
    else
        lv_label_set_text(guider_ui.main_label_co_val, "ERR");

    if(g_sensor_pack.jed105_valid)
        lv_label_set_text_fmt(guider_ui.main_label_nh3_val, "%d", g_sensor_pack.jed105_nh3);
    else
        lv_label_set_text(guider_ui.main_label_nh3_val, "ERR");

    if(g_sensor_pack.jed116_valid)
        lv_label_set_text_fmt(guider_ui.main_label_hcho_val, "%d", g_sensor_pack.jed116_hcho);
    else
        lv_label_set_text(guider_ui.main_label_hcho_val, "ERR");

    lv_label_set_text_fmt(guider_ui.main_label_bat_val, "%d%%", bat_percentage);
}

/*********************************************************************
 * @fn      main
 *
 * @brief   Main program.
 *
 * @return  none
 */
int main(void)
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	SystemCoreClockUpdate();
	Delay_Init();
	USART_Printf_Init(115200);	
	printf("SystemClk:%d\r\n", SystemCoreClock);
	printf("ChipID:%08x\r\n", DBGMCU_GetCHIPID() );

	LED_PC13_Init();
	Key_GPIO_Init();
    BAT_ADC_Init();

	ST7789_Init();
	ST7789_Backlight_Init();
	lv_init();
	lv_port_disp_init();
	TIM3_LVGL_Tick_Init();

    UserSettings boot_settings;
    Settings_Store_Init();
    Settings_Store_Load(&boot_settings);
    settings_brightness = boot_settings.brightness;
    auto_screen_off_enabled = boot_settings.auto_screen_off != 0;
    last_input_tick = lv_tick_get();
    ST7789_Backlight_Set(settings_brightness);

	setup_ui(&guider_ui);
    setup_scr_startup(&guider_ui);
    lv_scr_load(guider_ui.startup);
    guider_ui.main_del = false;
    BootDelay(300);

    Sensor_Fusion_Init();

    printf("Soft I2C Scan:\r\n");
    uint8_t addrs[] = {0x38, 0x76, 0x59, 0x54, 0x58, 0x5C};
    for(int i = 0; i < 6; i++) {
        uint8_t ack = I2C1_Soft_Scan(addrs[i]);
        printf("  %s 0x%02X\r\n", ack == 0 ? "Found" : "--   ", addrs[i]);
        if(ack == 0)
        {
            GPIO_SetBits(GPIOC, GPIO_Pin_13);
        } else
        {
            GPIO_ResetBits(GPIOC, GPIO_Pin_13);
        }
        BootDelay(50);
    }

    ui_load_scr_animation(&guider_ui, &guider_ui.main, guider_ui.main_del,
                          &guider_ui.startup_del, setup_scr_main,
                          LV_SCR_LOAD_ANIM_FADE_OUT, 100, 100, false, true);
    guider_ui.main_del = false;

    BootDelay(250);
    events_init(&guider_ui);
    setup_keypad_navigation(&guider_ui);
    TIM4_Sensor_Init();

	while(1)
    {
        if(g_sensor_collect_flag)
        {
            g_sensor_collect_flag = 0;

            bat_percentage = BAT_GetPercentage();
            bat_voltage = BAT_GetCachedVoltage();
            Sensor_Collect_All();

            printf("Collect: aht20_t=%.2f, aht20_h=%.2f, bmp280_t=%.2f, bmp280_p=%.2f, sgp41_voc=%d(%d), sgp41_nox=%d(%d)\r\n",
                   g_sensor_pack.aht20_temp, g_sensor_pack.aht20_hum,
                   g_sensor_pack.bmp280_temp, g_sensor_pack.bmp280_press,
                   g_sensor_pack.sgp41_voc_index, g_sensor_pack.sgp41_voc_sraw, g_sensor_pack.sgp41_nox_index, g_sensor_pack.sgp41_nox_sraw);
            printf("Battery: %.2fV (%d%%)\r\n", bat_voltage, bat_percentage);
        }

        if(screen_request != 0) {
            if(screen_request == 1) ShowSettingsScreen();
            else if(screen_request == 2) ShowMainScreen();
            screen_request = 0;
        }

        if(auto_screen_off_enabled && !screen_is_off) {
            if(!screen_dimmed &&
               lv_tick_elaps(last_input_tick) >= SCREEN_OFF_TIMEOUT_MS) {
                screen_dimmed = true;
                screen_dimmed_tick = lv_tick_get();
                ST7789_Backlight_Set(SCREEN_DIM_BRIGHTNESS);
                printf("[UI] screen dimmed to %u%%\r\n", SCREEN_DIM_BRIGHTNESS);
            }
            else if(screen_dimmed &&
                    lv_tick_elaps(screen_dimmed_tick) >= SCREEN_DIM_TIMEOUT_MS) {
                screen_is_off = true;
                screen_dimmed = false;
                ST7789_Backlight_Off();
                printf("[UI] screen off timeout\r\n");
            }
        }

        if(g_sensor_ui_update_flag)
        {
            g_sensor_ui_update_flag = 0;
            update_ui();
            printf("ui update\r\n");
        }

		lv_timer_handler();
        Delay_Ms(2);
	}
}
