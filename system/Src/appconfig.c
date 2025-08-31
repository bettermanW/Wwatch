
//
// Created by 14419 on 25-8-29.
//
#include "appconfig.h"
appconfig_s appConfig;
/**
 * @brief  从 EEPROM 读取，如果 EEPROM 未初始化，恢复默认值。
 */
void appconfig_init(void)
{
    uint16_t data16;
    EE_ReadVariable(EE_ADDR_SLEEP_TIMEOUT, &data16);
    if (data16 == 0xFFFF)   // EEPROM 未写入过
    {
        appconfig_reset();
        return;
    }

    appConfig.sleepTimeout = (uint8_t)data16;

    EE_ReadVariable(EE_ADDR_INVERT, &data16);
    appConfig.invert = (data16 != 0);

#if COMPILE_ANIMATIONS
    EE_ReadVariable(EE_ADDR_ANIMATIONS, &data16);
    appConfig.animations = (data16 != 0);
#endif

    EE_ReadVariable(EE_ADDR_DISPLAY180, &data16);
    appConfig.display180 = (data16 != 0);

    EE_ReadVariable(EE_ADDR_CTRL_LEDS, &data16);
    appConfig.CTRL_LEDs = (data16 != 0);

    EE_ReadVariable(EE_ADDR_SHOWFPS, &data16);
    appConfig.showFPS = (data16 != 0);

    EE_ReadVariable(EE_ADDR_TIMEMODE, &data16);
    appConfig.timeMode = (timemode_t)data16;

    EE_ReadVariable(EE_ADDR_VOLUMES, &data16);
    appConfig.volumes = (uint8_t)data16;
}

/**
 * @brief  每个字段单独写入 EEPROM（写多少，EEPROM 仿真会自动处理页切换和日志式更新）
 */
void appconfig_save(void)
{
    EE_WriteVariable(EE_ADDR_SLEEP_TIMEOUT, appConfig.sleepTimeout);
    EE_WriteVariable(EE_ADDR_INVERT, appConfig.invert ? 1 : 0);
#if COMPILE_ANIMATIONS
    EE_WriteVariable(EE_ADDR_ANIMATIONS, appConfig.animations ? 1 : 0);
#endif
    EE_WriteVariable(EE_ADDR_DISPLAY180, appConfig.display180 ? 1 : 0);
    EE_WriteVariable(EE_ADDR_CTRL_LEDS, appConfig.CTRL_LEDs ? 1 : 0);
    EE_WriteVariable(EE_ADDR_SHOWFPS, appConfig.showFPS ? 1 : 0);
    EE_WriteVariable(EE_ADDR_TIMEMODE, (uint16_t)appConfig.timeMode);
    EE_WriteVariable(EE_ADDR_VOLUMES, appConfig.volumes);
}

void appconfig_reset(void)
{
    appConfig.sleepTimeout = 1;
    appConfig.invert = false;
#if COMPILE_ANIMATIONS
    appConfig.animations = true;
#endif
    appConfig.display180 = false;
    appConfig.CTRL_LEDs = false;
    appConfig.showFPS = false;
    appConfig.timeMode = TIMEMODE_24HR;
    appConfig.volumes = 255;  // 默认最大音量、亮度 3 已经包含在 union 中
    appConfig.brightness = 3;
    appconfig_save();

    // alarm_reset();
}
