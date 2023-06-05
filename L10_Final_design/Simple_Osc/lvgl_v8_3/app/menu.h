//#ifndef MENU_H
//#define MENU_H

//#include "main.h"
//#include "lvgl.h"
//#include "lv_port_disp_template.h"
//#include "lv_port_indev_template.h"


//typedef struct MenuItem MenuItem;

//struct MenuItem {
//    void (*action)(void);
//    MenuItem *subMenu;
//    MenuItem *prev;
//    MenuItem *next;
//};

//void menu_error(void);
//void menu_init(MenuItem *menu);
//void menu_next(MenuItem **currentMenu);
//void menu_prev(MenuItem **currentMenu);
//void menu_select(MenuItem **currentMenu);
//void menu_back(MenuItem **currentMenu);

//#endif // MENU_H
#ifndef MENU_H
#define MENU_H

#include "main.h"
#include "lvgl.h"
#include "lv_port_disp_template.h"
#include "lv_port_indev_template.h"
#include "stdio.h"


typedef struct MenuItem MenuItem;

struct MenuItem {
    void (*action)(void);
    void (*hide_action)(void); // New function pointer for hiding previous active page
    MenuItem *subMenu;
    MenuItem *parentMenu;
    MenuItem *prev;
    MenuItem *next;
};

void menu_error(void);
void menu_init(MenuItem *menu);
void menu_next(MenuItem **currentMenu);
void menu_prev(MenuItem **currentMenu);
void menu_select(MenuItem **currentMenu);
void menu_back(MenuItem **currentMenu);

#endif // MENU_H
