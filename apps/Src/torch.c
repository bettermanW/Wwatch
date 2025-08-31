//
// Created by 14419 on 25-8-30.
//
#include "torch.h"

#if COMPILE_TORCH


/*
 * 静态变量，存储闪烁周期（以毫秒为单位）。
 * 。值为0表示持续点亮，非0表示闪烁模式，值越大闪烁频率越低。
 */
static uint16_t strobe;

static bool btnExit(void);
static bool btnFlashRate(void);
static display_t draw(void);
extern appconfig_s appConfig;
void torch_open()
{
    // pwrmgr_setState(PWR_ACTIVE_DISPLAY, PWR_STATE_BUSY);
    menu_close();
    // 初始化闪烁周期为0，表示默认持续点亮（非闪烁模式）
    strobe = 0;
    display_setDrawFunc(draw);
    buttons_setFuncs(btnExit, btnExit, btnFlashRate);
}

/**
 * @brief 处理退出手电筒模式的逻辑
 * @return 表示按钮事件已处理，可能通知系统事件已完成。
 */
static bool btnExit()
{
    // pwrmgr_setState(PWR_ACTIVE_DISPLAY, PWR_STATE_NONE);
    OLED_SetColorMode(appConfig.invert);
    display_load();
    return true;
}

/**
 * @brief 调整LED和显示屏的闪烁周期
 * @return
 */
static bool btnFlashRate()
{
    if (strobe < 500) // 闪烁周期小于500ms
        // 这种公式使闪烁周期以非线性方式增加
        strobe += 50 * (strobe / 50 + 1); // 增加闪烁周期
    else
        strobe = 0;
    return true;
}

/**
 * @brief 控制显示屏颜色反转和LED的闪烁或持续点亮。
 * @return
 */
static display_t draw()
{
    static bool invert; // 记录当前显示屏颜色反转状态
    static uint32_t lastStrobe;

    if (strobe) // 闪烁模式
    {
        const uint32_t now = HAL_GetTick();
        if (now - lastStrobe >= strobe)
        {
            lastStrobe = now;
            invert = !invert;
            OLED_SetColorMode(invert);
            // led_flash(invert ? LED_GREEN : LED_RED, 20, 255);
        }
        return DISPLAY_BUSY;
    }



    OLED_SetColorMode(true);
    // led_flash(LED_GREEN, 100, 255);
    // led_flash(LED_RED, 100, 255);

    return DISPLAY_DONE;
}

#endif