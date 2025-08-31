//
// Created by 14419 on 25-8-31.
//
#include "tune.h"


static uint8_t idx;          // 当前播放索引
static const tune_t* tune;   // 当前曲调指针
static vol_t vol;            // 音量类型
static tonePrio_t prio;      // 当前优先级

static void next(void);

// 播放曲调
void tune_play(const tune_t* _tune, vol_t _vol, tonePrio_t _prio)
{
    if (_prio < prio) return;  // 当前优先级低于正在播放的 → 忽略

    prio  = _prio;
    tune  = _tune;
    vol   = _vol;
    idx   = 0;

    next(); // 播放第一个音符
}

// 停止曲调
void tune_stop(tonePrio_t _prio)
{
    buzzer_buzz(0, TONE_STOP, VOL_OTHER, _prio, NULL);
    prio = PRIO_MIN;
}

// 播放下一个音符
static void next()
{
    uint16_t data = (tune[idx++]);  // STM32 Flash 直接读取
    uint8_t len   = data & 0xFF;             // 音符时长
    tone_t tone   = (tone_t)(data >> 8);     // 音调频率

    if (len == TONE_REPEAT)
    {
        // 循环播放
        idx = 0;
        next();
    }
    else
    {
        // 播放音符
        buzzer_buzz(len, tone, vol, prio, next);

        // 如果是立即停止
        if(len == TONE_STOP)
        {
            prio = PRIO_MIN;
        }
    }
}
