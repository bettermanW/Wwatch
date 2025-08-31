//
// Created by 14419 on 25-8-30.
//
#include "time_sys.h"

#define BUFFSIZE_TIME_FORMAT_SMALL		9

extern  timeDate_s timeDate;
char* time_timeStr()
{
    static char buff[BUFFSIZE_TIME_FORMAT_SMALL];
    sprintf(buff, "%02d:%02d%c", timeDate.time.hour, timeDate.time.mins, timeDate.time.ampm);
    return buff;
}