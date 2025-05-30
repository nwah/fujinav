#include <conio.h>
#include <stdint.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>
#include <stdio.h>
#include <fujinet-network.h>
#include "util.h"
#include "api.h"
#include "globals.h"
#include "check_settings.h"
#include "edit_settings.h"
#include "set_location.h"
#include "set_route_options.h"
#include "view_directions.h"
#include "print_directions.h"
#include "view_qr_code.h"
#include "ui.h"

char *version = "1.0.0";

int main() {
  network_init();
  ui_init();

  ui_screen_splash();
  while(1){}

  while (1) {
    switch (state) {
      case CHECK_SETTINGS:
        check_settings();
        break;
      case EDIT_SETTINGS:
        edit_settings();
        break;
      case SET_DESTINATION:
        set_destination();
        break;
      case SET_ORIGIN:
        set_origin();
        break;
      case SET_ROUTE_OPTIONS:
        set_route_options();
        break;
      case VIEW_DIRECTIONS:
        view_directions();
        break;
      case PRINT_DIRECTIONS:
        print_directions();
        break;
      case VIEW_QR_CODE:
        view_qr_code();
        break;
      default:
        break;
    }

    if (state == DONE) {
      break;
    }
  }

  return 0;
}
