#include "buzzer.h"

#define BUZZER_CHANNEL TIM_CHANNEL_4
extern appconfig_s appConfig;
extern TIM_HandleTypeDef htim4;
static TIM_HandleTypeDef *g_HPWM_PassiveBuzzer = &htim4;

// === 状态管理变量 ===
static uint32_t buzzLen = 0;       // 响铃时长（ms）
static uint32_t startTime = 0;     // 开始时间
static tonePrio_t prio = PRIO_MIN; // 当前优先级
static buzzFinish_f onFinish = NULL; // 响铃结束回调

// === 辅助函数声明 ===
static void stop(void);

/**
 * @brief 控制蜂鸣器开/关
 */
static void PassiveBuzzer_Control(const int on) {
    if (on) {
        HAL_TIM_PWM_Start(g_HPWM_PassiveBuzzer, BUZZER_CHANNEL);
    } else {
        HAL_TIM_PWM_Stop(g_HPWM_PassiveBuzzer, BUZZER_CHANNEL);
    }
}

/**
 * @brief 设置蜂鸣器的频率与占空比
 * @param freq 频率 Hz
 * @param duty 占空比 (0~100 %)
 */
static void PassiveBuzzer_Set_Freq_Duty(const uint32_t freq, const uint8_t duty) {
    if (freq == 0 || duty == 0) {
        PassiveBuzzer_Control(0);
        return;
    }

    // 周期 (ARR) = 1MHz / freq - 1
    const uint32_t period = 1000000 / freq - 1;
    const uint32_t pulse  = period * duty / 100; // CCR

    __HAL_TIM_SET_AUTORELOAD(g_HPWM_PassiveBuzzer, period);
    __HAL_TIM_SET_COMPARE(g_HPWM_PassiveBuzzer, BUZZER_CHANNEL, pulse);

    PassiveBuzzer_Control(1);
}

/**
 * @brief 开始一次响铃
 * @param len 持续时间 (ms)
 * @param tone 频率 (Hz)，特殊值 TONE_STOP/TONE_PAUSE
 * @param volType 音量 (0~100 %)
 * @param _prio 优先级
 * @param _onFinish 结束回调
 */
void buzzer_buzz(const uint32_t len, const tone_t tone, const tonePrio_t volType,
                 const tonePrio_t _prio, const buzzFinish_f _onFinish) {
    // 忽略低优先级
    if (_prio < prio) {
        return;
    }

    // 停止
    if (tone == TONE_STOP) {
        stop();
        return;
    }

    // 更新状态
    prio      = _prio;
    onFinish  = _onFinish;
    buzzLen   = len;
    startTime = HAL_GetTick();

    // 静音模式
    if (tone == TONE_PAUSE) {
        PassiveBuzzer_Control(0);
        return;
    }
    uint8_t vol;
    switch(volType)
    {
        case VOL_UI:
            vol = appConfig.volUI * 15;
            break;
        case VOL_ALARM:
            vol = appConfig.volAlarm * 15;
            break;
        case VOL_HOUR:
            vol = appConfig.volHour * 15;
            break;
        default:
            vol =  2 * 15;
            break;
    }


    // 设置频率和占空比
    PassiveBuzzer_Set_Freq_Duty(tone, vol);
}

/**
 * @brief 判断蜂鸣器是否正在响
 */
bool buzzer_buzzering(void) {
    return buzzLen > 0;
}

/**
 * @brief 定期调用，检查蜂鸣器是否到时
 */
void buzzer_update(void) {
    if (buzzLen > 0 && (HAL_GetTick() - startTime) >= buzzLen) {
        stop();
        if (onFinish != NULL) {
            onFinish();
        }
    }
}

/**
 * @brief 停止蜂鸣器
*/
static void stop(void) {
    PassiveBuzzer_Control(0);
    buzzLen = 0;
    prio    = PRIO_MIN;
    onFinish = NULL;
}



