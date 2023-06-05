#include "simple_oscilloscope.h"


lv_obj_t * chart_oscilloscope;
lv_chart_series_t * ser1;
lv_obj_t * label;

void lv_simple_oscilloscope()
{
	// 创建图表对象并将其添加到活动屏幕
    chart_oscilloscope = lv_chart_create(lv_scr_act());
	
    lv_obj_set_size(chart_oscilloscope, 200, 180);									// 设置图表对象的大小
	lv_obj_align_to(chart_oscilloscope, lv_scr_act(), LV_ALIGN_TOP_MID, 0, 30); 	// 将图表对齐到活动屏幕顶部中心，并从顶部偏移20个像素单位设置图表的类型为折线图
    lv_chart_set_type(chart_oscilloscope, LV_CHART_TYPE_LINE);						// 设置图表的类型为折线图
	lv_obj_set_style_size(chart_oscilloscope, 0, LV_PART_INDICATOR);				// 隐藏图表指示器
	lv_chart_set_point_count(chart_oscilloscope,BUFFER_SIZE);						// 设置图表上显示的点的数量
    lv_chart_set_div_line_count(chart_oscilloscope, 20, 20);						// 设置图表的分隔线数量

	// 向图表中添加数据序列
    ser1 = lv_chart_add_series(chart_oscilloscope, lv_palette_main(LV_PALETTE_BLUE), LV_CHART_AXIS_PRIMARY_Y);
	
	// 创建标签对象
	label = lv_label_create(lv_scr_act());
	
    lv_label_set_text(label, "Simple Oscilloscope");							// 设置标签的文本
    lv_obj_align_to(label, chart_oscilloscope, LV_ALIGN_OUT_TOP_MID, 0, 0);		// 将标签对齐到图表的顶部中心LV_ALIGN_OUT_RIGHT_MID
	
}

//void lv_update_value_mul(uint32_t adc_num, uint32_t* adc_value0)
//{
//    for(uint32_t i = 0; i < adc_num/8; i++)
//        lv_chart_set_next_value(chart_oscilloscope, ser1, adc_value0[i]*3.3f/4096*30);
//}

float waveform_buffer[BUFFER_SIZE];
uint32_t buffer_index = 0;

bool shouldUpdateSer1 = false;
extern bool shouldUpdateOsc;

void lv_update_value_mul(uint32_t adc_num, uint32_t* adc_value0)
{
    if(shouldUpdateSer1) {
		lv_obj_add_flag(chart_oscilloscope, LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(label, LV_OBJ_FLAG_HIDDEN);
		shouldUpdateSer1 = false;
		shouldUpdateOsc = false;
		user_file_debug("shouldUpdateOsc = false && shouldUpdateSer1 = false\n");
        return;
    }
	else
	{
		lv_obj_clear_flag(chart_oscilloscope, LV_OBJ_FLAG_HIDDEN);
		lv_obj_clear_flag(label, LV_OBJ_FLAG_HIDDEN);
	}

    for(uint32_t i = 0; i < adc_num/10; i++)
    {
        // 将样本添加到缓冲区
        waveform_buffer[buffer_index] = adc_value0[i]*3.3f/4096*30;
        buffer_index++;

        // 当缓冲区已满时，显示缓冲区中的波形
        if(buffer_index == BUFFER_SIZE)
        {
            for(uint32_t j = 0; j < BUFFER_SIZE; j++)
            {
                lv_chart_set_next_value(chart_oscilloscope, ser1, waveform_buffer[j]);
            }

            buffer_index = 0; // 重置缓冲区索引
        }
    }
}


void lv_simple_oscilloscope_hide_action()
{
	user_file_debug("lv_simple_oscilloscope_hide_action\n");
    shouldUpdateSer1 = true;
}

void lv_update_value(uint32_t value)
{
	for(uint32_t i = 0; i < 200; i++)
	{
        lv_chart_set_next_value(chart_oscilloscope, ser1, value);
//		lv_chart_set_next_value(chart_oscilloscope, ser2, adc_value1[i]*3.3f/4096*30+1.3);
	}
//	lv_chart_set_next_value(chart_oscilloscope, ser1, value*3.3f/4096*30);
}
