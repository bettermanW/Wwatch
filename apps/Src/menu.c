//
// Created by 14419 on 25-8-23.
//
#include "menu.h"

#include "button.h"

static void doBtn(menu_f btn);



operation_s operation;

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




/**************************************实现绘制接口*********************************************/
static void loader(operation_t op, uint8_t num, uint8_t data)
{
    operation.op = op;     // 记录“要干什么”（绘图/执行动作/画文字…）
    operation.id = num;    // 记录“针对哪个菜单项”
    operation.data = data; // 附带参数（坐标/是否动画/等）

    if(menuData.func.loader != NULL)
        menuData.func.loader(num); // 把“第 num 项”交给当前菜单的 loader 回调去处理
}


/**
 * @brief 绘制菜单标题，居中显示在屏幕顶部
 */
static void drawTitle()
{
    char buff[BUFFSIZE_STR_MENU];
    memset(buff, ' ', sizeof(buff));
    // 计算标题居中偏移
    strcpy((buff + (9 - (strlen(menuData.title) / 2))),menuData.title);
    draw_string(buff, false, 0, 0);
}

/**
 * @brief 绘制基于字符串的菜单项列表，带有一个“>”符号指示当前选中的选项
 */
static void menu_drawStr()
{
    drawTitle(); // 绘制标题

    uint8_t scroll = menuData.scroll; // 获取当前滚动偏移量
    // 计算显示的菜单项范围 菜单项总数optionCount
    uint8_t count = ((MAX_MENU_ITEMS < menuData.optionCount) ? MAX_MENU_ITEMS : menuData.optionCount) + scroll;
    // 遍历显示范围内的菜单项
    for(uint8_t i=scroll;i<count;i++)
    {
        // 计算每项的纵坐标y = 8 + (8 * (i - scroll))（每项占8像素高，从第8行开始）
        uint8_t y = 8 + (8 * (i - scroll));
        if(i == menuData.selected) // 当前选中的菜单项索引
            draw_string(">", false, 0, y);
        // 加载并绘制菜单项的字符串名称。
        loader(OPERATION_DRAWNAME_STR, i, y);
    }
}

/**
 * 😭无动画
 * @brief   用于绘制基于图标的菜单的函数，负责在屏幕上渲染菜单项的图标、选中框以及选中项的名称
 * @return  指示绘制是否完成
 */
static display_t menu_drawIcon()
{
    static int animX = 64;  // 表示图标的水平位置,屏幕水平中心点。
    /* 计算选中菜单项的目标水平位置
     * 每个图标的宽度或间距为 48 像素（固定值）。
     * 表示选中项的图标应位于屏幕中心的水平坐标
     */
    int x = 64 - (48 * menuData.selected);

    animX = x;

    x = animX - 16; // 将绘制起点向左偏移 16 像素。

    drawTitle();
    // 在屏幕上绘制选中项的上下边框（选择框）。
    draw_bitmap(46, 14, selectbar_top, 36, 8, NOINVERT, 0);
    draw_bitmap(46, 42, selectbar_bottom, 36, 8, NOINVERT, 0);

    // 遍历所有菜单项（`menuData.optionCount`），绘制可见范围内的图标。
    LOOP(menuData.optionCount, i)
    {
        // 确保图标未超出屏幕右侧 && 确保图标未完全移出屏幕左侧
        if(x < FRAME_WIDTH && x > -32)
            loader(OPERATION_DRAWICON, i, x);
        x += 48;
    }

    // 绘制选中项名称 名称显示在固定位置
    loader(OPERATION_DRAWNAME_ICON, menuData.selected, 0);

    return DISPLAY_DONE;
}

/**
 * @brief 这是菜单绘制的入口函数，负责根据菜单类型调用相应的绘制函数。
 * @return 状态用于支持动画效果
 */
display_t menu_draw()
{
    display_t busy = DISPLAY_DONE;

    // 如果菜单类型为文字菜单
    if(menuData.menuType == MENU_TYPE_STR)
        menu_drawStr();
    else
        busy = menu_drawIcon(); // 绘制图标菜单

    // 如果定义了额外的绘制函数（由菜单项自己实现）
    if(menuData.func.draw != NULL)
        busy = busy || menuData.func.draw() ? DISPLAY_BUSY : DISPLAY_DONE;

    return busy;
}


// #include <math.h>

/**
 * @brief  根据`operation.op`执行菜单项的绘制（图标或字符串）或动作，核心处理函数。
 * @param num 菜单项索引
 * @param name 菜单项名称（字符串
 * @param icon 指向图标数据的指针（可能为`NULL`
 * @param actionFunc 菜单项的动作函数
 */
void setMenuOption(const uint8_t num, const char* name, const uint8_t* icon, const menu_f actionFunc)
{
    // 确保只处理当前操作的菜单项
    if(num != operation.id)
        return;

    // 处理四种操作
    switch(operation.op)
    {
        case OPERATION_DRAWICON: // 绘制图标
        {
            // const uint8_t a = operation.data;

            // const float x = ((a/(float)(FRAME_WIDTH-32)) * (M_PI / 2)) + (M_PI / 4);
            // uint8_t y = (sin(x) * 32); //             // 使用正弦函数基于`a`计算动态Y坐标
            const uint8_t y = 28; // comment this out for magic

            draw_bitmap(operation.data, y + 4 - 16, icon != NULL ? icon : menu_default, 32, 32, NOINVERT, 0);
        }
            break;
        case OPERATION_DRAWNAME_ICON:
            draw_string((char*)name, false, 0, FRAME_HEIGHT - 8);
            break;
        case OPERATION_DRAWNAME_STR:
            draw_string((char*)name, false, 6, operation.data);
            break;
        case OPERATION_ACTION:
            if(actionFunc != NULL)
                // operation.data ? beginAnimation(actionFunc) : actionFunc();
                    actionFunc();
            break;
        default:
            break;
    }
}

/***************************光标滚动逻辑********************************/

/**
 * @brief 调整菜单的滚动偏移量，确保当前选中的菜单项在屏幕的可见范围内
 */
static void checkScroll()
{
    // 获取当前滚动偏移量
    uint8_t scroll = menuData.scroll;
    // 检查选中项是否超出可见范围
    if(menuData.selected >= scroll + MAX_MENU_ITEMS)
        // 使选中项位于可见窗口的最后一行
        scroll = (menuData.selected + 1) - MAX_MENU_ITEMS;
    else if(menuData.selected < scroll)
        scroll = menuData.selected;
    menuData.scroll = scroll;
}

/**
 * @brief 将当前选中的菜单项索引加 1，切换到下一个菜单项
 */
void nextOption()
{
    menuData.selected++;
    // 达到或超过总数（即超出最后一个项），将其重置为 0，实现循环选择（从最后一个项回到第一个项）。
    if(menuData.selected >= menuData.optionCount)
        menuData.selected = 0;

    checkScroll();
}

/**
 * @brief 将当前选中的菜单项索引减 1，切换到上一个菜单项
 */
void prevOption()
{
    menuData.selected--;
    if(menuData.selected >= menuData.optionCount)
        menuData.selected = menuData.optionCount - 1;

    checkScroll();
}

/***************************菜单返回与退出逻********************************/
/**
 * @brief 判断当前选项是否是“退出/返回”条目（约定最后一项为 Back）
 */
bool exitSelected()
{
    return menuData.selected == menuData.optionCount - 1;
}

/**
 * @brief 进入一个子菜单时，设置 prevMenu 结构以便返回时能恢复上一级选择状态,并把 menuData.prevMenu 指向新的“返回到上级菜单”的函数 newPrevMenu。
 * @param prevMenu 上一级菜单状态结构体
 * @param newPrevMenu 当前子菜单退出时要调用的函数（返回上一级菜单）
 */
void setPrevMenuOpen(prev_menu_s* prevMenu, const menu_f newPrevMenu)
{
    if(menuData.prevMenu != newPrevMenu)
        prevMenu->last = menuData.prevMenu; // 保存上一级菜单的打开函数
    menuData.selected = prevMenu->lastSelected; // 恢复上一级菜单选中项
    menuData.prevMenu = newPrevMenu; // 设置当前菜单返回时调用的函数
}

/**
 * @brief 在从子菜单退出时更新 prevMenu
 * @param prevMenu
 */
void setPrevMenuExit(prev_menu_s* prevMenu)
{
    if(!exitSelected()) // 如果当前选中不是 Back
        prevMenu->lastSelected = menuData.selected; // 保存选中的菜单项索引
    else
    {
        prevMenu->lastSelected = 0; // 重置选中索引
        menuData.prevMenu = prevMenu->last; // 恢复上一级菜单的打开函数
    }
}

/**
 * @brief 清空 menuData.func（回调集合），防止悬挂函数指针。常在 menu_close() 前调用。
 */
static void clear()
{
    memset(&menuData.func, 0, sizeof(menuFuncs_t));
}

/**
 * @brief 给当前菜单的 最后一项 添加一个固定的“返回/退出”选项。
 */
void addBackOption()
{
    setMenuOption(menuData.optionCount - 1, menuBack, menu_exit, back);
}

/**
 * @brief ：清理菜单回调函数，避免悬挂函数指针或意外调用
 */
void menu_close()
{
    clear();    // 清理菜单回调函数，避免悬挂函数指针或意外调用
    menuData.isOpen = false; //  标记菜单已关闭
    menuData.prevMenu = NULL;   // 清空“返回上一级菜单”的记录，防止回退时误调用
    display_load(); // 关闭菜单后恢复显示（通常是表盘或者默认界面）
}

/**
 * @brief 菜单的 返回功能，结合 prev_menu_s 可以实现从子菜单返回上级菜单，同时保持光标位置。
 */
void back()
{
    /*
    判断 menuData.prevMenu 是否存在（即是否有上一级菜单记录）：
    如果存在 → 调用 prevMenu()，返回上一级菜单。
    如果不存在 → 调用 mMainOpen()，回到主菜单。
    注意代码里最后 又调用了一次 mMainOpen()，这是作者的保险写法，确保返回后至少打开主菜单。
     */
    menuData.prevMenu != NULL ? menuData.prevMenu() : mMainOpen();
    mMainOpen();
}

/**
 * @brief 始化或重置菜单的全局状态，为新菜单的显示和交互准备必要的数据
 * @param optionCount 表示菜单的选项数量
 * @param menuType 指定菜单类型
 * @param title 菜单的标题字符串
 */
void setMenuInfo(const uint8_t optionCount, const menu_type_t menuType, const char* title)
{
    clear(); // 避免旧菜单的回调函数, 干扰新菜单，确保新菜单的回调函数从干净状态开始设置。
    menuData.scroll = 0;    // 确保菜单显示从第一个选项开始。
    menuData.selected = 0;  // 将当前选中项重置为第一个选项（索引 0）
    menuData.optionCount = optionCount + 1; // 设置菜单的总选项数，包含传入的 optionCount 加上一个“返回”选项
    menuData.menuType = menuType;   // 设置菜单类型，决定后续绘制逻辑（字符串菜单或图标菜单）
    menuData.title = title;
}

/**
 * @brief 设置菜单的按钮回调函数和菜单项加载函数。
 *
 * 该函数为当前菜单配置用户交互的回调函数（对应三个按钮）和菜单项加载函数。
 * 它将传入的函数指针存储在 menuData.func 结构体中，供菜单系统在处理按键事件
 * 或加载菜单项（如图标或字符串）时调用。通常在 setMenuInfo() 后调用，以完成
 * 菜单初始化。
 *
 * @param btn1Func 按钮 1 的回调函数，通常用于“上移”操作（如 prevOption）。
 *                 可为 NULL，表示无操作。
 * @param btn2Func 按钮 2 的回调函数，通常用于“选择”或“确认”操作（如 doAction）。
 *                 可为 NULL，表示无操作。
 * @param btn3Func 按钮 3 的回调函数，通常用于“下移”操作（如 nextOption）。
 *                 可为 NULL，表示无操作。
 * @param loader 菜单项加载函数，用于动态加载菜单项的内容（如 setMenuOption_P）。
 *               可为 NULL，表示无需自定义加载。
 */
void setMenuFuncs(const menu_f btn1Func, const menu_f btn2Func, const menu_f btn3Func, const itemLoader_f loader)
{
    menuData.func.btn1 = btn1Func;  // 设置上移按钮回调
    menuData.func.btn2 = btn2Func;  // 设置选择按钮回调
    menuData.func.btn3 = btn3Func;  // 设置下移按钮回调
    menuData.func.loader = loader;   // 设置菜单项加载函数
}

/**
 * @brief 执行当前选中的菜单项动作
 * @param anim 是否带动画
 */
void doAction(bool anim)
{
    loader(OPERATION_ACTION, menuData.selected, anim);
}


