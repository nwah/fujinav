#include <conio.h>
#include <stdio.h>
#include <string.h>
#include "set_route_options.h"
#include "typedefs.h"
#include "ui.h"
#include "globals.h"

void set_route_options(void) {
    char c;
    ui_screen_route_options(&routeOptions);

    c = cgetc();
    switch (c) {
      case 't':
      case 'T':
        strcpy(routeOptions.mode, MODE_TRANSIT);
        break;
      case 'b':
      case 'B':
        strcpy(routeOptions.mode, MODE_BIKING);
        break;
      case 'd':
      case 'D':
      case 'c':
      case 'C':
        strcpy(routeOptions.mode, MODE_DRIVING);
        break;
      case 'w':
      case 'W':
        strcpy(routeOptions.mode, MODE_WALKING);
        break;
      case CH_ENTER:
        state = VIEW_DIRECTIONS;
        break;
      default:
        break;
    }
}
