//#include "menu.h"

//void menu_error(void) {
//    // Implement the error menu here.
//}

//void menu_init(MenuItem *menu) {
//    // Initialize the menu here.
//}

//void menu_next(MenuItem **currentMenu) {
//    if ((*currentMenu)->next == NULL) {
//        menu_error();
//    } else {
//        *currentMenu = (*currentMenu)->next;
//        (*currentMenu)->action();
//    }
//}

//void menu_prev(MenuItem **currentMenu) {
//    if ((*currentMenu)->prev == NULL) {
//        menu_error();
//    } else {
//        *currentMenu = (*currentMenu)->prev;
//        (*currentMenu)->action();
//    }
//}

//void menu_select(MenuItem **currentMenu) {
//    if ((*currentMenu)->subMenu == NULL) {
//        menu_error();
//    } else {
//        *currentMenu = (*currentMenu)->subMenu;
//        (*currentMenu)->action();
//    }
//}

//void menu_back(MenuItem **currentMenu) {
//    // Implement the logic to go back to the parent menu.
//}

#include "menu.h"

static uint32_t error_cnt = 0;
void menu_error(void) {
	error_cnt++;
    user_main_debug("error %d\n",error_cnt);
}

void menu_init(MenuItem *menu) {
    // Initialize the menu here.
}

void menu_next(MenuItem **currentMenu) {
    if ((*currentMenu)->next == NULL) {
        menu_error();
    } else {
        // Hide current active page before moving to the next
        if ((*currentMenu)->hide_action != NULL) {
            (*currentMenu)->hide_action();
        }
        *currentMenu = (*currentMenu)->next;
        (*currentMenu)->action();
    }
}

void menu_prev(MenuItem **currentMenu) {
    if ((*currentMenu)->prev == NULL) {
        menu_error();
    } else {
        // Hide current active page before moving to the previous
        if ((*currentMenu)->hide_action != NULL) {
            (*currentMenu)->hide_action();
        }
        *currentMenu = (*currentMenu)->prev;
        (*currentMenu)->action();
    }
}

void menu_select(MenuItem **currentMenu) {
    if ((*currentMenu)->subMenu == NULL) {
        menu_error();
    } else {
        // Hide current active page before moving to the submenu
        if ((*currentMenu)->hide_action != NULL) {
			user_main_debug("hide_action");
            (*currentMenu)->hide_action();
        }
        *currentMenu = (*currentMenu)->subMenu;
        (*currentMenu)->action();
    }
}

void menu_back(MenuItem **currentMenu) {
    if ((*currentMenu)->parentMenu == NULL) {
        menu_error();
    } else {
        // Hide current active page before moving back to the parent menu
        if ((*currentMenu)->hide_action != NULL) {
            (*currentMenu)->hide_action();
        }
        *currentMenu = (*currentMenu)->parentMenu;
        (*currentMenu)->action();
    }
}
