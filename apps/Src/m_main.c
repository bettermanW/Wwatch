//
// Created by 14419 on 25-8-26.
//
#include "m_main.h"

/**
 * @brief 主菜单入口函数（外部调用时进入主菜单）
 */
void mMainOpen() {
    // 设置按键响应：此时只有“确认键”有效
    // 启动动画，动画完成后会调用
    buttons_setFuncs(NULL, menu_select, NULL);
}