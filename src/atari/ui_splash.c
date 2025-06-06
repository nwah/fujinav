#include <atari.h>
#include <peekpoke.h>
#include "globals.h"
#include "typedefs.h"
#include "screen.h"
#include "ui_core.h"

void ui_screen_splash() {
  screen_clear();
  set_dlist_dli_logo_with_text();
}
