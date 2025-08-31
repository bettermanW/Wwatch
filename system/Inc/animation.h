//
// Created by 14419 on 25-8-31.
//

#ifndef ANIMATION_H
#define ANIMATION_H
#include "config.h"
#include "typedef.h"
#include "stddef.h"
#include "appconfig.h"

#define ANIM_MOVE_OFF	true
#define ANIM_MOVE_ON	false

#if COMPILE_ANIMATIONS

void animation_init(void);
void animation_update(void);
void animation_start(void (*animOnComplete)(void), bool);
bool animation_active(void);
bool animation_movingOn(void);
uint8_t animation_offsetY(void);

#else

#define animation_active() (false)
#define animation_movingOn() (false)
#define animation_offsetY() (0)

void animation_start(void (*animOnComplete)(void), bool goingOffScreen);

#endif

#endif //ANIMATION_H
