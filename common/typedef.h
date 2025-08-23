//
// Created by 14419 on 25-8-19.
//

#ifndef TYPEDEF_H
#define TYPEDEF_H
#include "stdint.h"
#include "stdbool.h"

#define BUFFSIZE_STR_DAYS	4
#define BUFFSIZE_STR_MONTHS	4
#define BUFFSIZE_DATE_FORMAT		((BUFFSIZE_STR_DAYS - 1) + (BUFFSIZE_STR_MONTHS - 1) + 12)
#define FONT_SMALL2_WIDTH 11
#define FONT_SMALL2_HEIGHT 16

#define NOINVERT false

#define FRAME_HEIGHT 64
#define FRAME_WIDTH 128

// 定义 12 个月份的索引（0-11），用于 date_s 结构中的 month 字段
typedef enum
{
    MONTH_JAN = 0,
    MONTH_FEB = 1,
    MONTH_MAR = 2,
    MONTH_APR = 3,
    MONTH_MAY = 4,
    MONTH_JUN = 5,
    MONTH_JUL = 6,
    MONTH_AUG = 7,
    MONTH_SEP = 8,
    MONTH_OCT = 9,
    MONTH_NOV = 10,
    MONTH_DEC = 11
} month_t;

// 定义一周 7 天的索引（0-6）
// 修改为与struct tm一致（0=星期日）
typedef enum {
    DAY_SUN = 0,  // 0 = 星期日
    DAY_MON = 1,  // 1 = 星期一
    DAY_TUE = 2,  // 2 = 星期二
    DAY_WED = 3,  // 3 = 星期三
    DAY_THU = 4,  // 4 = 星期四
    DAY_FRI = 5,  // 5 = 星期五
    DAY_SAT = 6,  // 6 = 星期六
} day_t;

// 存储时间信息，包括秒、分钟、小时和 AM/PM 指示
typedef struct {
    uint8_t secs;   // 秒 (0-59)
    uint8_t mins;   // 分钟 (0-59)
    uint8_t hour;   // 小时 (0-23)
    char ampm;      // AM/PM ('A' 或 'P') 12/24
}time_s;

// 存储日期信息，包括星期、日期、月份和年份
typedef struct {
    day_t day;      // 星期 (DAY_MON 到 DAY_SUN)
    uint8_t date;   // 日期 (1-31)
    month_t month;  // 月份 (MONTH_JAN 到 MONTH_DEC)
    uint8_t year;   // 年份后两位 (例如 25 表示 2025)
} date_s;

// 存储完整的当前时间和日期。
// 供 ticker 和 drawDate 函数使用，驱动时间和日期显示。
typedef struct {
    time_s time;    // 时间信息
    date_s date;    // 日期信息
} timeDate_s;

typedef struct
{
    uint8_t x;         // 横坐标
    uint8_t y;         // 纵坐标
    const uint8_t* bitmap; // 字体位图
    uint8_t w;         // 宽
    uint8_t h;         // 高
    uint8_t offsetY;   // 垂直偏移量，用于滚动
    uint8_t val;       // 当前显示数字
    uint8_t maxVal;    // 该位数字最大值，用于翻页
    bool moving;    // 是否正在滚动
} tickerData_t;


#endif //TYPEDEF_H
