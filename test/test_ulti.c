//
// Created by 14419 on 25-8-13.
//
#include "test.h"




// void test_ulti(void) {
//     // 计算0-9的累加和
//     uint32_t res = 0;
//     LOOP(10, i) {
//         res += i;  // 0+1+2+...+9 = 45
//     }
//     LOOPR(res, i) {
//         res = i;
//     }
//     // 直接通过串口输出结果
//     char buf[16];  // 足够存放"res=45\n"
//     uint8_t len = snprintf(buf, sizeof(buf), "res=%lu\n", res);
//     HAL_UART_Transmit(&huart2, (uint8_t*)buf, len, HAL_MAX_DELAY);
// }

