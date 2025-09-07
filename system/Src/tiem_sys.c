//
// Created by 14419 on 25-8-30.
//
#include "time_sys.h"

#define BUFFSIZE_TIME_FORMAT_SMALL		9

extern  timeDate_s timeDate;
char* time_timeStr()
{
    struct tm* now;
    static char buff[BUFFSIZE_TIME_FORMAT_SMALL];
    sprintf(buff, "%02d:%02d%c", now->tm_hour, now->tm_sec, 'A');
    return buff;
}