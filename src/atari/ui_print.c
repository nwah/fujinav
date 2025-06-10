#include <atari.h>
#include <peekpoke.h>
#include "globals.h"
#include "typedefs.h"
#include "screen.h"
#include "ui_core.h"

void ui_screen_print() {
  dli_stop();
  set_default_dlist();
  screen_clear();

  screen_gotoxy(0, 0);
  // screen_puts("PRINT DIRECTIONS");

  screen_clear_line(8);
  screen_puts_center(8, "Press any key to print");

  screen_puts_center(16, CH_KEY_ESC "Cancel");
}

void ui_screen_print_show_printing()
{
  screen_clear_line(8);
  screen_clear_line(16);
  screen_puts_center(8, "Printing...");
}

void ui_screen_print_show_finished()
{
  screen_clear_line(8);
  screen_puts_center(8, "Finished...");

  screen_puts_center(16, "Press any key to continue");
}
