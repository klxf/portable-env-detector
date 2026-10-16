#include "settings_store.h"
#include "ch32v30x.h"
#include "ch32v30x_flash.h"

#define SETTINGS_PAGE_OFFSET 0x00047F00u
#define SETTINGS_PAGE_ADDR   (FLASH_BASE + SETTINGS_PAGE_OFFSET)
#define SETTINGS_MAGIC       0x4A454431u

typedef struct {
    uint32_t magic;
    uint8_t brightness;
    uint8_t auto_screen_off;
    uint8_t reserved[2];
    uint32_t crc;
} StoredSettings;

static uint32_t crc32(const uint8_t *data, uint32_t length)
{
    uint32_t crc = 0xFFFFFFFFu;

    for(uint32_t i = 0; i < length; i++) {
        crc ^= data[i];
        for(uint8_t bit = 0; bit < 8; bit++) {
            if((crc & 1u) != 0u) {
                crc = (crc >> 1) ^ 0xEDB88320u;
            } else {
                crc >>= 1;
            }
        }
    }

    return ~crc;
}

static void read_settings(StoredSettings *settings)
{
    const uint32_t *source = (const uint32_t *)SETTINGS_PAGE_ADDR;
    uint32_t *target = (uint32_t *)settings;

    for(uint32_t i = 0; i < sizeof(StoredSettings) / sizeof(uint32_t); i++) {
        target[i] = source[i];
    }
}

static uint8_t write_settings(const StoredSettings *settings)
{
    FLASH_Unlock_Fast();
    FLASH_ErasePage_Fast(SETTINGS_PAGE_ADDR);

    for(uint32_t i = 0; i < sizeof(StoredSettings); i += 2) {
        uint16_t value = ((uint16_t)((const uint8_t *)settings)[i + 1] << 8) |
                         ((const uint8_t *)settings)[i];

        if(FLASH_ProgramHalfWord(SETTINGS_PAGE_ADDR + i, value) != FLASH_COMPLETE) {
            FLASH_Lock();
            return 1;
        }
    }

    FLASH_Lock_Fast();
    return 0;
}

void Settings_Store_Init(void)
{
    UserSettings defaults;
    StoredSettings stored;

    defaults.brightness = 80;
    defaults.auto_screen_off = 0;

    read_settings(&stored);
    if(stored.magic != SETTINGS_MAGIC ||
       stored.crc != crc32((const uint8_t *)&stored, sizeof(StoredSettings) - sizeof(uint32_t))) {
        Settings_Store_Save(&defaults);
    }
}

uint8_t Settings_Store_Save(const UserSettings *user_settings)
{
    StoredSettings stored;

    if(user_settings == 0) {
        return 1;
    }

    stored.magic = SETTINGS_MAGIC;
    stored.brightness = user_settings->brightness;
    if(stored.brightness < 10u) stored.brightness = 10u;
    if(stored.brightness > 100u) stored.brightness = 100u;
    stored.auto_screen_off = user_settings->auto_screen_off ? 1u : 0u;
    stored.reserved[0] = 0;
    stored.reserved[1] = 0;
    stored.crc = crc32((const uint8_t *)&stored, sizeof(StoredSettings) - sizeof(uint32_t));

    return write_settings(&stored);
}

void Settings_Store_Load(UserSettings *user_settings)
{
    StoredSettings stored;

    if(user_settings == 0) {
        return;
    }

    user_settings->brightness = 80;
    user_settings->auto_screen_off = 0;

    read_settings(&stored);
    if(stored.magic != SETTINGS_MAGIC ||
       stored.crc != crc32((const uint8_t *)&stored, sizeof(StoredSettings) - sizeof(uint32_t))) {
        return;
    }

    if(stored.brightness < 10u) stored.brightness = 10u;
    if(stored.brightness > 100u) stored.brightness = 100u;
    stored.auto_screen_off = stored.auto_screen_off ? 1u : 0u;

    user_settings->brightness = stored.brightness;
    user_settings->auto_screen_off = stored.auto_screen_off;
}
