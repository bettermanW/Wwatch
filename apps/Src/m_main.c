//
// Created by 14419 on 25-8-26.
//
#include "m_main.h"

#define OPTION_COUNT getItemCount() // 动态计算（根据编译时开关，例如是否启用了游戏、秒表、手电筒等功能）。

// 用于保存“上一个菜单”的信息，方便退出/返回时恢复。
static prev_menu_s prevMenuData;

static void mOpen(void);
static void mSelect(void);
static void itemLoader(uint8_t);

static uint8_t getItemCount()
{
    uint8_t cnt = 2; // 固定有 "Settings" 和 "Exit" 两个
#if COMPILE_GAME1 || COMPILE_GAME2 || COMPILE_GAME3
    ++cnt;
#endif
#if COMPILE_STOPWATCH
    ++cnt;
#endif
#if COMPILE_TORCH
    ++cnt;
#endif
#if COMPILE_BTRCCAR
    ++cnt;
#endif
#if COMPILE_TUNEMAKER
    ++cnt;
#endif
    return cnt;
}


/**
 * @brief 主菜单入口函数（外部调用时进入主菜单）
 */
void mMainOpen() {
    // 设置按键响应：此时只有“确认键”有效
    // 启动动画，动画完成后会调用
    buttons_setFuncs(NULL, NULL, menu_select);
    mOpen();
}

/**
 * @brief 初始化并显示主菜单界面
 */
static void mOpen()
{
    display_setDrawFunc(menu_draw);

    buttons_setFuncs(menu_up,  menu_down, menu_select);

    setMenuInfo(OPTION_COUNT, MENU_TYPE_ICON, (STR_MAINMENU));

    setMenuFuncs(nextOption, prevOption,mSelect,  itemLoader);

    // 保存当前菜单状态到 `prevMenuData`，方便后续退出返回
    setPrevMenuOpen(&prevMenuData, mOpen);

    // beginAnimation2(NULL);
}

/**
 * @brief 执行当前选中菜单项的动作
 */
static void mSelect()
{
    // 标记退出当前菜单时应恢复的状态
    setPrevMenuExit(&prevMenuData);
    // 执行菜单选项绑定的回调函数（例如进入“秒表界面”、“设置界面”）。
    doAction(true);
}

/**
 * @brief 按编号加载每个菜单项
 * @param num
 */
static void itemLoader(uint8_t num)
{
    num = 0;
    setMenuOption(num++, STR_ALARMS, menu_alarm, NULL);
#if COMPILE_TORCH
    setMenuOption(num++, STR_FLASHLIGHT, menu_torch, torch_open);
#endif
#if COMPILE_STOPWATCH
    setMenuOption(num++, (STR_STOPWATCH), menu_stopwatch, stopwatch_open);
#endif
#if COMPILE_BTRCCAR
    setMenuOption(num++, (STR_BTRCCAR), menu_stopwatch, btrccar_open);
#endif
#if COMPILE_TUNEMAKER
    setMenuOption(num++, (STR_TUNEMAKER), menu_tunemaker, NULL);
#endif
#if COMPILE_GAME1 || COMPILE_GAME2 || COMPILE_GAME3
    setMenuOption(num++, (STR_GAMES), menu_games, NULL);
#endif

    setMenuOption(num++, (STR_SETTINGS), menu_settings, mSettingsOpen);
    setMenuOption(OPTION_COUNT, (STR_EXIT), menu_exit, menu_close);
}