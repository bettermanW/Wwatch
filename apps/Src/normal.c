//
// Created by 14419 on 25-8-22.
#include "normal.h"

#include "kk_time.h"

static void drawDate(struct tm* now);
static display_t draw();
static display_t ticker(struct tm* now);
static void drawTickerNum(tickerData_t* data);




extern appconfig_s appConfig;





static bool down()
{
    // Set watchface切换到 `watchfaceOpen` 这个显示逻辑
    display_set(watchfaceOpen);
    display_load();

    return true;
}

static bool up()
{
    // Set watchface切换到 `watchfaceOpen` 这个显示逻辑
    display_set(watchfaceOpen);
    display_load();

    return true;
}

void watchface_normal()
{
    // 当前界面绘制函数， 指定这个界面的绘制逻辑
    display_setDrawFunc(draw);
    // 绑定按键处理函数。
    buttons_setFuncs(up, down, menu_select);
    animation_start(NULL, ANIM_MOVE_ON);
}

/**
 * @brief 表盘的核心绘制逻辑
 * @return 绘制是否完成
 */
static display_t draw()
{

    struct  tm* now = KK_RTC_GetTime();
    /*一、绘制日期*/
    drawDate(now);
    ticker(now);
    drawBattery();
    // display_t busy = ticker();
    /*二、数字滚动动画*/

    // display_t busy = ticker();


    return DISPLAY_DONE;
}

/**
 * @brief 绘制日期字符串
 */
static void drawDate(struct tm* now)
{

    // 星期几
    char wday[BUFFSIZE_STR_DAYS];
    strcpy(wday, days[now->tm_wday]);

    // Get month string 月份字符串
    char month[BUFFSIZE_STR_MONTHS];
    strcpy(month, months[now->tm_mon]);

    // 准备最终显示字符串
    char buff[BUFFSIZE_DATE_FORMAT];
    sprintf(buff, "%s %02d %s %04d", wday, now->tm_mday, month, now->tm_year + 1900);
    draw_string(buff,false,12,0);
}

/**
 * @brief 数字滚动动画函数（ticker）
 * @return DISPLAY_BUSY: 动画进行中
 *         DISPLAY_DONE: 动画完成
 */
static display_t ticker(struct  tm* now) {

    // ---------- 静态变量，保持跨帧状态 ----------
    static uint8_t yPos;            // 小时/分钟滚动偏移
    static uint8_t yPos_secs;       // 秒滚动偏移
    static bool moving = false;  // 是否有数字正在滚动
    static bool moving2[5];      // 每个数字是否滚动，顺序：H十,H个,M十,M个,S十

#if COMPILE_ANIMATIONS
    static uint8_t hour2;
    static uint8_t mins;
    static uint8_t secs;

    if(appConfig.animations)
    {
        if(now->tm_sec != secs)
        {
            yPos = 0;
            yPos_secs = 0;
            moving = true;

            moving2[0] = div10(now->tm_hour) != div10(hour2);
            moving2[1] = mod10(now->tm_hour) != mod10(hour2);
            moving2[2] = div10(now->tm_min) != div10(mins);
            moving2[3] = mod10(now->tm_min) != mod10(mins);
            moving2[4] = div10(now->tm_sec) != div10(secs);
		
            //memcpy(&timeDateLast, &timeDate, sizeof(timeDate_s));
            hour2 = now->tm_hour;
            mins = now->tm_min;
            secs = now->tm_sec;
        }

        if(moving)
        {
            if(yPos <= 3)
                yPos++;
            else if(yPos <= 6)
                yPos += 3;
            else if(yPos <= 16)
                yPos += 5;
            else if(yPos <= 22)
                yPos += 3;
            else if(yPos <= 24 + TICKER_GAP)
                yPos++;

            if(yPos >= MIDFONT_HEIGHT + TICKER_GAP)
                yPos = 255;

            if(yPos_secs <= 1)
                yPos_secs++;
            else if(yPos_secs <= 13)
                yPos_secs += 3;
            else if(yPos_secs <= 16 + TICKER_GAP)
                yPos_secs++;

            if(yPos_secs >= FONT_SMALL2_HEIGHT + TICKER_GAP)
                yPos_secs = 255;

            if(yPos_secs > FONT_SMALL2_HEIGHT + TICKER_GAP && yPos > MIDFONT_HEIGHT + TICKER_GAP)
            {
                yPos = 0;
                yPos_secs = 0;
                moving = false;
                memset(moving2, false, sizeof(moving2));
            }
        }
    }
    else
#endif
    {
        // 如果没有开启动画，直接静态显示
        yPos = 0;   // 小时/分钟滚动偏移
        yPos_secs = 0;  // 秒滚动偏移
        moving = false; // 无数字正在滚动
        memset(moving2, false, sizeof(moving2));    // 没有数字是否滚动
    }

    

    // ---------- 绘制每个数字 ----------
    tickerData_t data;

    // 秒十位
    data.x = 104;
    data.y = 28;
    data.bitmap = (const uint8_t*)&small2Font;
    data.w = FONT_SMALL2_WIDTH;
    data.h = FONT_SMALL2_HEIGHT;
    data.offsetY = yPos_secs;        // 秒滚动偏移
    data.val = div10(now->tm_sec);
    data.maxVal = 5;
    data.moving = moving2[4];        // 是否滚动
    drawTickerNum(&data);

    // 秒个位
    data.x = 116;
    data.val = mod10(now->tm_sec);
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
    data.val = div10(now->tm_min);
    data.maxVal = 5;
    data.moving = moving2[2];
    drawTickerNum(&data);

    // 分钟个位
    data.x = 83;
    data.val = mod10(now->tm_min);
    data.maxVal = 9;
    data.moving = moving2[3];
    drawTickerNum(&data);

    // 小时十位
    data.x = 1;
    data.val = div10(now->tm_hour);
    data.maxVal = 5;
    data.moving = moving2[0];
    drawTickerNum(&data);

    // 小时个位
    data.x = 24;
    data.val = mod10(now->tm_hour);
    data.maxVal = 9;
    data.moving = moving2[1];
    drawTickerNum(&data);

    // ---------- 绘制冒号，每半秒闪烁 ----------
    if(HAL_GetTick() % 3600 > 1800)
        draw_bitmap(TIME_POS_X + 46 + 2, TIME_POS_Y, colon,
                    FONT_COLON_WIDTH, FONT_COLON_HEIGHT, NOINVERT, 0);

    // ---------- 绘制 AM/PM ----------
    // char tmp[2];
    // tmp[0] = timeDate.time.ampm;
    // tmp[1] = 0x00;
    // draw_string(tmp, false, 104, 20);

    // ---------- 返回动画状态 ----------
    return (moving ? DISPLAY_BUSY : DISPLAY_DONE);
}


/**
 * @brief 绘制数字翻牌（无动画版本）
 * @param data tickerData_t* 指向数字显示参数
 */
static void drawTickerNum(tickerData_t* data)
{
    uint8_t arraySize = (data->w * data->h) / 8;
    uint8_t yPos = data->offsetY;
    const uint8_t* bitmap = &data->bitmap[data->val * arraySize];
    uint8_t x = data->x;
    uint8_t y = data->y;

    if(!data->moving || yPos == 0 || yPos == 255)
        draw_bitmap(x, y, bitmap, data->w, data->h, NOINVERT, 0);
    else
    {
        uint8_t prev = data->val - 1;
        if(prev == 255)
            prev = data->maxVal;

        draw_bitmap(x, y, bitmap, data->w, data->h, NOINVERT, yPos - data->h - TICKER_GAP);
        draw_bitmap(x, y, &data->bitmap[prev * arraySize], data->w, data->h, NOINVERT, yPos);
    }	
}



