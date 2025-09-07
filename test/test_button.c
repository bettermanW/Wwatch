//
// Created by 14419 on 25-8-20.
//
#include "test.h"
#include <string.h>
#include "usart.h"
// #include "button.h"

// void key1_callback(void) {
//     if (HAL_GPIO_ReadPin(KEY2_GPIO_Port,KEY2_Pin) == GPIO_PIN_RESET)
//     {
//         //软件消抖
//         HAL_Delay(10);
//         if (HAL_GPIO_ReadPin(KEY2_GPIO_Port,KEY2_Pin) == GPIO_PIN_RESET)
//         {
//             HAL_UART_Transmit(&huart2, (uint8_t *)"KEY1 pressed!\r\n", strlen("KEY1 pressed!\r\n"), 100);
//             //�?测到key2按下时，�?始死等知道key2松开
//             while (HAL_GPIO_ReadPin(KEY2_GPIO_Port,KEY2_Pin) == GPIO_PIN_RESET){}
//         }
//
//
//     }
//
// }
//
// void key2_callback(void) {
//     if (HAL_GPIO_ReadPin(KEY2_GPIO_Port,KEY2_Pin) == GPIO_PIN_RESET)
//     {
//         //软件消抖
//         HAL_Delay(10);
//         if (HAL_GPIO_ReadPin(KEY2_GPIO_Port,KEY2_Pin) == GPIO_PIN_RESET)
//         {
//             HAL_UART_Transmit(&huart2, (uint8_t *)"KEY2 pressed!\r\n", strlen("KEY2 pressed!\r\n"), 100);
//             //�?测到key2按下时，�?始死等知道key2松开
//             while (HAL_GPIO_ReadPin(KEY2_GPIO_Port,KEY2_Pin) == GPIO_PIN_RESET){}
//         }
//
//
//     }
// }
//
// void key3_callback(void) {
//
// }

// void test_key() {
//     // 单个按钮设置回调
//     buttons_setFunc(BTN_1, key1_callback);
//
//     // 同时设置三个按钮
//     //buttons_setFuncs(key1_callback, key2_callback, key3_callback);
// }

// bool btn_up_callback() {
//     HAL_UART_Transmit(&huart2, (uint8_t*)"KEY1", 5, HAL_MAX_DELAY);
//     return true;
// }
//
// bool btn_down_callback() {
//     HAL_UART_Transmit(&huart2, (uint8_t*)"KEY2", 5, HAL_MAX_DELAY);
//     return true;
// }
//
// bool btn_ok_callback() {
//     HAL_UART_Transmit(&huart2, (uint8_t*)"KEY0", 5, HAL_MAX_DELAY);
//     return true;
// }
//
// void test_bitcount() {
//     buttons_setFuncs(btn_up_callback, btn_down_callback, btn_ok_callback);
//     buttons_update();
// }

