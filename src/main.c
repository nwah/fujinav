#include <conio.h>
#include <stdbool.h>
#include <fujinet-network.h>
#include "api.h"
#include "common/typedefs.h"
#include "globals.h"
#include "check_settings.h"
#include "edit_settings.h"
#include "set_location.h"
#include "view_directions.h"
#include "print_directions.h"
#include "view_qr_code.h"
#include "ui.h"
// #include "printer.h"

char *version = "1.0.0";

int main() {
  network_init();
  ui_init();

  state = CHECK_SETTINGS;

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
