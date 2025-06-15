#include <atari.h>
#include <peekpoke.h>
#include <stdint.h>
#include "globals.h"
#include "typedefs.h"
#include "screen.h"
#include "ui_core.h"

void text_with_highlight = {
  DL_BLK8, DL_BLK8, DL_BLK8,
  DL_LMS(DL_CHR40x8x1), scr_mem,
  DL_CHR40x8x1, DL_CHR40x8x1, DL_CHR40x8x1,
  DL_CHR40x8x1, DL_CHR40x8x1, DL_CHR40x8x1, DL_CHR40x8x1,
  DL_CHR40x8x1, DL_CHR40x8x1, DL_CHR40x8x1, DL_CHR40x8x1,
  DL_CHR40x8x1, DL_CHR40x8x1, DL_CHR40x8x1, DL_CHR40x8x1,
  DL_CHR40x8x1, DL_CHR40x8x1, DL_CHR40x8x1, DL_CHR40x8x1,
  DL_CHR40x8x1, DL_CHR40x8x1, DL_CHR40x8x1, DL_CHR40x8x1,
  DL_JVB, dlist_mem
};

void ui_screen_settings_render_units() {
  screen_clear_line(10);
  screen_gotoxy(0, 10);
  screen_puts("UNITS");
  screen_gotoxy(8, 10);
  if (routeOptions.units[0] == 'm') {
    screen_puts(CH_KEY_LABEL_L CH_INV_M CH_INV_I CH_KEY_LABEL_R " KM ");
  } else {
    screen_puts(" MI " CH_KEY_LABEL_L CH_INV_K CH_INV_M CH_KEY_LABEL_R);
  }
}

void ui_screen_settings_render_server() {
  screen_clear_line(8);
  screen_gotoxy(0, 8);
  screen_puts("SERVER");
  screen_gotoxy(8, 8);
  screen_puts(settings.server);
}

void ui_screen_settings() {
  set_dlist_dli_logo_with_text();

  screen_clear();
  screen_puts_center(2, "v0.0.1-alpha1");

  ui_screen_settings_render_units();
  ui_screen_settings_render_server();
}

void ui_screen_settings_menu_default() {
  screen_clear_line(19);
  screen_puts_center(19, CH_KEY_ESC "Cancel " CH_KEY_RETURN "Edit");
}

void ui_screen_settings_menu_editing() {
  screen_clear_line(19);
  screen_puts_center(19, CH_KEY_ESC "Cancel " CH_KEY_RETURN "Save");
}

void ui_screen_settings_focus_none() {
  highlight_row(0xFF);
}

void ui_screen_settings_focus_server() {
  highlight_row(8);
}

void ui_screen_settings_focus_units() {
  highlight_row(10);
}

uint8_t ui_screen_settings_edit_server(char *server_url) {
  screen_gotoxy(8, 8);
  screen_input_default(server_url, 31, server_url);
}

void ui_screen_settings_show_error(char *msg) {
  screen_clear_line(14);
  screen_puts_center(14, msg);
}
