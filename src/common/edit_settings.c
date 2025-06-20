#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <conio.h>
#include <fujinet-fuji.h>

#include "edit_settings.h"
#include "globals.h"
#include "typedefs.h"
#include "ui.h"

// TODO: This seems dumb
#ifndef CH_TAB
#define CH_TAB 0x09
#endif

#define DONE 0
#define SERVER 1
#define UNITS 2

uint8_t settings_state = SERVER;

void edit_server() {
  char c;
  bool ok;
  uint8_t err;

  ui_screen_settings_menu_default();

  ui_screen_settings_focus_server();

  while (c != CH_ENTER) {
    while (!kbhit());
    c = cgetc();

    if (c == CH_ESC) {
      settings_state = DONE;
      return;
    }
    else if (c == CH_TAB) {
      settings_state = UNITS;
      return;
    }
  }

  ui_screen_settings_menu_editing();

  err = ui_screen_settings_edit_server(settings.server);

  ui_screen_settings_menu_default();

  if (err == ERR_ABORTED) {
    settings_state = DONE;
    state = SET_DESTINATION;
    return;
  }

  ok = fuji_write_appkey(APPKEY_ID_API_URL, strlen(settings.server), settings.server);
  if (!ok) {
    ui_screen_settings_show_error("Error saving server URL");
    cgetc();
    return;
  }

  ui_screen_settings_render_server();

  settings_state = UNITS;
}

void edit_units() {
  bool ok;
  uint8_t err;
  char old_units[3];
  char c;

  ui_screen_settings_menu_editing();

  strcpy(old_units, routeOptions.units);
  ui_screen_settings_focus_units();

  while (1) {
    c = cgetc();
    switch (c) {
    case CH_TAB:
      settings_state = SERVER;
      return;
    case CH_ESC:
      settings_state = SERVER;
      strcpy(routeOptions.units, old_units);
      return;
    case CH_ENTER:
      ok = fuji_write_appkey(APPKEY_ID_UNITS, 3, routeOptions.units);
      if (!ok) {
        ui_screen_settings_show_error("Error saving units");
        cgetc();
        return;
      }
      settings_state = DONE;
      return;
    case CH_CURS_RIGHT:
    case 'k':
    case 'K':
      strcpy(routeOptions.units, "km");
      ui_screen_settings_render_units();
      break;
    case CH_CURS_LEFT:
    case 'm':
    case 'M':
      strcpy(routeOptions.units, "mi");
      ui_screen_settings_render_units();
      break;
    default:
      break;
    }
  }
}

void edit_settings(void) {
  settings_state = SERVER;

  ui_screen_settings();
  ui_screen_settings_menu_default();

  while (settings_state != DONE) {
    switch (settings_state) {
      case SERVER:
        edit_server();
        break;
      case UNITS:
        edit_units();
        break;
      default:
        settings_state = DONE;
        break;
    }
  }

  state = SET_DESTINATION;
}
