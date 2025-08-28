//
// Created by 14419 on 25-8-19.
//

#ifndef TYPEDEF_H
#define TYPEDEF_H
#include "stdint.h"
#include "stdbool.h"

#define BUFFSIZE_STR_MENU   24 // 文本菜单24字节，包含23个字符+1个空终止符

#define BUFFSIZE_STR_DAYS	4
#define BUFFSIZE_STR_MONTHS	4
#define BUFFSIZE_DATE_FORMAT		((BUFFSIZE_STR_DAYS - 1) + (BUFFSIZE_STR_MONTHS - 1) + 12)

#define SMALLFONT_WIDTH 5 // 字体宽度为 5 像素
#define SMALLFONT_HEIGHT 8 // 字体高度为 8 像素
#define FONT_SMALL2_WIDTH 11
#define FONT_SMALL2_HEIGHT 16

#define NOINVERT false

#define FRAME_HEIGHT 64
#define FRAME_WIDTH 128

/**
 * @brief 显示状态枚举
 *
 * 用于指示显示操作的完成状态：
 * - DISPLAY_DONE: 显示已完成，无需进一步处理
 * - DISPLAY_BUSY: 显示正在进行中（如动画播放），需要继续处理
 */
typedef enum
{
    DISPLAY_DONE,   ///< 显示操作已完成
    DISPLAY_BUSY,   ///< 显示操作正在进行中（通常用于动画或过渡效果）
} display_t;

/**
 * @brief 绘制函数指针类型
 *
 * 定义了一个函数指针类型，指向无参数且返回display_t状态的函数。
 * 通常用于需要多帧渲染的动画或渐进式显示功能。
 *
 * @return display_t 返回显示状态（DONE或BUSY）
 */
typedef display_t (*draw_f)(void);

/**
 * @brief 显示函数指针类型
 *
 * 定义了一个函数指针类型，指向无参数且无返回值的函数。
 * 通常用于单次执行的静态显示功能，不需要状态反馈。
 */
typedef void (*display_f)(void);


/******************************日期数据结构***************************************/

// 定义 12 个月份的索引（0-11），用于 date_s 结构中的 month 字段
typedef enum
{
    MONTH_JAN = 0,
    MONTH_FEB = 1,
    MONTH_MAR = 2,
    MONTH_APR = 3,
    MONTH_MAY = 4,
    MONTH_JUN = 5,
    MONTH_JUL = 6,
    MONTH_AUG = 7,
    MONTH_SEP = 8,
    MONTH_OCT = 9,
    MONTH_NOV = 10,
    MONTH_DEC = 11
} month_t;

// 定义一周 7 天的索引（0-6）
// 修改为与struct tm一致（0=星期日）
typedef enum {
    DAY_SUN = 0,  // 0 = 星期日
    DAY_MON = 1,  // 1 = 星期一
    DAY_TUE = 2,  // 2 = 星期二
    DAY_WED = 3,  // 3 = 星期三
    DAY_THU = 4,  // 4 = 星期四
    DAY_FRI = 5,  // 5 = 星期五
    DAY_SAT = 6,  // 6 = 星期六
} day_t;

// 存储时间信息，包括秒、分钟、小时和 AM/PM 指示
typedef struct {
    uint8_t secs;   // 秒 (0-59)
    uint8_t mins;   // 分钟 (0-59)
    uint8_t hour;   // 小时 (0-23)
    char ampm;      // AM/PM ('A' 或 'P') 12/24
}time_s;

// 存储日期信息，包括星期、日期、月份和年份
typedef struct {
    day_t day;      // 星期 (DAY_MON 到 DAY_SUN)
    uint8_t date;   // 日期 (1-31)
    month_t month;  // 月份 (MONTH_JAN 到 MONTH_DEC)
    uint8_t year;   // 年份后两位 (例如 25 表示 2025)
} date_s;

// 存储完整的当前时间和日期。
// 供 ticker 和 drawDate 函数使用，驱动时间和日期显示。
typedef struct {
    time_s time;    // 时间信息
    date_s date;    // 日期信息
} timeDate_s;

typedef struct
{
    uint8_t x;         // 横坐标
    uint8_t y;         // 纵坐标
    const uint8_t* bitmap; // 字体位图
    uint8_t w;         // 宽
    uint8_t h;         // 高
    uint8_t offsetY;   // 垂直偏移量，用于滚动
    uint8_t val;       // 当前显示数字
    uint8_t maxVal;    // 该位数字最大值，用于翻页
    bool moving;    // 是否正在滚动
} tickerData_t;


/***********************************菜单回调数据结构********************************************/
// 函数指针类型，表示一个 **无参无返回值的菜单操作函数** 用来绑定按钮行为或者菜单切换
typedef void (*menu_f)(void);
// 用于 **加载菜单项**（比如显示对应项的内容）。
typedef void (*itemLoader_f)(uint8_t);

typedef enum
{
    MENU_TYPE_STR,  // 文字菜单（比如 "Alarm", "Settings"）
    MENU_TYPE_ICON  // 图标菜单（比如 电池、时钟图标）
} menu_type_t;  // 菜单枚举类型

typedef struct{
    menu_f btn1;     // 按钮1的处理函数 KEY1
    menu_f btn2;     // 按钮2的处理函数 KEY2
    menu_f btn3;     // 按钮3的处理函数 KEY0
    draw_f draw;     // 绘制菜单界面的函数
    itemLoader_f loader; // 菜单项加载函数
} menuFuncs_t;  // 提供菜单的 **行为接口**（绘制、按键响应、加载内容）

typedef struct{
    uint8_t selected;           // 当前选中的菜单项索引
    uint8_t scroll;             // 滚动偏移量（如果菜单项多于一屏）
    uint8_t optionCount;        // 菜单项总数
    bool isOpen;             // 菜单是否打开
    const char* title;       // 菜单标题（例如 "Settings"）
    menu_type_t menuType;    // 菜单类型（字符串/图标）
    menuFuncs_t func;        // 绑定的功能函数集合
    menu_f prevMenu;         // 上一级菜单（返回用）
} menu_s;   // 保存菜单的 **状态**（光标、滚动、打开/关闭等）

/*管理菜单系统的操作和绘制逻辑*/

typedef enum
{
    OPERATION_DRAWICON, // 绘制图标（例如菜单项的图形表示）
    OPERATION_DRAWNAME_ICON, // 绘制当前选中菜单项的名称（通常在图标菜单中显示）。
    OPERATION_DRAWNAME_STR, // 绘制字符串形式的菜单项（用于字符串类型的菜单）
    OPERATION_ACTION    // 执行某个动作（例如触发菜单项的功能）
} operation_t; // 菜单系统中可能执行的四种操作类型

typedef struct
{
    uint8_t data;   // 存储与操作相关的附加数据
    operation_t op;    // 指定操作的类型
    uint8_t id;     // 标识菜单项的索引
} operation_s; // 量级的数据结构，用于封装单个菜单操作的详细信息，充当操作任务的“描述符”

/**/
typedef struct{
    uint8_t lastSelected;
    menu_f last;
}prev_menu_s;
#endif //TYPEDEF_H
