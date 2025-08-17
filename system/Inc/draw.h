//
// Created by 14419 on 25-8-13.
//

#ifndef DRAW_H
#define DRAW_H
#include  "oled.h"
#include "stdbool.h"
#include "ulti.h"


void draw_init();
void draw_end();

void draw_bitmap(uint8_t x, uint8_t yy, const uint8_t* bitmap, uint8_t w, uint8_t h, bool invert, uint8_t offsetY);

// 暂时
uint8_t readPixels(const uint8_t* loc, bool invert);

#endif //DRAW_H
