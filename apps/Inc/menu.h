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
// max number of items to show on screen (can have more, but they won't be shown)
//一次可显示的菜单项数量。
#define MAX_MENU_ITEMS 7

#include "stdbool.h"
#include "typedef.h"
#include <stddef.h>
bool menu_isOpen(void);
bool menu_select(void);
void test_menu_draw(void);
display_t menu_draw();
void menu_setup_and_open(void);
#endif //MENU_H
