//
// Created by 14419 on 25-8-20.
//

#include "button.h"

/**
 * @brief 保存旧地回调函数，设置新地回调函数
 * @param btn 哪一个按钮
 * @param func 指定的处理函数指针
 * @return 返回旧的函数指针
 */
button_f buttons_setFunc(const btn_t btn, const button_f func) {
    const button_f old = buttons[btn].onPress; // 保存旧的回调函数
    buttons[btn].onPress = func; // 设置新地回调函数
    return old;
}

/**
 * @brief  同时设置 3 个按钮的行为
 * @param btn1 按钮1
 * @param btn2 按钮2
 * @param btn3 按钮3
 */
void buttons_setFuncs(button_f btn1, button_f btn2, button_f btn3)
{
    buttons[BTN_1].onPress = btn1;
    buttons[BTN_2].onPress = btn2;
    buttons[BTN_3].onPress = btn3;
}

