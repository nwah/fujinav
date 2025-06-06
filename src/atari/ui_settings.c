#include <atari.h>
#include <peekpoke.h>
#include "globals.h"
#include "typedefs.h"
#include "screen.h"
#include "ui_core.h"

void ui_screen_settings() {
  screen_clear();
  set_dlist_dli_logo_with_text();

  screen_puts_center(6, "SERVER");
  screen_puts_center(8, settings.server);
}

void ui_screen_settings_menu_default() {
  // screen_clear_line(19);
  screen_puts_center(19, CH_KEY_LABEL_L CH_INV_C CH_KEY_LABEL_R "Config " CH_KEY_RETURN "Continue");
}
