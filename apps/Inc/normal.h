//
// Created by 14419 on 25-8-22.
//

#ifndef NORMAL_H
#define NORMAL_H
#include "typedef.h"
#include "display.h"
#include "stdio.h"
#include "time.h"

#define BUFFSIZE_STR_DAYS	4
#define BUFFSIZE_STR_MONTHS	4
#define BUFFSIZE_DATE_FORMAT		((BUFFSIZE_STR_DAYS - 1) + (BUFFSIZE_STR_MONTHS - 1) + 12)

#define TIME_POS_X	1
#define TIME_POS_Y	20
#define TICKER_GAP	4

#define MIDFONT_WIDTH 19
#define MIDFONT_HEIGHT 24

#define FONT_COLON_WIDTH 6
#define FONT_COLON_HEIGHT 24

#define NOINVERT false

void watchface_normal();

#endif //NORMAL_H
