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

/**
 * @brief 统计二进制数中 1 的个数
 * @param val 8位整数，1个byte
 * @return  val中二进制位为 1 的个数*
 */
static uint8_t bitCount(uint8_t val)
{
    uint8_t count = 0;
    // 每次右移一位，相当于逐位检查 `val` 的每一位是否为 1
    for (; val; val >>= 1)
        // 取出当前最低位（0或1）并累加到 `count`
        count += val & 1;
    return count;
}

/**
 * @brief 按键去抖动 + 回调处理
 * @param button
 * @param isPressed
 */
static void processButton(s_button* button, bool isPressed)
{
    /*2.去抖处理*/

    // // 状态计数器左移一位，相当于记录一个滑动窗口，存储最近 N 次采样结果
    button->counter <<= 1;
    if (isPressed)
    {
        // 如果当前检测到 **按下**，就在最低位写 `1`就保存了一段时间内的按键采样历史
        button->counter |= 1;

        /*3. 判断是否足够“稳定”按下*/
        // 去抖动策略
        if (bitCount(button->counter) >= BTN_IS_PRESSED)
        {
            /*4. 第一次按下时记录时间*/
            if (!button->processed)
            {
                button->pressedTime = HAL_GetTick();
                button->processed = true; // 表示已经按下一次
            }

            /*5. 执行回调函数*/
            // 绑定了函数指针 && 调用回调函数成功 && 保证本次只执行一次回调
            if (!button->funcDone && button->onPress != NULL && button->onPress())
            {
                button->funcDone = true;
                // 蜂鸣器 + LED

            }
        }
    }
    else /*6. 松开时恢复状态*/
    {
        // 如果当前采样结果是 **没按下**，则继续观察去抖计数器
        if (bitCount(button->counter) <= BTN_NOT_PRESSED)
        {
            button->processed = false;
            button->funcDone = false;
        }
    }
}

uint8_t test_bitcount() {
    return bitCount(0x56);
}