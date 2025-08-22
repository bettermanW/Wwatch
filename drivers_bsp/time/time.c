//
// Created by 14419 on 25-8-22.
//

#include "time.h"
timeDate_s timeDate;
/**
 * @brief 初始化函数
 */
void time_init()
{
    timeDate.date.year  = 25;  // 初始年份2000-25=1975?
    timeDate.date.month = (month_t)8;  // 9月
    timeDate.date.day   = DAY_FRI;  // 星期二
    timeDate.date.date  = 22;  // 12日
    timeDate.time.ampm = ' ';  // 24小时制
}