/*
* Copyright 2026 NXP
* NXP Proprietary. This software is owned or controlled by NXP and may only be used strictly in
* accordance with the applicable license terms. By expressly accepting such terms or by downloading, installing,
* activating and/or otherwise using the software, you are agreeing that you have read, and that you agree to
* comply with and are bound by, such license terms.  If you do not agree to be bound by the applicable license
* terms, then you may not retain, install, activate or otherwise use the software.
*/

#ifndef GUI_GUIDER_H
#define GUI_GUIDER_H
#ifdef __cplusplus
extern "C" {
#endif

#include "lvgl.h"

typedef struct
{
  
	lv_obj_t *startup;
	bool startup_del;
	lv_obj_t *startup_spinner_1;
	lv_obj_t *main;
	bool main_del;
	lv_obj_t *main_cont_main;
	lv_obj_t *main_cont_temp;
	lv_obj_t *main_label_temp_val;
	lv_obj_t *main_label_temp_title;
	lv_obj_t *main_img_temp;
	lv_obj_t *main_cont_humi;
	lv_obj_t *main_label_humi_val;
	lv_obj_t *main_label_humi_titl;
	lv_obj_t *main_img_humi;
	lv_obj_t *main_cont_pres;
	lv_obj_t *main_label_pres_val;
	lv_obj_t *main_label_pres_title;
	lv_obj_t *main_img_pres;
	lv_obj_t *main_cont_hcho;
	lv_obj_t *main_label_hcho_val;
	lv_obj_t *main_label_hcho_title;
	lv_obj_t *main_img_hcho;
	lv_obj_t *main_cont_nh3;
	lv_obj_t *main_label_nh3_val;
	lv_obj_t *main_label_nh3_title;
	lv_obj_t *main_img_nh3;
	lv_obj_t *main_cont_voc;
	lv_obj_t *main_label_voc_val;
	lv_obj_t *main_label_voc_title;
	lv_obj_t *main_img_voc;
	lv_obj_t *main_cont_nox;
	lv_obj_t *main_label_nox_val;
	lv_obj_t *main_label_nox_title;
	lv_obj_t *main_img_nox;
	lv_obj_t *main_cont_co;
	lv_obj_t *main_label_co_val;
	lv_obj_t *main_label_co_title;
	lv_obj_t *main_img_co;
	lv_obj_t *main_cont_bat;
	lv_obj_t *main_label_bat_val;
	lv_obj_t *main_label_bat_title;
	lv_obj_t *main_img_bat;
	lv_obj_t *settings;
	bool settings_del;
	lv_obj_t *settings_cont_main;
	lv_obj_t *settings_cont_1;
	lv_obj_t *settings_label_1;
	lv_obj_t *settings_slider_1;
	lv_obj_t *settings_cont_2;
	lv_obj_t *settings_sw_1;
	lv_obj_t *settings_label_2;
	lv_obj_t *settings_label_version;
}lv_ui;

typedef void (*ui_setup_scr_t)(lv_ui * ui);

void ui_init_style(lv_style_t * style);

void ui_load_scr_animation(lv_ui *ui, lv_obj_t ** new_scr, bool new_scr_del, bool * old_scr_del, ui_setup_scr_t setup_scr,
                           lv_scr_load_anim_t anim_type, uint32_t time, uint32_t delay, bool is_clean, bool auto_del);

void ui_animation(void * var, int32_t duration, int32_t delay, int32_t start_value, int32_t end_value, lv_anim_path_cb_t path_cb,
                       uint16_t repeat_cnt, uint32_t repeat_delay, uint32_t playback_time, uint32_t playback_delay,
                       lv_anim_exec_xcb_t exec_cb, lv_anim_start_cb_t start_cb, lv_anim_ready_cb_t ready_cb, lv_anim_deleted_cb_t deleted_cb);


void init_scr_del_flag(lv_ui *ui);

void setup_ui(lv_ui *ui);

void init_keyboard(lv_ui *ui);

extern lv_ui guider_ui;


void setup_scr_startup(lv_ui *ui);
void setup_scr_main(lv_ui *ui);
void setup_scr_settings(lv_ui *ui);
LV_IMG_DECLARE(_temp_alpha_32x32);
LV_IMG_DECLARE(_humi_alpha_32x32);
LV_IMG_DECLARE(_pres_alpha_32x32);
LV_IMG_DECLARE(_hcho_alpha_32x32);
LV_IMG_DECLARE(_nh3_alpha_32x32);
LV_IMG_DECLARE(_voc_alpha_32x32);
LV_IMG_DECLARE(_nox_alpha_32x32);
LV_IMG_DECLARE(_co_alpha_32x32);
LV_IMG_DECLARE(_battery_alpha_16x16);

LV_FONT_DECLARE(lv_font_montserratMedium_26)
LV_FONT_DECLARE(lv_font_SourceHanSerifSC_Regular_12)
LV_FONT_DECLARE(lv_font_montserratMedium_16)


#ifdef __cplusplus
}
#endif
#endif
