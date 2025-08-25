//
// Created by 14419 on 25-8-23.
//
#include "menu.h"

#include "button.h"

static void doBtn(menu_f btn);

menu_s menuData;
/**
 * @brief 查询菜单是否用于打开，用于**事件路由**
 * @return 是否打开
 */
bool menu_isOpen(void) {
    return menuData.isOpen;
}


/**
 * @brief 若菜单未打开：打开菜单、初始化选中项与滚动窗口
 *        若已打开：对当前选中项执行“进入/执行”动作（叶子功能或进入子菜单）。
 * @return
 */
bool menu_select()
{
    // 没有动画效果👍
    if(!menuData.isOpen) // 标志当前菜单没有打开
    {
        menuData.isOpen = true; // 设置菜单状态为 已打开
        // 调用菜单主界面的初始化函数，绘制初始界面
        // mMainOpen();

        char buf[64];
        int len = sprintf(buf, "菜单 [%s] 已打开\r\n", menuData.title);
        HAL_UART_Transmit(&huart2, (uint8_t*)buf, len, HAL_MAX_DELAY);

    }
    else if(menuData.func.btn3 != NULL)
        menuData.func.btn3();
    return true;
}

/**
 * @brief 调用 btn3 回调（菜单的 向下 功能
 * @return
 */
bool menu_down()
{
    doBtn(menuData.func.btn2);
    return true;
}

/**
 * @brief 调用 btn1 回调（菜单的 向上 功能）
 * @return
 */
bool menu_up()
{
    doBtn(menuData.func.btn1);
    return true;
}
/**
 * @brief   只有菜单模式下，按钮回调才会真正执行，避免误触。
 * @param btn 按键回调函数
 */
static void doBtn(menu_f btn)
{
    if(menuData.isOpen) // 标志当前菜单打开
        btn();
}

