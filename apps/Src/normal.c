//
// Created by 14419 on 25-8-22.
#include "normal.h"

static void drawDate();
static display_t draw();
static display_t ticker();
static void drawTickerNum(tickerData_t* data);




extern timeDate_s timeDate; // 定义时间结构体
// extern const uint8_t small2Font[][22];
// extern const uint8_t midFont[][57];
// extern const uint8_t colon[];
uint32_t milliseconds;


void watchface_normal()
{
    display_setDrawFunc(draw);
}

/**
 * @brief 表盘的核心绘制逻辑
 * @return 绘制是否完成
 */
static display_t draw()
{

    /*一、绘制日期*/
    drawDate();
    ticker();
    drawBattery();
    // display_t busy = ticker();
    /*二、数字滚动动画*/

    // display_t busy = ticker();


    return DISPLAY_DONE;
}

/**
 * @brief 绘制日期字符串
 */
static void drawDate()
{
    // 星期几
    char day[BUFFSIZE_STR_DAYS];
    //strcpy(day, days[timeDate.date.day]);
    strcpy(day, "Fri");
    // Get month string 月份字符串
    char month[BUFFSIZE_STR_MONTHS];
    // strcpy(month, months[timeDate.date.month]);
    strcpy(month, "Aug");
    // 准备最终显示字符串
    char buff[BUFFSIZE_DATE_FORMAT];
    //sprintf(buff, PSTR(DATE_FORMAT), day, timeDate.date.date, month, timeDate.date.year);
    sprintf(buff, "%s %02u %s %04u", day, 22, month, 2025);
    draw_string(buff,false,12,0);
}

/**
 * @brief 数字滚动动画函数（ticker）
 * @return DISPLAY_BUSY: 动画进行中
 *         DISPLAY_DONE: 动画完成
 */
static display_t ticker() {

    // ---------- 静态变量，保持跨帧状态 ----------
    static uint8_t yPos;            // 小时/分钟滚动偏移
    static uint8_t yPos_secs;       // 秒滚动偏移
    static bool moving = false;  // 是否有数字正在滚动
    static bool moving2[5];      // 每个数字是否滚动，顺序：H十,H个,M十,M个,S十

    // 如果没有开启动画，直接静态显示
    yPos = 0;   // 小时/分钟滚动偏移
    yPos_secs = 0;  // 秒滚动偏移
    moving = false; // 无数字正在滚动
    memset(moving2, false, sizeof(moving2));    // 没有数字是否滚动

    // ---------- 绘制每个数字 ----------
    tickerData_t data;

    // 秒十位
    data.x = 104;
    data.y = 28;
    data.bitmap = (const uint8_t*)&small2Font;
    data.w = FONT_SMALL2_WIDTH;
    data.h = FONT_SMALL2_HEIGHT;
    data.offsetY = yPos_secs;        // 秒滚动偏移
    data.val = div10(timeDate.time.secs);
    data.maxVal = 5;
    data.moving = moving2[4];        // 是否滚动
    drawTickerNum(&data);

    // 秒个位
    data.x = 116;
    data.val = mod10(timeDate.time.secs);
    data.maxVal = 9;
    data.moving = moving;
    drawTickerNum(&data);

    // ---------- 小时和分钟使用大字体 ----------
    data.y = TIME_POS_Y;
    data.w = MIDFONT_WIDTH;
    data.h = MIDFONT_HEIGHT;
    data.bitmap = (const uint8_t*)&midFont;
    data.offsetY = yPos;

    // 分钟十位
    data.x = 60;
    data.val = div10(timeDate.time.mins);
    data.maxVal = 5;
    data.moving = moving2[2];
    drawTickerNum(&data);

    // 分钟个位
    data.x = 83;
    data.val = mod10(timeDate.time.mins);
    data.maxVal = 9;
    data.moving = moving2[3];
    drawTickerNum(&data);

    // 小时十位
    data.x = 1;
    data.val = div10(timeDate.time.hour);
    data.maxVal = 5;
    data.moving = moving2[0];
    drawTickerNum(&data);

    // 小时个位
    data.x = 24;
    data.val = mod10(timeDate.time.hour);
    data.maxVal = 9;
    data.moving = moving2[1];
    drawTickerNum(&data);

    // ---------- 绘制冒号，每半秒闪烁 ----------
    if(milliseconds % 3600 > 1800)
        draw_bitmap(TIME_POS_X + 46 + 2, TIME_POS_Y, colon,
                    FONT_COLON_WIDTH, FONT_COLON_HEIGHT, NOINVERT, 0);

    // ---------- 绘制 AM/PM ----------
    char tmp[2];
    tmp[0] = timeDate.time.ampm;
    tmp[1] = 0x00;
    draw_string(tmp, false, 104, 20);

    // ---------- 返回动画状态 ----------
    return (moving ? DISPLAY_BUSY : DISPLAY_DONE);
}


/**
 * @brief 绘制数字翻牌（无动画版本）
 * @param data tickerData_t* 指向数字显示参数
 */
static void drawTickerNum(tickerData_t* data)
{
    // 每个数字图像所占用的字节数
    uint8_t arraySize = (data->w * data->h) / 8;

    // 找到当前数字对应的位图
    const uint8_t* bitmap = &data->bitmap[data->val * arraySize];

    // 绘制位置
    uint8_t x = data->x;
    uint8_t y = data->y;

    // 直接绘制当前数字，不再考虑滚动
    draw_bitmap(x, y, bitmap, data->w, data->h, NOINVERT, 0);
}



