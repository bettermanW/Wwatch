//
// Created by 14419 on 25-8-30.
//

#ifndef STOPWATCH_H
#define STOPWATCH_H
#include "config.h"
#include "stdbool.h"
#include "menu.h"
#include "time_sys.h"
#if COMPILE_STOPWATCH

void stopwatch_open(void);
bool stopwatch_active(void);
void stopwatch_update(void);

#endif
#endif //STOPWATCH_H
