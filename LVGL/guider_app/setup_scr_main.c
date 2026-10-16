/*
* Copyright 2026 NXP
* NXP Proprietary. This software is owned or controlled by NXP and may only be used strictly in
* accordance with the applicable license terms. By expressly accepting such terms or by downloading, installing,
* activating and/or otherwise using the software, you are agreeing that you have read, and that you agree to
* comply with and are bound by, such license terms.  If you do not agree to be bound by the applicable license
* terms, then you may not retain, install, activate or otherwise use the software.
*/

#include "lvgl.h"
#include <stdio.h>
#include "gui_guider.h"
#include "events_init.h"
#include "widgets_init.h"
#include "custom.h"



void setup_scr_main(lv_ui *ui)
{
    //Write codes main
    ui->main = lv_obj_create(NULL);
    lv_obj_set_size(ui->main, 240, 240);
    lv_obj_set_scrollbar_mode(ui->main, LV_SCROLLBAR_MODE_OFF);

    //Write style for main, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->main, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->main, lv_color_hex(0x0F172A), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->main, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes main_cont_main
    ui->main_cont_main = lv_obj_create(ui->main);
    lv_obj_set_pos(ui->main_cont_main, 0, 0);
    lv_obj_set_size(ui->main_cont_main, 240, 240);
    lv_obj_set_scrollbar_mode(ui->main_cont_main, LV_SCROLLBAR_MODE_ACTIVE);
    lv_obj_add_flag(ui->main_cont_main, LV_OBJ_FLAG_SCROLLABLE);

    //Write style for main_cont_main, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->main_cont_main, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->main_cont_main, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->main_cont_main, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->main_cont_main, 10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->main_cont_main, 10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->main_cont_main, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->main_cont_main, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->main_cont_main, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes main_cont_temp
    ui->main_cont_temp = lv_obj_create(ui->main_cont_main);
    lv_obj_set_pos(ui->main_cont_temp, 10, 0);
    lv_obj_set_size(ui->main_cont_temp, 105, 105);
    lv_obj_set_scrollbar_mode(ui->main_cont_temp, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui->main_cont_temp, LV_OBJ_FLAG_CLICK_FOCUSABLE);

    //Write style for main_cont_temp, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->main_cont_temp, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->main_cont_temp, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->main_cont_temp, lv_color_hex(0x1E293B), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->main_cont_temp, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->main_cont_temp, 10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->main_cont_temp, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->main_cont_temp, lv_color_hex(0x1E293B), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->main_cont_temp, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->main_cont_temp, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->main_cont_temp, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->main_cont_temp, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->main_cont_temp, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->main_cont_temp, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes main_label_temp_val
    ui->main_label_temp_val = lv_label_create(ui->main_cont_temp);
    lv_label_set_text(ui->main_label_temp_val, "0.00");
    lv_label_set_long_mode(ui->main_label_temp_val, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->main_label_temp_val, 0, 68);
    lv_obj_set_size(ui->main_label_temp_val, 105, 26);

    //Write style for main_label_temp_val, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->main_label_temp_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->main_label_temp_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->main_label_temp_val, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->main_label_temp_val, &lv_font_montserratMedium_26, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->main_label_temp_val, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->main_label_temp_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->main_label_temp_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->main_label_temp_val, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->main_label_temp_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->main_label_temp_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->main_label_temp_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->main_label_temp_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->main_label_temp_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->main_label_temp_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes main_label_temp_title
    ui->main_label_temp_title = lv_label_create(ui->main_cont_temp);
    lv_label_set_text(ui->main_label_temp_title, "温度 (℃)");
    lv_label_set_long_mode(ui->main_label_temp_title, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->main_label_temp_title, 0, 46);
    lv_obj_set_size(ui->main_label_temp_title, 105, 14);

    //Write style for main_label_temp_title, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->main_label_temp_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->main_label_temp_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->main_label_temp_title, lv_color_hex(0x94a3b8), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->main_label_temp_title, &lv_font_SourceHanSerifSC_Regular_12, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->main_label_temp_title, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->main_label_temp_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->main_label_temp_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->main_label_temp_title, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->main_label_temp_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->main_label_temp_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->main_label_temp_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->main_label_temp_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->main_label_temp_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->main_label_temp_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes main_img_temp
    ui->main_img_temp = lv_img_create(ui->main_cont_temp);
    lv_obj_add_flag(ui->main_img_temp, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->main_img_temp, &_temp_alpha_32x32);
    lv_img_set_pivot(ui->main_img_temp, 16,16);
    lv_img_set_angle(ui->main_img_temp, 0);
    lv_obj_set_pos(ui->main_img_temp, 36, 8);
    lv_obj_set_size(ui->main_img_temp, 32, 32);

    //Write style for main_img_temp, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->main_img_temp, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_recolor(ui->main_img_temp, lv_color_hex(0xfb7185), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->main_img_temp, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->main_img_temp, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->main_img_temp, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes main_cont_humi
    ui->main_cont_humi = lv_obj_create(ui->main_cont_main);
    lv_obj_set_pos(ui->main_cont_humi, 125, 0);
    lv_obj_set_size(ui->main_cont_humi, 105, 105);
    lv_obj_set_scrollbar_mode(ui->main_cont_humi, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui->main_cont_humi, LV_OBJ_FLAG_CLICK_FOCUSABLE);

    //Write style for main_cont_humi, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->main_cont_humi, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->main_cont_humi, 10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->main_cont_humi, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->main_cont_humi, lv_color_hex(0x1E293B), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->main_cont_humi, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->main_cont_humi, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->main_cont_humi, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->main_cont_humi, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->main_cont_humi, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->main_cont_humi, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes main_label_humi_val
    ui->main_label_humi_val = lv_label_create(ui->main_cont_humi);
    lv_label_set_text(ui->main_label_humi_val, "0.00");
    lv_label_set_long_mode(ui->main_label_humi_val, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->main_label_humi_val, 0, 68);
    lv_obj_set_size(ui->main_label_humi_val, 105, 26);

    //Write style for main_label_humi_val, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->main_label_humi_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->main_label_humi_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->main_label_humi_val, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->main_label_humi_val, &lv_font_montserratMedium_26, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->main_label_humi_val, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->main_label_humi_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->main_label_humi_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->main_label_humi_val, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->main_label_humi_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->main_label_humi_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->main_label_humi_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->main_label_humi_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->main_label_humi_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->main_label_humi_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes main_label_humi_titl
    ui->main_label_humi_titl = lv_label_create(ui->main_cont_humi);
    lv_label_set_text(ui->main_label_humi_titl, "湿度 (%RH)");
    lv_label_set_long_mode(ui->main_label_humi_titl, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->main_label_humi_titl, 0, 45);
    lv_obj_set_size(ui->main_label_humi_titl, 105, 14);

    //Write style for main_label_humi_titl, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->main_label_humi_titl, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->main_label_humi_titl, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->main_label_humi_titl, lv_color_hex(0x94a3b8), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->main_label_humi_titl, &lv_font_SourceHanSerifSC_Regular_12, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->main_label_humi_titl, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->main_label_humi_titl, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->main_label_humi_titl, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->main_label_humi_titl, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->main_label_humi_titl, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->main_label_humi_titl, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->main_label_humi_titl, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->main_label_humi_titl, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->main_label_humi_titl, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->main_label_humi_titl, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes main_img_humi
    ui->main_img_humi = lv_img_create(ui->main_cont_humi);
    lv_obj_add_flag(ui->main_img_humi, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->main_img_humi, &_humi_alpha_32x32);
    lv_img_set_pivot(ui->main_img_humi, 16,16);
    lv_img_set_angle(ui->main_img_humi, 0);
    lv_obj_set_pos(ui->main_img_humi, 36, 8);
    lv_obj_set_size(ui->main_img_humi, 32, 32);

    //Write style for main_img_humi, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->main_img_humi, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_recolor(ui->main_img_humi, lv_color_hex(0x38bdf8), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->main_img_humi, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->main_img_humi, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->main_img_humi, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes main_cont_pres
    ui->main_cont_pres = lv_obj_create(ui->main_cont_main);
    lv_obj_set_pos(ui->main_cont_pres, 10, 115);
    lv_obj_set_size(ui->main_cont_pres, 220, 105);
    lv_obj_set_scrollbar_mode(ui->main_cont_pres, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui->main_cont_pres, LV_OBJ_FLAG_CLICK_FOCUSABLE);

    //Write style for main_cont_pres, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->main_cont_pres, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->main_cont_pres, 10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->main_cont_pres, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->main_cont_pres, lv_color_hex(0x1E293B), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->main_cont_pres, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->main_cont_pres, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->main_cont_pres, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->main_cont_pres, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->main_cont_pres, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->main_cont_pres, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes main_label_pres_val
    ui->main_label_pres_val = lv_label_create(ui->main_cont_pres);
    lv_label_set_text(ui->main_label_pres_val, "0.00");
    lv_label_set_long_mode(ui->main_label_pres_val, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->main_label_pres_val, 0, 68);
    lv_obj_set_size(ui->main_label_pres_val, 220, 26);

    //Write style for main_label_pres_val, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->main_label_pres_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->main_label_pres_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->main_label_pres_val, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->main_label_pres_val, &lv_font_montserratMedium_26, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->main_label_pres_val, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->main_label_pres_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->main_label_pres_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->main_label_pres_val, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->main_label_pres_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->main_label_pres_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->main_label_pres_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->main_label_pres_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->main_label_pres_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->main_label_pres_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes main_label_pres_title
    ui->main_label_pres_title = lv_label_create(ui->main_cont_pres);
    lv_label_set_text(ui->main_label_pres_title, "大气压强 (hPa)");
    lv_label_set_long_mode(ui->main_label_pres_title, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->main_label_pres_title, 0, 45);
    lv_obj_set_size(ui->main_label_pres_title, 220, 14);

    //Write style for main_label_pres_title, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->main_label_pres_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->main_label_pres_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->main_label_pres_title, lv_color_hex(0x94a3b8), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->main_label_pres_title, &lv_font_SourceHanSerifSC_Regular_12, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->main_label_pres_title, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->main_label_pres_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->main_label_pres_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->main_label_pres_title, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->main_label_pres_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->main_label_pres_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->main_label_pres_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->main_label_pres_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->main_label_pres_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->main_label_pres_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes main_img_pres
    ui->main_img_pres = lv_img_create(ui->main_cont_pres);
    lv_obj_add_flag(ui->main_img_pres, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->main_img_pres, &_pres_alpha_32x32);
    lv_img_set_pivot(ui->main_img_pres, 16,16);
    lv_img_set_angle(ui->main_img_pres, 0);
    lv_obj_set_pos(ui->main_img_pres, 94, 8);
    lv_obj_set_size(ui->main_img_pres, 32, 32);

    //Write style for main_img_pres, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->main_img_pres, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_recolor(ui->main_img_pres, lv_color_hex(0x818cf8), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->main_img_pres, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->main_img_pres, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->main_img_pres, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes main_cont_hcho
    ui->main_cont_hcho = lv_obj_create(ui->main_cont_main);
    lv_obj_set_pos(ui->main_cont_hcho, 10, 230);
    lv_obj_set_size(ui->main_cont_hcho, 105, 105);
    lv_obj_set_scrollbar_mode(ui->main_cont_hcho, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui->main_cont_hcho, LV_OBJ_FLAG_CLICK_FOCUSABLE);

    //Write style for main_cont_hcho, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->main_cont_hcho, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->main_cont_hcho, 10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->main_cont_hcho, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->main_cont_hcho, lv_color_hex(0x1E293B), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->main_cont_hcho, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->main_cont_hcho, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->main_cont_hcho, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->main_cont_hcho, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->main_cont_hcho, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->main_cont_hcho, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes main_label_hcho_val
    ui->main_label_hcho_val = lv_label_create(ui->main_cont_hcho);
    lv_label_set_text(ui->main_label_hcho_val, "0.00");
    lv_label_set_long_mode(ui->main_label_hcho_val, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->main_label_hcho_val, 0, 68);
    lv_obj_set_size(ui->main_label_hcho_val, 105, 26);

    //Write style for main_label_hcho_val, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->main_label_hcho_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->main_label_hcho_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->main_label_hcho_val, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->main_label_hcho_val, &lv_font_montserratMedium_26, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->main_label_hcho_val, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->main_label_hcho_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->main_label_hcho_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->main_label_hcho_val, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->main_label_hcho_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->main_label_hcho_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->main_label_hcho_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->main_label_hcho_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->main_label_hcho_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->main_label_hcho_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes main_label_hcho_title
    ui->main_label_hcho_title = lv_label_create(ui->main_cont_hcho);
    lv_label_set_text(ui->main_label_hcho_title, "甲醛 (ppm)");
    lv_label_set_long_mode(ui->main_label_hcho_title, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->main_label_hcho_title, 0, 45);
    lv_obj_set_size(ui->main_label_hcho_title, 105, 14);

    //Write style for main_label_hcho_title, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->main_label_hcho_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->main_label_hcho_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->main_label_hcho_title, lv_color_hex(0x94a3b8), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->main_label_hcho_title, &lv_font_SourceHanSerifSC_Regular_12, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->main_label_hcho_title, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->main_label_hcho_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->main_label_hcho_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->main_label_hcho_title, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->main_label_hcho_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->main_label_hcho_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->main_label_hcho_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->main_label_hcho_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->main_label_hcho_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->main_label_hcho_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes main_img_hcho
    ui->main_img_hcho = lv_img_create(ui->main_cont_hcho);
    lv_obj_add_flag(ui->main_img_hcho, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->main_img_hcho, &_hcho_alpha_32x32);
    lv_img_set_pivot(ui->main_img_hcho, 16,16);
    lv_img_set_angle(ui->main_img_hcho, 0);
    lv_obj_set_pos(ui->main_img_hcho, 36, 8);
    lv_obj_set_size(ui->main_img_hcho, 32, 32);

    //Write style for main_img_hcho, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->main_img_hcho, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_recolor(ui->main_img_hcho, lv_color_hex(0x34d399), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->main_img_hcho, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->main_img_hcho, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->main_img_hcho, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes main_cont_nh3
    ui->main_cont_nh3 = lv_obj_create(ui->main_cont_main);
    lv_obj_set_pos(ui->main_cont_nh3, 125, 230);
    lv_obj_set_size(ui->main_cont_nh3, 105, 105);
    lv_obj_set_scrollbar_mode(ui->main_cont_nh3, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui->main_cont_nh3, LV_OBJ_FLAG_CLICK_FOCUSABLE);

    //Write style for main_cont_nh3, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->main_cont_nh3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->main_cont_nh3, 10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->main_cont_nh3, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->main_cont_nh3, lv_color_hex(0x1E293B), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->main_cont_nh3, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->main_cont_nh3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->main_cont_nh3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->main_cont_nh3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->main_cont_nh3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->main_cont_nh3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes main_label_nh3_val
    ui->main_label_nh3_val = lv_label_create(ui->main_cont_nh3);
    lv_label_set_text(ui->main_label_nh3_val, "0.00");
    lv_label_set_long_mode(ui->main_label_nh3_val, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->main_label_nh3_val, 0, 68);
    lv_obj_set_size(ui->main_label_nh3_val, 105, 26);

    //Write style for main_label_nh3_val, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->main_label_nh3_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->main_label_nh3_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->main_label_nh3_val, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->main_label_nh3_val, &lv_font_montserratMedium_26, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->main_label_nh3_val, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->main_label_nh3_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->main_label_nh3_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->main_label_nh3_val, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->main_label_nh3_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->main_label_nh3_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->main_label_nh3_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->main_label_nh3_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->main_label_nh3_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->main_label_nh3_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes main_label_nh3_title
    ui->main_label_nh3_title = lv_label_create(ui->main_cont_nh3);
    lv_label_set_text(ui->main_label_nh3_title, "氨气 (ppm)");
    lv_label_set_long_mode(ui->main_label_nh3_title, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->main_label_nh3_title, 0, 45);
    lv_obj_set_size(ui->main_label_nh3_title, 105, 14);

    //Write style for main_label_nh3_title, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->main_label_nh3_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->main_label_nh3_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->main_label_nh3_title, lv_color_hex(0x94a3b8), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->main_label_nh3_title, &lv_font_SourceHanSerifSC_Regular_12, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->main_label_nh3_title, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->main_label_nh3_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->main_label_nh3_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->main_label_nh3_title, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->main_label_nh3_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->main_label_nh3_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->main_label_nh3_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->main_label_nh3_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->main_label_nh3_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->main_label_nh3_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes main_img_nh3
    ui->main_img_nh3 = lv_img_create(ui->main_cont_nh3);
    lv_obj_add_flag(ui->main_img_nh3, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->main_img_nh3, &_nh3_alpha_32x32);
    lv_img_set_pivot(ui->main_img_nh3, 16,16);
    lv_img_set_angle(ui->main_img_nh3, 0);
    lv_obj_set_pos(ui->main_img_nh3, 36, 8);
    lv_obj_set_size(ui->main_img_nh3, 32, 32);

    //Write style for main_img_nh3, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->main_img_nh3, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_recolor(ui->main_img_nh3, lv_color_hex(0xfbbf24), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->main_img_nh3, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->main_img_nh3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->main_img_nh3, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes main_cont_voc
    ui->main_cont_voc = lv_obj_create(ui->main_cont_main);
    lv_obj_set_pos(ui->main_cont_voc, 10, 345);
    lv_obj_set_size(ui->main_cont_voc, 105, 105);
    lv_obj_set_scrollbar_mode(ui->main_cont_voc, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui->main_cont_voc, LV_OBJ_FLAG_CLICK_FOCUSABLE);

    //Write style for main_cont_voc, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->main_cont_voc, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->main_cont_voc, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->main_cont_voc, lv_color_hex(0x1E293B), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->main_cont_voc, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->main_cont_voc, 10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->main_cont_voc, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->main_cont_voc, lv_color_hex(0x1E293B), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->main_cont_voc, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->main_cont_voc, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->main_cont_voc, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->main_cont_voc, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->main_cont_voc, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->main_cont_voc, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes main_label_voc_val
    ui->main_label_voc_val = lv_label_create(ui->main_cont_voc);
    lv_label_set_text(ui->main_label_voc_val, "0");
    lv_label_set_long_mode(ui->main_label_voc_val, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->main_label_voc_val, 0, 68);
    lv_obj_set_size(ui->main_label_voc_val, 105, 26);

    //Write style for main_label_voc_val, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->main_label_voc_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->main_label_voc_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->main_label_voc_val, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->main_label_voc_val, &lv_font_montserratMedium_26, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->main_label_voc_val, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->main_label_voc_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->main_label_voc_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->main_label_voc_val, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->main_label_voc_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->main_label_voc_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->main_label_voc_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->main_label_voc_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->main_label_voc_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->main_label_voc_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes main_label_voc_title
    ui->main_label_voc_title = lv_label_create(ui->main_cont_voc);
    lv_label_set_text(ui->main_label_voc_title, "VOC 指数");
    lv_label_set_long_mode(ui->main_label_voc_title, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->main_label_voc_title, 0, 45);
    lv_obj_set_size(ui->main_label_voc_title, 105, 14);

    //Write style for main_label_voc_title, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->main_label_voc_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->main_label_voc_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->main_label_voc_title, lv_color_hex(0x94a3b8), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->main_label_voc_title, &lv_font_SourceHanSerifSC_Regular_12, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->main_label_voc_title, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->main_label_voc_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->main_label_voc_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->main_label_voc_title, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->main_label_voc_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->main_label_voc_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->main_label_voc_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->main_label_voc_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->main_label_voc_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->main_label_voc_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes main_img_voc
    ui->main_img_voc = lv_img_create(ui->main_cont_voc);
    lv_obj_add_flag(ui->main_img_voc, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->main_img_voc, &_voc_alpha_32x32);
    lv_img_set_pivot(ui->main_img_voc, 16,16);
    lv_img_set_angle(ui->main_img_voc, 0);
    lv_obj_set_pos(ui->main_img_voc, 36, 8);
    lv_obj_set_size(ui->main_img_voc, 32, 32);

    //Write style for main_img_voc, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->main_img_voc, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_recolor(ui->main_img_voc, lv_color_hex(0xa82ffc), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->main_img_voc, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->main_img_voc, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->main_img_voc, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes main_cont_nox
    ui->main_cont_nox = lv_obj_create(ui->main_cont_main);
    lv_obj_set_pos(ui->main_cont_nox, 125, 345);
    lv_obj_set_size(ui->main_cont_nox, 105, 105);
    lv_obj_set_scrollbar_mode(ui->main_cont_nox, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui->main_cont_nox, LV_OBJ_FLAG_CLICK_FOCUSABLE);

    //Write style for main_cont_nox, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->main_cont_nox, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->main_cont_nox, 10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->main_cont_nox, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->main_cont_nox, lv_color_hex(0x1E293B), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->main_cont_nox, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->main_cont_nox, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->main_cont_nox, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->main_cont_nox, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->main_cont_nox, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->main_cont_nox, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes main_label_nox_val
    ui->main_label_nox_val = lv_label_create(ui->main_cont_nox);
    lv_label_set_text(ui->main_label_nox_val, "0");
    lv_label_set_long_mode(ui->main_label_nox_val, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->main_label_nox_val, 0, 68);
    lv_obj_set_size(ui->main_label_nox_val, 105, 26);

    //Write style for main_label_nox_val, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->main_label_nox_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->main_label_nox_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->main_label_nox_val, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->main_label_nox_val, &lv_font_montserratMedium_26, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->main_label_nox_val, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->main_label_nox_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->main_label_nox_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->main_label_nox_val, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->main_label_nox_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->main_label_nox_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->main_label_nox_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->main_label_nox_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->main_label_nox_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->main_label_nox_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes main_label_nox_title
    ui->main_label_nox_title = lv_label_create(ui->main_cont_nox);
    lv_label_set_text(ui->main_label_nox_title, "NOx 指数");
    lv_label_set_long_mode(ui->main_label_nox_title, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->main_label_nox_title, 0, 45);
    lv_obj_set_size(ui->main_label_nox_title, 105, 14);

    //Write style for main_label_nox_title, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->main_label_nox_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->main_label_nox_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->main_label_nox_title, lv_color_hex(0x94a3b8), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->main_label_nox_title, &lv_font_SourceHanSerifSC_Regular_12, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->main_label_nox_title, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->main_label_nox_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->main_label_nox_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->main_label_nox_title, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->main_label_nox_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->main_label_nox_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->main_label_nox_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->main_label_nox_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->main_label_nox_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->main_label_nox_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes main_img_nox
    ui->main_img_nox = lv_img_create(ui->main_cont_nox);
    lv_obj_add_flag(ui->main_img_nox, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->main_img_nox, &_nox_alpha_32x32);
    lv_img_set_pivot(ui->main_img_nox, 16,16);
    lv_img_set_angle(ui->main_img_nox, 0);
    lv_obj_set_pos(ui->main_img_nox, 36, 8);
    lv_obj_set_size(ui->main_img_nox, 32, 32);

    //Write style for main_img_nox, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->main_img_nox, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_recolor(ui->main_img_nox, lv_color_hex(0xf73859), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->main_img_nox, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->main_img_nox, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->main_img_nox, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes main_cont_co
    ui->main_cont_co = lv_obj_create(ui->main_cont_main);
    lv_obj_set_pos(ui->main_cont_co, 10, 460);
    lv_obj_set_size(ui->main_cont_co, 220, 105);
    lv_obj_set_scrollbar_mode(ui->main_cont_co, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui->main_cont_co, LV_OBJ_FLAG_CLICK_FOCUSABLE);

    //Write style for main_cont_co, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->main_cont_co, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->main_cont_co, 10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->main_cont_co, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->main_cont_co, lv_color_hex(0x1E293B), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->main_cont_co, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->main_cont_co, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->main_cont_co, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->main_cont_co, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->main_cont_co, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->main_cont_co, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes main_label_co_val
    ui->main_label_co_val = lv_label_create(ui->main_cont_co);
    lv_label_set_text(ui->main_label_co_val, "0.00");
    lv_label_set_long_mode(ui->main_label_co_val, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->main_label_co_val, 0, 68);
    lv_obj_set_size(ui->main_label_co_val, 220, 26);

    //Write style for main_label_co_val, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->main_label_co_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->main_label_co_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->main_label_co_val, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->main_label_co_val, &lv_font_montserratMedium_26, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->main_label_co_val, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->main_label_co_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->main_label_co_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->main_label_co_val, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->main_label_co_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->main_label_co_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->main_label_co_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->main_label_co_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->main_label_co_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->main_label_co_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes main_label_co_title
    ui->main_label_co_title = lv_label_create(ui->main_cont_co);
    lv_label_set_text(ui->main_label_co_title, "一氧化碳 (ppm)");
    lv_label_set_long_mode(ui->main_label_co_title, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->main_label_co_title, 0, 45);
    lv_obj_set_size(ui->main_label_co_title, 220, 16);

    //Write style for main_label_co_title, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->main_label_co_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->main_label_co_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->main_label_co_title, lv_color_hex(0x94a3b8), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->main_label_co_title, &lv_font_SourceHanSerifSC_Regular_12, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->main_label_co_title, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->main_label_co_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->main_label_co_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->main_label_co_title, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->main_label_co_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->main_label_co_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->main_label_co_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->main_label_co_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->main_label_co_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->main_label_co_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes main_img_co
    ui->main_img_co = lv_img_create(ui->main_cont_co);
    lv_obj_add_flag(ui->main_img_co, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->main_img_co, &_co_alpha_32x32);
    lv_img_set_pivot(ui->main_img_co, 16,16);
    lv_img_set_angle(ui->main_img_co, 0);
    lv_obj_set_pos(ui->main_img_co, 94, 8);
    lv_obj_set_size(ui->main_img_co, 32, 32);

    //Write style for main_img_co, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->main_img_co, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_recolor(ui->main_img_co, lv_color_hex(0xFF6F00), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->main_img_co, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->main_img_co, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->main_img_co, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes main_cont_bat
    ui->main_cont_bat = lv_obj_create(ui->main_cont_main);
    lv_obj_set_pos(ui->main_cont_bat, 10, 575);
    lv_obj_set_size(ui->main_cont_bat, 220, 36);
    lv_obj_set_scrollbar_mode(ui->main_cont_bat, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui->main_cont_bat, LV_OBJ_FLAG_CLICK_FOCUSABLE);

    //Write style for main_cont_bat, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->main_cont_bat, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->main_cont_bat, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->main_cont_bat, lv_color_hex(0x1E293B), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->main_cont_bat, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->main_cont_bat, 10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->main_cont_bat, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->main_cont_bat, lv_color_hex(0x1E293B), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->main_cont_bat, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->main_cont_bat, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->main_cont_bat, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->main_cont_bat, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->main_cont_bat, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->main_cont_bat, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes main_label_bat_val
    ui->main_label_bat_val = lv_label_create(ui->main_cont_bat);
    lv_label_set_text(ui->main_label_bat_val, "100%");
    lv_label_set_long_mode(ui->main_label_bat_val, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->main_label_bat_val, 145, 11);
    lv_obj_set_size(ui->main_label_bat_val, 64, 16);

    //Write style for main_label_bat_val, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->main_label_bat_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->main_label_bat_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->main_label_bat_val, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->main_label_bat_val, &lv_font_SourceHanSerifSC_Regular_12, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->main_label_bat_val, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->main_label_bat_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->main_label_bat_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->main_label_bat_val, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->main_label_bat_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->main_label_bat_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->main_label_bat_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->main_label_bat_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->main_label_bat_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->main_label_bat_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes main_label_bat_title
    ui->main_label_bat_title = lv_label_create(ui->main_cont_bat);
    lv_label_set_text(ui->main_label_bat_title, "电池电量");
    lv_label_set_long_mode(ui->main_label_bat_title, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->main_label_bat_title, 34, 11);
    lv_obj_set_size(ui->main_label_bat_title, 100, 16);

    //Write style for main_label_bat_title, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->main_label_bat_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->main_label_bat_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->main_label_bat_title, lv_color_hex(0x94a3b8), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->main_label_bat_title, &lv_font_SourceHanSerifSC_Regular_12, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->main_label_bat_title, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->main_label_bat_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->main_label_bat_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->main_label_bat_title, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->main_label_bat_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->main_label_bat_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->main_label_bat_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->main_label_bat_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->main_label_bat_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->main_label_bat_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes main_img_bat
    ui->main_img_bat = lv_img_create(ui->main_cont_bat);
    lv_obj_add_flag(ui->main_img_bat, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->main_img_bat, &_battery_alpha_16x16);
    lv_img_set_pivot(ui->main_img_bat, 16,16);
    lv_img_set_angle(ui->main_img_bat, 0);
    lv_obj_set_pos(ui->main_img_bat, 12, 10);
    lv_obj_set_size(ui->main_img_bat, 16, 16);

    //Write style for main_img_bat, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->main_img_bat, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_recolor(ui->main_img_bat, lv_color_hex(0xafffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->main_img_bat, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->main_img_bat, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->main_img_bat, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //The custom code of main.


    //Update current screen layout.
    lv_obj_update_layout(ui->main);

}
