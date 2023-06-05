#include "init_menu.h"

lv_obj_t * arc_init;
lv_anim_t anim_arc, anim_size, anim_size_2;
lv_obj_t *label1;
 
static void set_arc_angle(void * obj, int32_t v)
{
    lv_arc_set_value(obj, v);
}

static void set_arc_size(void * obj, int32_t value) 
{
    lv_obj_set_size(obj, value, value);
}

void animation_complete_callback_2(lv_anim_t *anim)
{
    lv_obj_t *arc = anim->var;
    label1 = lv_label_create(lv_scr_act());

    lv_label_set_text(label1, "Click to Start!");
    lv_obj_align_to(label1, arc, LV_ALIGN_CENTER, 0, 0);
    
    lv_anim_init(&anim_size_2);
    lv_anim_set_var(&anim_size_2, arc);
    lv_anim_set_exec_cb(&anim_size_2, set_arc_size);
    lv_anim_set_time(&anim_size_2, 40);
    lv_anim_set_repeat_count(&anim_size_2, 1);
    lv_anim_set_values(&anim_size_2, 200, 220);
    lv_anim_start(&anim_size_2);
}

void animation_complete_callback(lv_anim_t *anim)
{
    lv_obj_t *arc = anim->var;

    lv_anim_init(&anim_size);
    lv_anim_set_var(&anim_size, arc);
    lv_anim_set_exec_cb(&anim_size, set_arc_size);
    lv_anim_set_time(&anim_size, 200);
    lv_anim_set_repeat_count(&anim_size, 1);
    lv_anim_set_values(&anim_size, 100, 200);
    lv_anim_set_ready_cb(&anim_size, animation_complete_callback_2);
    lv_anim_start(&anim_size);
}

lv_obj_t* init_anim(void)
{
    arc_init = lv_arc_create(lv_scr_act());
	
    lv_arc_set_rotation(arc_init, 270);
    lv_arc_set_bg_angles(arc_init, 0, 360);
    lv_obj_remove_style(arc_init, NULL, LV_PART_KNOB);
    lv_obj_clear_flag(arc_init, LV_OBJ_FLAG_CLICKABLE);
    lv_obj_set_size(arc_init, 100, 100);
    lv_obj_center(arc_init);

    lv_anim_init(&anim_arc);
    lv_anim_set_var(&anim_arc, arc_init);
    lv_anim_set_exec_cb(&anim_arc, set_arc_angle);
    lv_anim_set_time(&anim_arc, 2000);
    lv_anim_set_repeat_count(&anim_arc, 1);
    lv_anim_set_values(&anim_arc, 0, 100);
    lv_anim_set_ready_cb(&anim_arc, animation_complete_callback);
    lv_anim_start(&anim_arc);
	
	return arc_init;
}
extern bool ClickToStart;

void cleanup_lvgl_components() 
{
	if(ClickToStart)
	{
		lv_obj_add_flag(arc_init, LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(label1, LV_OBJ_FLAG_HIDDEN);
	}
	
	else
	{
		lv_obj_clear_flag(arc_init, LV_OBJ_FLAG_HIDDEN);
		lv_obj_clear_flag(label1, LV_OBJ_FLAG_HIDDEN);
	}
}

void init_anim_hide_action() 
{
    // implement the hide action for init_anim
	lv_obj_add_flag(arc_init, LV_OBJ_FLAG_HIDDEN);
	lv_obj_add_flag(label1, LV_OBJ_FLAG_HIDDEN);
}

