//
// Created by 14419 on 25-8-22.
//

#ifndef RESOURSE_H
#define RESOURSE_H

#include <stdint.h>
#include "draw.h"
#include "typedef.h"
#define SMALLFONT_WIDTH 5
#define SMALLFONT_HEIGHT 8
extern const uint8_t small2Font[][22];

#define MIDFONT_WIDTH 19
#define MIDFONT_HEIGHT 24
extern const uint8_t midFont[][57];

#define FONT_COLON_WIDTH 6
#define FONT_COLON_HEIGHT 24
extern const uint8_t colon[];

uint8_t div10(const uint8_t val);

uint8_t mod10(const uint8_t val);

extern const uint8_t battIconEmpty[];
extern const uint8_t battIconLow[];
extern const uint8_t battIconHigh[];
extern const uint8_t battIconFull[];

extern const char days[7][BUFFSIZE_STR_DAYS];
extern const char months[12][BUFFSIZE_STR_MONTHS];

extern const uint8_t selectbar_bottom[];
extern const uint8_t selectbar_top[];
extern const uint8_t menu_default[];

void drawBattery();

/*m_main*/
extern const uint8_t menu_alarm[];
extern const uint8_t menu_torch[];
extern const uint8_t menu_stopwatch[];
extern const uint8_t menu_tunemaker[];
extern const uint8_t menu_games[];
extern const uint8_t menu_settings[];
extern const uint8_t menu_exit[];

/* settings 界面*/
extern const uint8_t menu_timedate[];
extern const uint8_t menu_sleep[];
extern const uint8_t menu_sound[];
extern const uint8_t menu_display[];
extern const uint8_t menu_diagnostic[];
extern const uint8_t menu_rotate[];

extern const uint8_t menu_sleeptimeout[];



#endif //RESOURSE_H
