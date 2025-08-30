//
// Created by 14419 on 25-8-30.
//

#ifndef BUZZER_H
#define BUZZER_H
#include "stm32f1xx_hal.h"
#include <stdbool.h>
#include "typedef.h"



typedef void (*buzzFinish_f)(void);



bool buzzer_buzzering();

void buzzer_buzz(uint32_t len, tone_t tone, tonePrio_t volType,
                 tonePrio_t _prio, buzzFinish_f _onFinish);

void buzzer_update();


#endif //BUZZER_H
