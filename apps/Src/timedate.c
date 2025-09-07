//
// Created by 14419 on 25-9-4.
//
#include "timedate.h"

#define OPTION_COUNT	1

static void mSelect(void);
static void itemLoader(uint8_t);
static prev_menu_s prevMenuData;

void mtimeDateOpen() {
    setMenuInfo(OPTION_COUNT, MENU_TYPE_ICON, (STR_TIMEDATE));
    setMenuFuncs(nextOption, prevOption, mSelect, itemLoader);

    setPrevMenuOpen(&prevMenuData, mDisplayOpen);

    beginAnimation2(NULL);
}

static void mSelect(void) {

}