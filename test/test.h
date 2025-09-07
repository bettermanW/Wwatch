//
// Created by 14419 on 25-8-13.
//

#ifndef OLED_TEST_H
#define OLED_TEST_H
#include "stm32f1xx_hal.h"
#include "stm32f1xx_hal_uart.h"
#include "usart.h"
//#include "ulti.h"
// #include <stdio.h>
// #include "draw.h"
// #include "usart.h"
// #include "display.h"
//#include "watchface.h"
#include "stdint.h"

void test_oled(void);

void test_ulti();

void test_bitmap_functions(void);

void ShowSmileyDemo();

 void draw_smiley_example();

void test_update1();

void test_watchface(void);

void test_draw_string(void);

void test_key();


#endif //OLED_TEST_H
