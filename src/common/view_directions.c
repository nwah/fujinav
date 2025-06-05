#include <conio.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "view_directions.h"
#include "api.h"
#include "globals.h"
#include "typedefs.h"
#include "ui.h"
#include "printer.h"

void view_directions(void) {
    char c;
    bool waiting = true;

    ui_screen_directions();

    ui_screen_directions_show_routing();
    api_route(fromLoc.latlng, toLoc.latlng, &routeOptions);

    ui_screen_directions_show_results();
    ui_screen_directions_menu_default();

    while (waiting) {
      waiting = false;
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
        case CH_ESC:
          state = SET_DESTINATION;
          break;
        case CH_CURS_UP:
        case 'i':
        case 'I':
          waiting = true;
          ui_screen_directions_scroll_up();
          break;
        case CH_CURS_DOWN:
        case 'k':
        case 'K':
          waiting = true;
          ui_screen_directions_scroll_down();
          break;
        case 'p':
        case 'P':
            state = PRINT_DIRECTIONS;
            break;
        default:
          waiting = true;
          break;
      }
    }
}
