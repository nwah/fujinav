#include <conio.h>
#include <stdio.h>
#include "edit_settings.h"
#include "globals.h"
#include "ui.h"

void edit_settings(void) {
    ui_screen_settings();
    cgetc();
    state = SET_DESTINATION;
} 