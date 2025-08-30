//
// Created by 14419 on 25-8-30.
//


#include "stopwatch.h"

#if COMPILE_STOPWATCH

typedef enum
{
	STATE_STOPPED = 0,	// 秒表停止状态
	STATE_TIMING	// 秒表计时状态
} stopwatch_state_t;

static stopwatch_state_t state;	//跟踪秒表当前状态（停止或计时）
static uint32_t timer;	//	记录经过的毫秒数
static uint32_t lastMS;	//	记录上一次更新的毫秒时间戳

static bool btnReset(void);
static bool btnStartStop(void);
static bool btnExit(void);
static display_t draw(void);


void stopwatch_open()
{
	// 关闭当前菜单
	menu_close();
	// 用于渲染秒表界面。
	display_setDrawFunc(draw);
	// 配置按钮功能，分别绑定到 `btnReset`（重置）、`btnStartStop`（启动/停止）和 `btnExit`（退出）。
	buttons_setFuncs(btnReset, btnExit, btnStartStop);
}


bool stopwatch_active()
{
	// 检查秒表是否处于计时状态。
	return (state == STATE_TIMING);
}

/**
 * @brief 更新计时器的毫秒计数
 */
void stopwatch_update()
{
	if(state == STATE_TIMING)
	{
		const uint32_t now = HAL_GetTick();
		timer += now - lastMS;
		lastMS = now;
		if(timer > 359999999) // 99 hours, 59 mins, 59 secs, 999 ms
			timer = 359999999;
	}
}

static bool btnReset()
{
	timer = 0;
	lastMS = HAL_GetTick();
	return true;
}

static bool btnStartStop()
{
	if(state == STATE_TIMING)
	{
		state = STATE_STOPPED;
		// pwrmgr_setState(PWR_ACTIVE_STOPWATCH, PWR_STATE_NONE);
	}
	else if(state == STATE_STOPPED)
	{
		state = STATE_TIMING;
		// pwrmgr_setState(PWR_ACTIVE_STOPWATCH, PWR_STATE_IDLE);
	}
	lastMS = HAL_GetTick();
	return true;
}

static bool btnExit()
{
	// animation_start(display_load, ANIM_MOVE_OFF);
	return true;
}


#define TIME_POS_X 1
#define TIME_POS_Y 20

static display_t draw()
{
	// Draw battery icon
	drawBattery();

	uint8_t num1;
	uint8_t num2;
	uint8_t num3;
	const uint32_t  timer1=timer/2.32;     //调整时间
	const uint32_t secs = timer1 / 1000;

	if(timer1 < 3600000)
	{
		num3 = (timer1 % 1000) / 10; // ms
		num2 = secs % 60; // secs
		num1 = secs / 60; // mins
	}
	else
	{
		num3 = secs % 60; // secs
		num2 = (secs / 60) % 60; // mins
		num1 = (secs / 3600); // hours
	}

	draw_bitmap(1, TIME_POS_Y, midFont[div10(num1)], MIDFONT_WIDTH, MIDFONT_HEIGHT, NOINVERT, 0);
	draw_bitmap(24, TIME_POS_Y, midFont[mod10(num1)], MIDFONT_WIDTH, MIDFONT_HEIGHT, NOINVERT, 0);
	draw_bitmap(60, TIME_POS_Y, midFont[div10(num2)], MIDFONT_WIDTH, MIDFONT_HEIGHT, NOINVERT, 0);
	draw_bitmap(83, TIME_POS_Y, midFont[mod10(num2)], MIDFONT_WIDTH, MIDFONT_HEIGHT, NOINVERT, 0);
	draw_bitmap(104, 20 - 4 + 12, small2Font[div10(num3)], FONT_SMALL2_WIDTH, FONT_SMALL2_HEIGHT, NOINVERT, 0);
	draw_bitmap(116, 20 - 4 + 12, small2Font[mod10(num3)], FONT_SMALL2_WIDTH, FONT_SMALL2_HEIGHT, NOINVERT, 0);
	draw_bitmap(TIME_POS_X + 46 + 2, TIME_POS_Y, colon, FONT_COLON_WIDTH, FONT_COLON_HEIGHT, NOINVERT, 0);

	// Draw time
	draw_string(time_timeStr(), NOINVERT, 48, 0);

	return DISPLAY_BUSY;
}

#endif
