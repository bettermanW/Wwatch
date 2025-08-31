//
// Created by 14419 on 25-8-30.
//
//
// Created by 14419 on 25-8-30.
//
#include "sleep.h"

#define OPTION_COUNT	1
extern menu_s menuData;
static prev_menu_s prevMenuData;
extern appconfig_s appConfig;

static void mSelect(void);
static void itemLoader();
static display_t mDraw(void);
static void setTimeout(void);

void mSleepOpen()
{
    setMenuInfo(OPTION_COUNT, MENU_TYPE_ICON, STR_SLEEPMENU);
    setMenuFuncs(nextOption, prevOption, mSelect, itemLoader);
    menuData.func.draw = mDraw;
    // 保存上一级菜单信息，用于菜单返回时恢复
    setPrevMenuOpen(&prevMenuData, mSleepOpen);

    beginAnimation2(NULL);
}

static void mSelect()
{
    // 判断是否选中了退出项，保存配置
    bool isExiting = exitSelected();
    if(isExiting)
        appconfig_save();
    // 菜单退出时恢复状态
    setPrevMenuExit(&prevMenuData);
    doAction(isExiting);
}

static void itemLoader()
{
    setMenuOption(0, (STR_TIMEOUT), menu_sleeptimeout, setTimeout);

    addBackOption();
}

static display_t mDraw()
{
    // 如果当前选中的是第 0 项（Timeout）
    if(menuData.selected == 0)
    {
        char buff[4];
        sprintf(buff, "%02dS", (unsigned char)(appConfig.sleepTimeout * 5));
        draw_string(buff, NOINVERT, 56, 40);
    }
    return DISPLAY_DONE;
}

static void setTimeout()
{
    uint8_t timeout = appConfig.sleepTimeout;
    timeout++;
    if(timeout > 12)
        timeout = 0;
    appConfig.sleepTimeout = timeout;
}
