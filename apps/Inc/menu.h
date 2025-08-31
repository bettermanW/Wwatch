//
// Created by 14419 on 25-8-23.
//

#ifndef MENU_H
#define MENU_H
#include "stm32f1xx_hal.h"
#include "stm32f1xx_hal_uart.h"
#include "string.h"
#include "usart.h"
#include "string.h"
#include "stdio.h"

#include "m_main.h"
#include "draw.h"
#include "resourse.h"
#include "display.h"
#include "animation.h"
#include "appconfig.h"
// max number of items to show on screen (can have more, but they won't be shown)
//一次可显示的菜单项数量。
#define MAX_MENU_ITEMS 7

#include "stdbool.h"
#include "typedef.h"
#include <stddef.h>
bool menu_isOpen(void);
bool menu_select(void);
display_t menu_draw();


bool menu_down(void);
bool menu_up(void);
void menu_close(void);

display_t menu_draw();
void setMenuInfo(const uint8_t optionCount, const menu_type_t menuType, const char* title);
void setMenuFuncs(const menu_f btn1Func, const menu_f btn2Func, const menu_f btn3Func, const itemLoader_f loader);
void setPrevMenuOpen(prev_menu_s* prevMenu, const menu_f newPrevMenu);
void setPrevMenuExit(prev_menu_s* prevMenu);
void doAction(bool anim);
void setMenuOption(const uint8_t num, const char* name, const uint8_t* icon, const menu_f actionFunc);
void nextOption();
void prevOption();
void back();
void addBackOption();
bool exitSelected();
void beginAnimation(menu_f onComplete);
void beginAnimation2(menu_f onComplete);
#endif //MENU_H
