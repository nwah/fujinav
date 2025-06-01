#include <conio.h>
#include <stdio.h>
#include "edit_settings.h"
#include "globals.h"
#include "ui.h"

void edit_settings(void) {
    ui_screen_settings();
    ui_screen_settings_menu_default();
    cgetc();
    state = SET_DESTINATION;
} 