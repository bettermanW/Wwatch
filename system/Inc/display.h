//
// Created by 14419 on 25-8-17.
//

#ifndef DISPLAY_H
#define DISPLAY_H
#include "draw.h"
// 当某个界面被加载时的初始化 函数指针
typedef void (*display_f)(void);

typedef enum {
    DISPLAY_DONE,   // 绘图完成，无需继续刷新，系统可降低帧率
    DISPLAY_BUSY,   // 当前界面仍有内容需要绘制，系统应该维持高频率
} display_t;

// 用于每一帧的调用、绘制界面内容 函数指针
typedef display_t (*draw_f)(void);

void display_set(display_f);
void display_load();

draw_f display_setDrawFunc(draw_f func);
void display_update(void);
#endif //DISPLAY_H
