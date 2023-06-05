#include "picture.h"

lv_obj_t * obj_img_wechat_donate;
lv_obj_t * label_1;
void img_wechat_donate(void)
{
	LV_IMG_DECLARE(wechat_donate);
    obj_img_wechat_donate = lv_img_create(lv_scr_act());
    lv_img_set_src(obj_img_wechat_donate, &wechat_donate);
	lv_obj_align(obj_img_wechat_donate, LV_ALIGN_TOP_MID, 0, 30);
	
	label_1 = lv_label_create(lv_scr_act());
    lv_label_set_text(label_1,"Buy me a cup of coffee!");
	lv_obj_align_to(label_1, obj_img_wechat_donate, LV_ALIGN_OUT_BOTTOM_MID, 0, 20);
}

void img_wechat_donate_hide_action()
{
	lv_obj_add_flag(obj_img_wechat_donate, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(label_1, LV_OBJ_FLAG_HIDDEN);
}

lv_obj_t * obj_img_chathead;
lv_obj_t * label_name;
lv_obj_t * label_number;
lv_obj_t * label_my_github;
void img_chat_head(void)
{
    LV_IMG_DECLARE(chathead);
    obj_img_chathead = lv_img_create(lv_scr_act());
    lv_img_set_src(obj_img_chathead, &chathead);
	
    lv_obj_align(obj_img_chathead, LV_ALIGN_DEFAULT, 10, 20);
	
	label_name = lv_label_create(lv_scr_act());
    lv_label_set_text(label_name,"name: \nQiu Jinyu");
	lv_obj_align_to(label_name, obj_img_chathead, LV_ALIGN_OUT_RIGHT_TOP, 10, 0);
	
	label_number = lv_label_create(lv_scr_act());
    lv_label_set_text(label_number,"number: \n2038010061");
	lv_obj_align_to(label_number, obj_img_chathead, LV_ALIGN_OUT_RIGHT_TOP, 10, 40);
	
	label_my_github = lv_label_create(lv_scr_act());
    lv_label_set_text(label_my_github,"GitHub: \nhttps://github.com/Y006");
	lv_obj_align_to(label_my_github, obj_img_chathead, LV_ALIGN_OUT_BOTTOM_LEFT, 10, 10);
}

void img_chat_head_hide_action()
{
	lv_obj_add_flag(obj_img_chathead, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(label_name, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(label_number, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(label_my_github, LV_OBJ_FLAG_HIDDEN);
}
//void img_icons8_oscilloscope_64(void)
//{
//	LV_IMG_DECLARE(icons8_oscilloscope_64);
//    lv_obj_t * img_icons8_oscilloscope_64 = lv_img_create(lv_scr_act());
//    lv_img_set_src(img_icons8_oscilloscope_64, &icons8_oscilloscope_64);
//	lv_obj_align(img_icons8_oscilloscope_64, LV_ALIGN_TOP_MID, 0, 40);
//	
//	lv_obj_t * label_name = lv_label_create(lv_scr_act());
//    lv_label_set_text(label_name,"Simple Oscilloscope");
//	lv_obj_align_to(label_name, obj_img_wechat_donate, LV_ALIGN_OUT_BOTTOM_MID, 0, 20);
//	
//	lv_obj_t * label_func = lv_label_create(lv_scr_act());
//    lv_label_set_text(label_func,"Function: \n\t1. Display waveform.\n\t2. Multiple channels can\n\t    be added.\n\t3. Amplitude: 0-3.3V.\n\t4. Frequency: 0-1Hz.");
//	lv_obj_align_to(label_func, obj_img_wechat_donate, LV_ALIGN_OUT_BOTTOM_MID, -10, 40);
//}

static void event_handler(lv_event_t * e)
{
    lv_event_code_t code = lv_event_get_code(e);

    if(code == LV_EVENT_CLICKED) {
        LV_LOG_USER("Clicked");
    }
}

lv_obj_t * btn_osc;
lv_obj_t * obj_img_icons8_oscilloscope_64;
lv_obj_t * label_name_2;
lv_obj_t * label_func;
lv_obj_t * obj_img_icons8_back_100;
lv_obj_t * obj_img_icons8_forward_100;

void img_icons8_oscilloscope_64(void)
{
    btn_osc = lv_btn_create(lv_scr_act());
	lv_obj_set_style_bg_color(btn_osc,lv_color_hex(0xe8e8e8),LV_PART_MAIN);
	lv_obj_align(btn_osc, LV_ALIGN_TOP_MID, 0, 40);
	lv_obj_set_size(btn_osc, 110, 72);
	
    lv_obj_add_event_cb(btn_osc, event_handler, LV_EVENT_ALL, NULL);
	
	LV_IMG_DECLARE(icons8_oscilloscope_64);
    obj_img_icons8_oscilloscope_64 = lv_img_create(lv_scr_act());
    lv_img_set_src(obj_img_icons8_oscilloscope_64, &icons8_oscilloscope_64);

	lv_obj_align_to(obj_img_icons8_oscilloscope_64, btn_osc, LV_ALIGN_CENTER, 0, 0);
	
	label_name_2 = lv_label_create(lv_scr_act());
    lv_label_set_text(label_name_2,"Simple Oscilloscope");
	lv_obj_align_to(label_name_2, btn_osc, LV_ALIGN_OUT_BOTTOM_MID, 0, 20);
	
	label_func = lv_label_create(lv_scr_act());
    lv_label_set_text(label_func,"Function: \n\t1. Display waveform.\n\t2. Multiple channels can\n\t    be added.\n\t3. Amplitude: 0 - 3.3V.\n\t4. Frequency: 0 - 1Hz.");
	lv_obj_align_to(label_func, btn_osc, LV_ALIGN_OUT_BOTTOM_MID, -10, 40);
	
	
	LV_IMG_DECLARE(icons8_back_100);
    obj_img_icons8_back_100 = lv_img_create(lv_scr_act());
    lv_img_set_src(obj_img_icons8_back_100, &icons8_back_100);
	lv_obj_align(obj_img_icons8_back_100, LV_ALIGN_TOP_LEFT, -10, 42);

	LV_IMG_DECLARE(icons8_forward_100);
    obj_img_icons8_forward_100 = lv_img_create(lv_scr_act());
    lv_img_set_src(obj_img_icons8_forward_100, &icons8_forward_100);
	lv_obj_align(obj_img_icons8_forward_100, LV_ALIGN_TOP_RIGHT, 10, 42);\
//	HAL_Delay(1000);
//	lv_obj_add_flag(btn_osc, LV_OBJ_FLAG_HIDDEN);
//    lv_obj_add_flag(obj_img_icons8_oscilloscope_64, LV_OBJ_FLAG_HIDDEN);
//    lv_obj_add_flag(label_name, LV_OBJ_FLAG_HIDDEN);
//    lv_obj_add_flag(label_func, LV_OBJ_FLAG_HIDDEN);
//    lv_obj_add_flag(obj_img_icons8_back_100, LV_OBJ_FLAG_HIDDEN);
//    lv_obj_add_flag(obj_img_icons8_forward_100, LV_OBJ_FLAG_HIDDEN);
}

void img_icons8_oscilloscope_64_hide_action() 
{
	user_main_debug("img_icons8_oscilloscope_64_hide_action\n");
    // implement the hide action for img_icons8_oscilloscope_64
    lv_obj_add_flag(btn_osc, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(obj_img_icons8_oscilloscope_64, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(label_name_2, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(label_func, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(obj_img_icons8_back_100, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(obj_img_icons8_forward_100, LV_OBJ_FLAG_HIDDEN);
}




