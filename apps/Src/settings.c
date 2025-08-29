

#include "settings.h"

// 定义菜单项总数（5 个）
/*
    1. 时间日期 (Time & Date)
    2. 休眠 (Sleep)
    3. 声音 (Sound)
    4. 显示 (Display)
    5.  (Diagnostics)
 */
#define OPTION_COUNT	5

static prev_menu_s prevMenuData; // 上一个菜单的信息

static void mSelect(void); // 用户按下确认键时执行（进入子菜单）
static void itemLoader(); // 负责把具体的菜单项加载到菜单系统中

/**
 * @brief
 */
void mSettingsOpen()
{
    setMenuInfo(OPTION_COUNT, MENU_TYPE_ICON, STR_SETTINGSMENU);
    // 设置菜单的行为函数
    setMenuFuncs(nextOption, mSelect, prevOption, itemLoader);
    // 把当前菜单保存到, 供返回上级菜单时使用
    setPrevMenuOpen(&prevMenuData, mSettingsOpen);

    // beginAnimation2(NULL);
}

/**
 * @brief
 */
static void mSelect()
{
    // 记录退出时的菜单状态，保证返回时恢复正确
    setPrevMenuExit(&prevMenuData);
    // 执行当前选中菜单项的动作
    doAction(true);
}

static void itemLoader()
{
    // 设置每一个菜单项
    setMenuOption(0, STR_TIMEDATE, menu_timedate, mTimeDateOpen);
    setMenuOption(1, STR_SLEEP, menu_sleep, mSleepOpen);    //这里有bug！！！  可以再增加一个图标就可以解决
    setMenuOption(2, STR_SOUND, menu_sound, mSoundOpen);
    setMenuOption(3, STR_DISPLAY, menu_display, mDisplayOpen);
    setMenuOption(4, STR_DIAGNOSTICS, menu_diagnostic, mDiagOpen);


    // 动加一个 **返回 (Back)** 菜单项，让用户能回到上级菜单
    addBackOption();
}
