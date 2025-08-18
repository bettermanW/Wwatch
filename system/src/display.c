//
// Created by 14419 on 25-8-17.
//
#include "display.h"

#include <stdio.h>

#include "usart.h"


static display_f func;  // 当前页面的 “加载/初始化函数”
static uint32_t g_xres, g_yres, g_bpp; // 屏幕分辨率的宽度和高度，屏幕的色深
static uint8_t *g_framebuffer;  // 指向屏幕的帧缓冲区，是一个字节数组
static draw_f drawFunc; // 回调函数，进行屏幕的逐帧刷新


static unsigned char lastDraw = 0;  // 上一次绘制的时间戳
static uint8_t fpsMs = 33;   // 目标30 FPS (1000/30 ≈ 33 ms)
/**
 * @brief 设置当前页面的加载函数（一般用于初始化界面时调用）。
 * @param faceFunc 代表当前活跃的 “绘图函数”
 */
void display_set(const display_f faceFunc) {
    g_framebuffer = (uint8_t *)OLED_GetFrameBuffer(&g_xres, &g_yres, &g_bpp);
    func = faceFunc;    //
}

/**
 * @brief 立即调用当前界面的初始化函数，完成界面进入逻辑
 */
void display_load() {
    if (func != NULL) {
        // func 是通过 display_set() 设置的当前界面初始化
        func();
    }
}

/**
 * @brief 绘制函数，用于后续调用绘制当前界面（如主菜单、设置等）
 * @param func 当前页面的“加载/初始化函数”
 */
draw_f display_setDrawFunc(const draw_f func) {
    draw_f old = drawFunc; // 备份当前绘图函数指针
    drawFunc = func;    // 替换为新的绘图函数
    return old; // 返回原来的绘图函数指针
}

void display_update(void) {
    // 帧率限制
    unsigned char now = HAL_GetTick();
    if (now - lastDraw < fpsMs) return;
    lastDraw = now;

    // 执行绘制
    display_t busy = DISPLAY_DONE;
#if COMPILE_ANIMATIONS // 不显式定义默认为0
    // animation_update(); // 假设已实现
    if (drawFunc) busy = drawFunc();
#else
    if (drawFunc) busy = drawFunc();
#endif

    // 刷新屏幕

    draw_end();

}

