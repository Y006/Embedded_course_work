#ifndef USER_PWM_H
#define USER_PWM_H

#include "main.h"
#include <stdio.h>
#include "tim.h"

#define MAX_PRESCALER 65535
#define MAX_PERIOD 4294967295
#define MAX_PULSE 4294967295

typedef enum {
    PWM_OK,
    PWM_ERROR_PRESCALER_OUT_OF_RANGE,
    PWM_ERROR_PERIOD_OUT_OF_RANGE,
    PWM_ERROR_PULSE_OUT_OF_RANGE
} PWMError;

PWMError set_pwm(TIM_HandleTypeDef* htim, uint32_t channel, uint32_t target_frequency, float target_duty_cycle);
//void set_pwm_error_print(uint32_t target_frequency, float target_duty_cycle);

#endif // USER_PWM_H
