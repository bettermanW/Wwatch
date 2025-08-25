//
// Created by 14419 on 25-8-22.
//

#ifndef TIME_H
#define TIME_H
#include "typedef.h"
#include "stm32f1xx_hal.h"
#include "rtc.h"
#include <time.h>

void KK_RTC_Init();
struct tm *KK_RTC_GetTime();
HAL_StatusTypeDef KK_RTC_SetTime(struct tm *time);
#endif //TIME_H
