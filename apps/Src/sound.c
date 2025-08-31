//
// Created by 14419 on 25-8-30.
//
#include "sound.h"
#define OPTION_COUNT		3
extern appconfig_s appConfig;
static prev_menu_s prevMenuData;
static void mSelect(void);
static void itemLoader();
static void setVolumeUI(void);
static void setVolumeAlarm(void);
static void setVolumeHour(void);
static uint8_t setVolume(uint8_t vol);
static void setMenuOptions(void);

void mSoundOpen()
{
    setMenuInfo(OPTION_COUNT, MENU_TYPE_ICON, (STR_SOUNDMENU));
    setMenuFuncs(nextOption, prevOption, mSelect, itemLoader);

    setMenuOptions();

    setPrevMenuOpen(&prevMenuData, mSoundOpen);

    // beginAnimation2(NULL);
}

static void mSelect()
{
    bool isExiting = exitSelected();
    if(isExiting)

        appconfig_save();

    setPrevMenuExit(&prevMenuData);

    doAction(isExiting);
}

static void itemLoader()
{
    //  调用`setMenuOptions`重新设置所有菜单选项的内容
    setMenuOptions();
    addBackOption();
}

static void setVolumeUI()
{

    appConfig.volUI = setVolume(appConfig.volUI);
}

static void setVolumeAlarm()
{

    appConfig.volAlarm = setVolume(appConfig.volAlarm);
}

static void setVolumeHour()
{

    appConfig.volHour = setVolume(appConfig.volHour);
}

static uint8_t setVolume(uint8_t vol)
{
    vol++;
    if(vol > 3)
        vol = 0;
    return vol;
}

static void setMenuOptions()
{
    setMenuOption(0, (STR_UI), menu_volume[appConfig.volUI], setVolumeUI);
    setMenuOption(1, (STR_ALARMS), menu_volume[appConfig.volAlarm], setVolumeAlarm);
    setMenuOption(2, (STR_HOURBEEPS), menu_volume[appConfig.volHour], setVolumeHour);
}
