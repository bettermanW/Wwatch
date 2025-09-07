//
// Created by 14419 on 25-8-13.
//

#include "test.h"
//
// test_oled.c
// Created for testing OLED driver
//

#include "oled.h"


// 简单延时函数（如果在裸机上）
void delay_ms(uint32_t ms) {
    HAL_Delay(ms);
}

void test_oled(void) {

    // 3. 初始化 OLED
    OLED_Init();
    delay_ms(500);

    // 4. 清屏
    OLED_NewFrame();
    OLED_ShowFrame();
    delay_ms(500);

    // 5. 设置屏幕为反色
    OLED_SetColorMode(OLED_COLOR_REVERSED);
    OLED_ShowFrame();
    delay_ms(500);

    // 6. 设置一些像素
    OLED_NewFrame();
    for (uint8_t x = 0; x < 128; x += 4) {
        for (uint8_t y = 0; y < 64; y += 4) {
            OLED_SetPixel(x, y, OLED_COLOR_NORMAL);
        }
    }
    OLED_ShowFrame();
    delay_ms(2000);

    // 7. 恢复正常显示
    OLED_SetColorMode(OLED_COLOR_NORMAL);
    OLED_ShowFrame();

    // 8. 主循环（可选，不做任何操作）
    // while (1) {
    //     // 这里可以加闪烁或者其他测试
    // }
}


/*********************************** 测试用回调 ********************************************/

// 串口打印函数替代 printf
static void uartPrint(const char *msg) {
    HAL_UART_Transmit(&huart2, (uint8_t*)msg, strlen(msg), HAL_MAX_DELAY);
}


void onUp(void) {
    uartPrint("↑ 向上 (btn1)\r\n");
}

void onDown(void) {
    uartPrint("↓ 向下 (btn2)\r\n");
}

void onSelect(void) {
    uartPrint("✔ 确认 (btn3)\r\n");
}

// /*********************************** 测试主程序 ********************************************/
// void menu_test(void) {
//     char buf[64];
//
//     // 初始化菜单
//     menuData.isOpen = false;
//     menuData.title = "Main Menu";
//     menuData.func.btn1 = onUp;
//     menuData.func.btn2 = onDown;
//     menuData.func.btn3 = onSelect;
//
//     buttons_setFuncs(menu_up,menu_down,menu_select);
//
// }