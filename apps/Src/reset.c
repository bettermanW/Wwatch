//
// Created by 14419 on 25-8-31.
//
#include "reset.h"
extern appconfig_s ;
extern menu_s menuData;
#define OPTION_COUNT	1

// 标记是否确认复位，初始为 `false`。
static bool reset_flag = false;

static prev_menu_s prevMenuData;

static void mSelect(void);
static void itemLoader();
static display_t mDraw(void);
static void setReset(void);

void mResetOpen(void)
{
    setMenuInfo(OPTION_COUNT, MENU_TYPE_ICON, (STR_RESETMENU));
    setMenuFuncs(nextOption, prevOption, mSelect, itemLoader);
    menuData.func.draw = mDraw;

    setPrevMenuOpen(&prevMenuData, mResetOpen);

    beginAnimation2(NULL);
}

static void mSelect(void)
{
    bool isExiting = exitSelected();
    if(isExiting && reset_flag)
    {
        appconfig_reset();
        HAL_NVIC_SystemReset(); // RestartMCU 硬件复位。
    }
	
    setPrevMenuExit(&prevMenuData);
    doAction(isExiting);
}

static void itemLoader()
{

    setMenuOption(0, (STR_RESET), menu_rotate, setReset);

    addBackOption();
}

static display_t mDraw(void)
{
    if(menuData.selected == 0)
    {
        char buff[2];		
        sprintf(buff, reset_flag ? ("Y") : ("N"));
		
        draw_string(buff, NOINVERT, 61, 30);
    }
	
    return DISPLAY_DONE;
}

static void setReset(void)
{
    reset_flag = !reset_flag;
}