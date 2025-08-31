//
// Created by 14419 on 25-8-30.
//
#define OPTION_COUNT	getItemCount()
#include "games.h"
static prev_menu_s prevMenuData;

static void mSelect(void);
static void itemLoader(uint8_t num);

static uint8_t getItemCount()
{
    uint8_t cnt = 0;
#if COMPILE_GAME1
    ++cnt;
#endif
#if COMPILE_GAME2
    ++cnt;
#endif
#if COMPILE_GAME3
    ++cnt;
#endif
    return cnt;
}

void mGamesOpen()
{
    setMenuInfo(OPTION_COUNT, MENU_TYPE_STR, (STR_GAMESMENU));
    setMenuFuncs(nextOption,prevOption, mSelect,  itemLoader);

    setPrevMenuOpen(&prevMenuData, mGamesOpen);

    beginAnimation2(NULL);
}

static void mSelect()
{
    setPrevMenuExit(&prevMenuData);
    doAction(true);
}

static void itemLoader(uint8_t num)
{
    num = 0;
#if COMPILE_GAME1
    setMenuOption(num++, (STR_GAME1), NULL, game1_start );
#endif
#if COMPILE_GAME2
    setMenuOption(num++, (STR_GAME2), NULL, NULL);
#endif
#if COMPILE_GAME3
    setMenuOption(num++, (STR_GAME3), NULL, NULL);
#endif
    addBackOption();
}