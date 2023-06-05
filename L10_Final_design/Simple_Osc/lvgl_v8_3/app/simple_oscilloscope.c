#include "simple_oscilloscope.h"


lv_obj_t * chart_oscilloscope;
lv_chart_series_t * ser1;
lv_obj_t * label;

void lv_simple_oscilloscope()
{
	// ����ͼ����󲢽�����ӵ����Ļ
    chart_oscilloscope = lv_chart_create(lv_scr_act());
	
    lv_obj_set_size(chart_oscilloscope, 200, 180);									// ����ͼ�����Ĵ�С
	lv_obj_align_to(chart_oscilloscope, lv_scr_act(), LV_ALIGN_TOP_MID, 0, 30); 	// ��ͼ����뵽���Ļ�������ģ����Ӷ���ƫ��20�����ص�λ����ͼ�������Ϊ����ͼ
    lv_chart_set_type(chart_oscilloscope, LV_CHART_TYPE_LINE);						// ����ͼ�������Ϊ����ͼ
	lv_obj_set_style_size(chart_oscilloscope, 0, LV_PART_INDICATOR);				// ����ͼ��ָʾ��
	lv_chart_set_point_count(chart_oscilloscope,BUFFER_SIZE);						// ����ͼ������ʾ�ĵ������
    lv_chart_set_div_line_count(chart_oscilloscope, 20, 20);						// ����ͼ��ķָ�������

	// ��ͼ���������������
    ser1 = lv_chart_add_series(chart_oscilloscope, lv_palette_main(LV_PALETTE_BLUE), LV_CHART_AXIS_PRIMARY_Y);
	
	// ������ǩ����
	label = lv_label_create(lv_scr_act());
	
    lv_label_set_text(label, "Simple Oscilloscope");							// ���ñ�ǩ���ı�
    lv_obj_align_to(label, chart_oscilloscope, LV_ALIGN_OUT_TOP_MID, 0, 0);		// ����ǩ���뵽ͼ��Ķ�������LV_ALIGN_OUT_RIGHT_MID
	
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
        // ��������ӵ�������
        waveform_buffer[buffer_index] = adc_value0[i]*3.3f/4096*30;
        buffer_index++;

        // ������������ʱ����ʾ�������еĲ���
        if(buffer_index == BUFFER_SIZE)
        {
            for(uint32_t j = 0; j < BUFFER_SIZE; j++)
            {
                lv_chart_set_next_value(chart_oscilloscope, ser1, waveform_buffer[j]);
            }

            buffer_index = 0; // ���û���������
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
