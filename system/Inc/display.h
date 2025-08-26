//
// Created by 14419 on 25-8-17.
//

#ifndef DISPLAY_H
#define DISPLAY_H
#include "draw.h"


void display_set(display_f);
void display_load();

draw_f display_setDrawFunc(draw_f func);
void display_update(void);
#endif //DISPLAY_H
