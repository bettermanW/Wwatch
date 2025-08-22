//
// Created by 14419 on 25-8-22.
//

#ifndef RESOURSE_H
#define RESOURSE_H

#include <stdint.h>

#define SMALLFONT_WIDTH 5
#define SMALLFONT_HEIGHT 8
extern const uint8_t small2Font[][22];

#define MIDFONT_WIDTH 19
#define MIDFONT_HEIGHT 24
extern const uint8_t midFont[][57];

#define FONT_COLON_WIDTH 6
#define FONT_COLON_HEIGHT 24
extern const uint8_t colon[];

uint8_t div10(const uint8_t val);

uint8_t mod10(const uint8_t val);

#endif //RESOURSE_H
