#include "user_pwm.h"

PWMError set_pwm(TIM_HandleTypeDef *htim, uint32_t channel, uint32_t target_frequency, float target_duty_cycle) {
    uint32_t prescaler, period, pulse;

    // Calculate prescaler
    prescaler = (SystemCoreClock / (target_frequency * (1 << 16))) - 1;

    // Check if prescaler is within the allowed range
    if (prescaler > MAX_PRESCALER) {
        return PWM_ERROR_PRESCALER_OUT_OF_RANGE;
    }

    // Calculate period
    period = (SystemCoreClock / (target_frequency * (prescaler + 1))) - 1;

    // Check if period is within the allowed range
    if (period > MAX_PERIOD) {
        return PWM_ERROR_PERIOD_OUT_OF_RANGE;
    }

    // Calculate pulse
    pulse = (uint32_t)(((float)target_duty_cycle / 100.0) * (float)(period + 1));

    // Check if pulse is within the allowed range
    if (pulse > MAX_PULSE) {
        return PWM_ERROR_PULSE_OUT_OF_RANGE;
    }

    // Set PWM parameters
    __HAL_TIM_SET_PRESCALER(htim, prescaler);
    __HAL_TIM_SET_AUTORELOAD(htim, period);
    __HAL_TIM_SetCompare(htim, channel, pulse);
	
	HAL_TIM_GenerateEvent(htim, TIM_EVENTSOURCE_UPDATE);
	
    return PWM_OK;
}

//void set_pwm_error_print(uint32_t target_frequency, float target_duty_cycle) {
//	
//    PWMError status = set_pwm(&htim2, TIM_CHANNEL_1, target_frequency, target_duty_cycle);
//    
//    switch (status) {
//        case PWM_OK:
//            printf("PWM has been set successfully.\n");
//            break;
//        case PWM_ERROR_PRESCALER_OUT_OF_RANGE:
//            printf("Error: Prescaler value is out of range.\n");
//            break;
//        case PWM_ERROR_PERIOD_OUT_OF_RANGE:
//            printf("Error: Period value is out of range.\n");
//            break;
//        case PWM_ERROR_PULSE_OUT_OF_RANGE:
//            printf("Error: Pulse value is out of range.\n");
//            break;
//        default:
//            printf("Unknown error.\n");
//    }
//}
