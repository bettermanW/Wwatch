//
// Created by 14419 on 25-8-31.
//

#ifndef TUNE_H
#define TUNE_H
#include "typedef.h"
#include "buzzer.h"
#define PRIO_UI		PRIO_LOW
#define PRIO_ALARM	PRIO_HIGH
#define PRIO_HOUR	PRIO_NML

typedef void (*buzzFinish_f)(void);

#define buzzer_stop()	(buzzer_buzz(0, TONE_STOP, PRIO_MAX, NULL))

typedef uint32_t tune_t;

void tune_play(const tune_t*, vol_t, tonePrio_t);
void tune_stop(tonePrio_t);

#endif //TUNE_H
