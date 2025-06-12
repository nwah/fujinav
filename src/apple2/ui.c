#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <stdio.h>
#include <peekpoke.h>
#include <apple2enh.h>
#include "api.h"
#include "globals.h"
#include "util.h"
#include "ui.h"

#define TEXT_LEFT 0x20
#define TEXT_WIDTH 0x21
#define TEXT_TOP 0x22
#define TEXT_BOTTOM 0x23

void set_default_margins()
{
  POKE(TEXT_LEFT, 2);
  POKE(TEXT_WIDTH, 40);
  POKE(TEXT_TOP, 0);
  POKE(TEXT_BOTTOM, 23);
}

// Surely this can't be the best way to do this...
void full_screen_clear() {
  uint8_t l = PEEK(TEXT_LEFT);
  uint8_t r = PEEK(TEXT_WIDTH);
  uint8_t t = PEEK(TEXT_TOP);
  uint8_t b = PEEK(TEXT_BOTTOM);

  POKE(TEXT_LEFT, 0);
  POKE(TEXT_WIDTH, 40);
  POKE(TEXT_TOP, 0);
  POKE(TEXT_BOTTOM, 23);
  clrscr();

  POKE(TEXT_LEFT, l);
  POKE(TEXT_WIDTH, r);
  POKE(TEXT_TOP, t);
  POKE(TEXT_BOTTOM, b);
}

void ui_init(void)
{
  clrscr();
  set_default_margins();
  // Enable alternative charset
  // TODO: Limit to machines that support it
  POKE(0xC00F, 0);
}

void print_logo() {
  cputsxy(14, 4, "FUJI-NAV");
}

void ui_screen_splash()
{
  clrscr();
  print_logo();
}


void ui_screen_settings()
{
  full_screen_clear();
  print_logo();

  ui_screen_settings_render_server();
  ui_screen_settings_render_units();
}

void ui_screen_settings_menu_default()
{
  revers(1);
  cclearxy(0, 23, 40);
  cputsxy(9, 23, "ESC:Back  RETURN:Save");
  revers(0);
}

uint8_t ui_screen_settings_edit_server(char *result)
{
  char tmp[128];
  uint8_t err = readline(tmp);
  if (tmp[0] != '\0') {
    strcpy(result, tmp);
  }
  return err;
}

void ui_screen_settings_show_error(char *msg)
{
  cputsxy(0, 16, "Error saving settings");
}

void ui_screen_settings_focus_none()
{
  revers(0);
  cputsxy(0, 10, "SERVER:");
  cputsxy(0, 14, "UNITS:");
}

void ui_screen_settings_focus_server()
{
  revers(1);
  cputsxy(0, 10, "SERVER:");
  revers(0);
  cputsxy(0, 14, "UNITS:");
  gotoxy(1, 12);
  cursor(1);
}

void ui_screen_settings_focus_units()
{
  revers(1);
  cputsxy(0, 14, "UNITS:");
  revers(0);
  cputsxy(0, 10, "SERVER:");
  cursor(0);
}

void ui_screen_settings_render_units()
{
  gotoxy(8, 14);
  printf(routeOptions.units);
}

void ui_screen_settings_render_server()
{
  gotoxy(8, 10);
  printf(settings.server);
}


void ui_screen_destination()
{
  full_screen_clear();
  set_default_margins();
  print_logo();
  cputsxy(0, 10, "DESTINATION:");
}

void ui_screen_destination_menu_default()
{
  POKE(TEXT_LEFT, 0);
  revers(1);
  cclearxy(0, 23, 40);
  cputsxy(5, 23, "ESC:Settings  RETURN:Continue");
  revers(0);
  POKE(TEXT_LEFT, 2);
}

void ui_screen_origin()
{
  full_screen_clear();
  set_default_margins();
  print_logo();
  cputsxy(0, 10, "STARTING POINT:\n\n");
}

void ui_screen_origin_menu_default()
{
  POKE(TEXT_LEFT, 0);
  revers(1);
  cclearxy(0, 23, 40);
  cputsxy(5, 23, "ESC:Back      RETURN:Continue");
  revers(0);
  POKE(TEXT_LEFT, 2);
}

uint8_t ui_screen_location_input_query(char *query)
{
  gotoxy(1, 12);
  return readline(query);
}

void ui_screen_location_show_searching()
{
  gotoxy(0, 14);
  puts("Searching...    ");
}

void ui_screen_location_show_no_matches()
{
  gotoxy(0, 14);
  puts("No matches found");
}

uint8_t ui_screen_location_choose_result(uint8_t *choice, struct Location *results[], uint8_t num_results)
{
  uint8_t i;
  uint8_t err;
  char c;

  clrscr();
  gotoxy(0, 4);
  printf("MULTIPLE MATCHES:");

  gotoxy(0, 6);
  for (i = 0; i < num_results; i++)
  {
    if (i>3) break;
    printf("%i: %s\n%s\n\n", i+1, results[i]->desc, results[i]->addr);
  }

  while (1)
  {
    c = cgetc();
    if (c == KEY_ABORT)
    {
      err = ERR_ABORTED;
      break;
    }
    else if (c >= '1' && c <= '0' + num_results)
    {
      *choice = c - '1';
      err = ERR_OK;
      break;
    }
  }

  return err;
}


void ui_screen_route_options(RouteOptions *options)
{

}

void ui_screen_routing()
{

}


void ui_screen_directions()
{
  POKE(TEXT_TOP, 0);
  POKE(TEXT_LEFT, 0);
  full_screen_clear();

  revers(1);
  cclearxy(0,0,40);
  cclearxy(0,1,40);
  cputsxy(0,0," FROM: ");
  cputs(fromLoc.desc);
  cputsxy(0,1," TO:   ");
  cputs(toLoc.desc);
  revers(0);

  POKE(TEXT_TOP, 4);
  POKE(TEXT_BOTTOM, 21);
}

void ui_screen_directions_show_routing()
{
  POKE(TEXT_TOP, 0);
  revers(1);
  cclearxy(0,2,40);
  cputsxy(1,2,"Routing...");
  revers(0);
  POKE(TEXT_TOP, 4);
}

void ui_screen_directions_show_results()
{
  uint8_t i;

  POKE(TEXT_TOP, 0);
  POKE(TEXT_LEFT, 0);
  revers(1);
  cclearxy(0, 2, 40);
  cputsxy(1, 2, routeOptions.mode);
  cputs(" | ");
  cputs(directions.duration);
  cputs(" | ");
  cputs(directions.distance);
  revers(0);

  POKE(TEXT_TOP, 4);
  POKE(TEXT_LEFT, 1);
  POKE(TEXT_WIDTH, 39);
  gotoxy(0,0);
  for (i = 0; i < directions.num_steps; i++) {
    printf("%s\n\n",directions.steps[i].instructions);
  }
  POKE(TEXT_LEFT, 0);
  POKE(TEXT_WIDTH, 40);
}

void ui_screen_directions_menu_default()
{
  POKE(TEXT_BOTTOM, 23);
  POKE(TEXT_TOP, 0);
  revers(1);
  cclearxy(0, 23, 40);
  cputsxy(2, 23, "ESC:Back  C/T/W/B:Mode  UpDn:Scroll");
  revers(0);
  POKE(TEXT_TOP, 4);
  POKE(TEXT_BOTTOM, 21);
}

void ui_screen_directions_scroll_up()
{

}

void ui_screen_directions_scroll_down()
{

}


void ui_screen_print()
{
  char c;
  clrscr();
  printf("Press any key to print\n\n");

  c = cgetc();
  if (c == CH_ESC) {
    state = VIEW_DIRECTIONS;
    return;
  }
}

void ui_screen_print_show_printing()
{
  printf("Printing...\n");
}

void ui_screen_print_show_finished()
{
  printf("Press any key to continue\n");
}
