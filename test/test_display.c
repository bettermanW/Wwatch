// //
// // Created by 14419 on 25-8-17.
// //
//
// #include "test.h"
// static uint32_t g_xres, g_yres, g_bpp; // 屏幕分辨率的宽度和高度，屏幕的色深
// static uint8_t *g_framebuffer;  // 指向屏幕的帧缓冲区，是一个字节数组
// // OLED参数
// #define OLED_PAGE 8            // OLED页数
// #define OLED_ROW 8 * OLED_PAGE // OLED行数
// #define OLED_COLUMN 128        // OLED列数
//
// // 显存
// uint8_t framebuffer[OLED_PAGE][OLED_COLUMN];
//
// // // 页面1：主菜单初始化和绘制
// // void main_menu_init(void) {
// //
// //     char buf[16];  // 足够存放"res=45\n"
// //     uint8_t len = snprintf(buf, sizeof(buf), "Initializing Main Menu\n");
// //     HAL_UART_Transmit(&huart2, (uint8_t*)buf, len, HAL_MAX_DELAY);
// //     // 模拟初始化：清空帧缓冲区，绘制标题
// //     //for (int i = 0; i < sizeof(framebuffer); i++) framebuffer[i] = 0;
// //     // 假设在帧缓冲区写入"Main Menu"文字
// //     HAL_UART_Transmit(&huart2, (uint8_t*)("Main Menu text written to framebuffer\n"), 50, HAL_MAX_DELAY);
// // }
// //
// // int main_menu_draw(void) {
// //     HAL_UART_Transmit(&huart2, (uint8_t*)("Drawing Main Menu frame\n"), 50, HAL_MAX_DELAY);
// //     // 模拟绘制：更新帧缓冲区内容（如高亮选中项）
// //     return DISPLAY_DONE; // 绘制完成
// // }
// // // 测试回调函数
// // void test_display(void) {
// //     // 1. 设置并加载主菜单
// //     display_set(main_menu_init); // 设置主菜单初始化函数
// //     display_load();              // 调用初始化，打印"Initializing Main Menu"
// //     display_setDrawFunc(main_menu_draw); // 设置主菜单绘制函数
// //     display_update();                    // 调用绘制，打印"Drawing Main Menu frame"
// // }
//
// /*display_update测试*/
// // 测试用绘制函数1：简单写入帧缓冲区
// // 测试用绘制函数1：静态绘制
// int test_draw_static(void) {
//     HAL_UART_Transmit(&huart2, (uint8_t *)("Drawing static frame\n"), 50, 1000);
//     for (int i = 0; i < 128 * 64 / 8; i++) {
//         g_framebuffer[i] = 0x55; // 固定图案
//     }
//     return DISPLAY_DONE;
// }
//
// // 模拟 draw_map 绘制函数
// int draw_map(void) {
//
//     char buffer[64];
//     uint32_t len = snprintf(buffer, sizeof(buffer), "draw_map\r\n");
//     HAL_UART_Transmit(&huart2, (uint8_t *)buffer, len, 100);
//
//     // 绘制简单图案：斜线 (x=y)
//     for (uint8_t i = 0; i < 64; i++) {
//         OLED_SetPixel(i, i, 0); // 点亮 (x, x)
//     }
//     return DISPLAY_DONE;
// }
//
// void test_update1() {
//     // 初始化帧缓冲区
//     display_set(NULL);
//     g_framebuffer = (uint8_t *)framebuffer; // 关联缓冲区
//     display_setDrawFunc(draw_map);
//
//     // 测试两次调用
//     display_update(); // 第一次绘制
//     HAL_Delay(10);    // 10ms 后
//     display_update(); // 应跳帧
//     HAL_Delay(33);    // 33ms 后
//     display_update(); // 再次绘制
// }
//
// // void display_update(void) {
// //     char buffer[64];
// //     uint32_t len;
// //
// //     // 帧率控制
// //     unsigned char now = HAL_GetTick();
// //     len = snprintf(buffer, sizeof(buffer), "current time: %u ms\r\n", now);
// //     HAL_UART_Transmit(&huart2, (uint8_t *)buffer, len, 100);
// //     if (now - lastDraw < fpsMs) {
// //         len = snprintf(buffer, sizeof(buffer), "skim frame (time: %u ms)\r\n", now - lastDraw);
// //         HAL_UART_Transmit(&huart2, (uint8_t *)buffer, len, 100);
// //         return;
// //     }
// //     lastDraw = now;
// //
// //     // 执行绘制
// //     display_t busy = DISPLAY_DONE;
// //     if (drawFunc) {
// //         busy = drawFunc();
// //         len = snprintf(buffer, sizeof(buffer), "drawFunc return: %d\r\n", busy);
// //         HAL_UART_Transmit(&huart2, (uint8_t *)buffer, len, 100);
// //     } else {
// //         len = snprintf(buffer, sizeof(buffer), "no  drawFunc\r\n");
// //         HAL_UART_Transmit(&huart2, (uint8_t *)buffer, len, 100);
// //     }
// //
// //     // 刷新 OLED
// //     draw_end();
// // }
