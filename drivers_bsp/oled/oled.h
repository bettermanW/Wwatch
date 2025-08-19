//
// Created by 14419 on 25-8-12.
//

#ifndef OLED_H
#define OLED_H

#include "string.h"
#include "i2c.h"
#include <math.h>
#include <stdlib.h>
#include <stdint.h>

typedef enum {
    OLED_COLOR_NORMAL = 0, // 正常模式 黑底白字
    OLED_COLOR_REVERSED    // 反色模式 白底黑字
  } OLED_ColorMode;

void OLED_Init();
void OLED_DisPlay_On();
void OLED_DisPlay_Off();
void OLED_SetColorMode(OLED_ColorMode mode);

void OLED_NewFrame();
void OLED_ShowFrame();

void OLED_SetPixel(uint8_t x, uint8_t y, OLED_ColorMode color);
void OLED_DrawLine(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, OLED_ColorMode color);

void * OLED_GetFrameBuffer(uint32_t *pXres, uint32_t *pYres, uint32_t *pBpp);
#endif //OLED_H
