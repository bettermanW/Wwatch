//
// Created by 14419 on 25-8-20.
//

#ifndef BUTTON_DRIVER_H
#define BUTTON_DRIVER_H
#include "stm32f1xx_hal.h"


// 低电平（0）按下
// #define KEY0   HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_12)  // 确认
#define KEY1   HAL_GPIO_ReadPin(GPIOB, KEY1_Pin)  // 上
#define KEY2   HAL_GPIO_ReadPin(GPIOB, KEY2_Pin)  // 下

#endif //BUTTON_DRIVER_H
