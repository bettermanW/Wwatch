//
// Created by 14419 on 25-8-29.
//

#ifndef APPCONFIG_H
#define APPCONFIG_H
#include "typedef.h"
#include "eeprom.h"

// EEPROM 虚拟地址分配（每个字段一个16位地址）
#define EE_ADDR_SLEEP_TIMEOUT   0x0001
#define EE_ADDR_INVERT          0x0002
#define EE_ADDR_ANIMATIONS      0x0003
#define EE_ADDR_DISPLAY180      0x0004
#define EE_ADDR_CTRL_LEDS       0x0005
#define EE_ADDR_SHOWFPS         0x0006
#define EE_ADDR_TIMEMODE        0x0007
#define EE_ADDR_VOLUMES         0x0008



void appconfig_init(void);
void appconfig_save(void);
void appconfig_reset(void);
#endif //APPCONFIG_H
