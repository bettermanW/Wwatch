//
// Created by 14419 on 25-8-14.
//

#ifndef ULTI_H
#define ULTI_H
#include <stdint.h>
/*
 * 简化for循环，常用于遍历数组或屏幕像素
 */
// 正序循环：val 从 0 到 count - 1
#define LOOP(count, var)  for (uint32_t var = 0; (var) < (count); ++(var))

// 倒序循环：val 从 count - 1 到 0，闭区间
#define LOOPR(count, var) for (int32_t var = (int32_t)(count) - 1; (var) >= 0; --(var))
#endif //ULTI_H
