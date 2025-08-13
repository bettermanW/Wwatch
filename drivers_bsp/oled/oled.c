//
// Created by 14419 on 25-8-12.
//
#include "oled.h"

// OLED器件地址
#define OLED_ADDRESS 0x7A

// OLED参数
#define OLED_PAGE 8            // OLED页数
#define OLED_ROW 8 * OLED_PAGE // OLED行数
#define OLED_COLUMN 128        // OLED列数

// 显存
uint8_t OLED_GRAM[OLED_PAGE][OLED_COLUMN];

// ========================== 底层通信函数 ==========================

/**
 * @brief 向OLED发送数据的函数
 * @param data 要发送的数据
 * @param len 要发送的数据长度
 * @return None
 * @note 此函数是移植本驱动时的重要函数 将本驱动库移植到其他平台时应根据实际情况修改此函数
 */
void OLED_Send(uint8_t *data, uint8_t len) {
    HAL_I2C_Master_Transmit(&hi2c1, OLED_ADDRESS, data, len, HAL_MAX_DELAY);
}

/**
 * @brief 向OLED发送指令
 */
void OLED_SendCmd(uint8_t cmd) {
    static uint8_t sendBuffer[2] = {0};
    sendBuffer[1] = cmd;
    OLED_Send(sendBuffer, 2);
}

// ========================== OLED驱动函数 ==========================

/**
 * @brief 初始化OLED
 * @note 此函数是移植本驱动时的重要函数 将本驱动库移植到其他驱动芯片时应根据实际情况修改此函数
 */
void OLED_Init() {
    OLED_SendCmd(0xAE); /*关闭显示 display off*/

    OLED_SendCmd(0x02); /*设置列起始地址 set lower column address*/
    OLED_SendCmd(0x10); /*设置列结束地址 set higher column address*/

    OLED_SendCmd(0x40); /*设置起始行 set display start line*/

    OLED_SendCmd(0xB0); /*设置页地址 set page address*/

    OLED_SendCmd(0x81); /*设置对比度 contract control*/
    OLED_SendCmd(0xCF); /*128*/

    OLED_SendCmd(0xA1); /*设置分段重映射 从右到左 set segment remap*/

    OLED_SendCmd(0xA6); /*正向显示 normal / reverse*/

    OLED_SendCmd(0xA8); /*多路复用率 multiplex ratio*/
    OLED_SendCmd(0x3F); /*duty = 1/64*/

    OLED_SendCmd(0xAD); /*设置启动电荷泵 set charge pump enable*/
    OLED_SendCmd(0x8B); /*启动DC-DC */

    OLED_SendCmd(0x33); /*设置泵电压 set VPP 10V */

    OLED_SendCmd(0xC8); /*设置输出扫描方向 COM[N-1]到COM[0] Com scan direction*/

    OLED_SendCmd(0xD3); /*设置显示偏移 set display offset*/
    OLED_SendCmd(0x00); /* 0x00 */

    OLED_SendCmd(0xD5); /*设置内部时钟频率 set osc frequency*/
    OLED_SendCmd(0xC0);

    OLED_SendCmd(0xD9); /*设置放电/预充电时间 set pre-charge period*/
    OLED_SendCmd(0x1F); /*0x22*/

    OLED_SendCmd(0xDA); /*设置引脚布局 set COM pins*/
    OLED_SendCmd(0x12);

    OLED_SendCmd(0xDB); /*设置电平 set vcomh*/
    OLED_SendCmd(0x40);

    OLED_NewFrame();
    OLED_ShowFrame();

    OLED_SendCmd(0xAF); /*开启显示 display ON*/
}

/**
 * @brief 开启OLED显示
 */
void OLED_DisPlay_On() {
    OLED_SendCmd(0x8D); // 电荷泵使能
    OLED_SendCmd(0x14); // 开启电荷泵
    OLED_SendCmd(0xAF); // 点亮屏幕
}

/**
 * @brief 关闭OLED显示
 */
void OLED_DisPlay_Off() {
    OLED_SendCmd(0x8D); // 电荷泵使能
    OLED_SendCmd(0x10); // 关闭电荷泵
    OLED_SendCmd(0xAE); // 关闭屏幕
}

/**
 * @brief 设置颜色模式 黑底白字或白底黑字
 * @param ColorMode 颜色模式COLOR_NORMAL/COLOR_REVERSED
 * @note 此函数直接设置屏幕的颜色模式
 */
void OLED_SetColorMode(OLED_ColorMode mode) {
    if (mode == OLED_COLOR_NORMAL) {
        OLED_SendCmd(0xA6); // 正常显示
    }
    if (mode == OLED_COLOR_REVERSED) {
        OLED_SendCmd(0xA7); // 反色显示
    }
}

// ========================== 显存操作函数 ==========================

/**
 * @brief 清空显存 绘制新的一帧
 */
void OLED_NewFrame() {
    memset(OLED_GRAM, 0, sizeof(OLED_GRAM));
}

/**
 * @brief 将当前显存显示到屏幕上
 * @note 此函数是移植本驱动时的重要函数 将本驱动库移植到其他驱动芯片时应根据实际情况修改此函数
 */
void OLED_ShowFrame() {
    static uint8_t sendBuffer[OLED_COLUMN + 1];
    sendBuffer[0] = 0x40;
    for (uint8_t i = 0; i < OLED_PAGE; i++) {
        OLED_SendCmd(0xB0 + i); // 设置页地址
        OLED_SendCmd(0x02);     // 设置列地址低4位
        OLED_SendCmd(0x10);     // 设置列地址高4位
        memcpy(sendBuffer + 1, OLED_GRAM[i], OLED_COLUMN);
        OLED_Send(sendBuffer, OLED_COLUMN + 1);
    }
}