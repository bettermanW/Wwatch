//
// Created by 14419 on 25-8-20.
//

#ifndef BUTTON_H
#define BUTTON_H
#include "stdbool.h"
#include "stdint.h"
// 定义按钮索引编号
typedef enum {
    BTN_1 = 0,
    BTN_2 = 1,
    BTN_3 = 2,

    BTN_COUNT = 4 // 按钮数量
}btn_t;



/**
 * 函数指针类型，定义了按下时可以调用的回调函数
 * 返回true一次性操作， 返回false持续操作
 */
typedef bool (*button_f)(void);

/*封装每个按钮的状态与行为控制*/
typedef struct {
    unsigned int pressedTime;	// 记录最近一次按下的时间（用于是否活跃）
    bool processed;			// 是否已记录按下（防止重复记录时间）
    uint8_t counter;			// 用于按键防抖的“位移缓存”
    bool funcDone;			// 是否已经执行过按键处理函数（防止重复调用）
    button_f onPress;		// 回调函数（用户功能逻辑）
} s_button;
/*即每个按钮 `BTN_1 ~ BTN_3` 都有一个 `s_button` 实例，用数组统一管理。*/
static s_button buttons[BTN_COUNT];

void buttons_update(void);
button_f buttons_setFunc(btn_t btn, button_f func);
void buttons_setFuncs(button_f, button_f, button_f);

#endif //BUTTON_H
