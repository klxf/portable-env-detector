#ifndef __SETTINGS_STORE_H
#define __SETTINGS_STORE_H

#include <stdint.h>

typedef struct {
    uint8_t brightness;
    uint8_t auto_screen_off;
} UserSettings;

void Settings_Store_Init(void);
uint8_t Settings_Store_Save(const UserSettings *settings);
void Settings_Store_Load(UserSettings *settings);

#endif
