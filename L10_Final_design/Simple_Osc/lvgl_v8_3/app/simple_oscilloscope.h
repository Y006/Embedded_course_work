#ifndef SIMPLE_OSCILLOSCOPE
#define SIMPLE_OSCILLOSCOPE

#include "lvgl.h"
#include "lv_port_disp_template.h"
#include "lv_port_indev_template.h"
#include "user_log.h"

#define BUFFER_SIZE 100 // 缓冲区的大小

void lv_simple_oscilloscope();
void lv_update_value(uint32_t value);
void lv_update_value_mul(uint32_t adc_num, uint32_t* adc_value0);
void lv_update_value_mul_f(uint32_t adc_num, float* adc_value0);
void lv_simple_oscilloscope_hide_action();
#endif
