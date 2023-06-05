#ifndef INIT_MENU_H
#define INIT_MENU_H

#include "lvgl.h"
#include "lv_port_disp_template.h"
#include "lv_port_indev_template.h"

//void init_anim();
lv_obj_t * init_anim();
//void cleanup_lvgl_components(lv_obj_t * obj);
//void cleanup_lvgl_components(void);
void cleanup_lvgl_components();

void init_anim_hide_action() ;

#endif
