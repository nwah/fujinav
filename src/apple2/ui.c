#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <apple2enh.h>
#include "api.h"
#include "globals.h"
#include "util.h"
#include "ui.h"

void ui_init(void)
{

}

void print_logo() {
  gotoxy(15, 4);
  printf("FUJI-NAV");
}

void ui_screen_splash()
{
  clrscr();
  print_logo();
}


void ui_screen_settings()
{
  clrscr();
  print_logo();

  // gotoxy(1, 8);
  // printf("SETTINGS\n\n");

  ui_screen_settings_render_server();
  ui_screen_settings_render_units();
}

void ui_screen_settings_menu_default()
{
  gotoxy(9, 23);
  printf("ESC:Back  RETURN:Save");
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

}

void ui_screen_settings_focus_none()
{

}

void ui_screen_settings_focus_server()
{
  gotoxy(1, 12);
  cursor(1);
}

void ui_screen_settings_focus_units()
{
  gotoxy(1, 15);
  cursor(1);
  gotoxy(1, 14);
  putchar('*');
}

void ui_screen_settings_render_units()
{
  gotoxy(1, 14);
  printf("UNITS: %s", routeOptions.units);
}

void ui_screen_settings_render_server()
{
  gotoxy(1, 11);
  printf("SERVER: %s", settings.server);
}


void ui_screen_destination()
{
  clrscr();
  print_logo();
  gotoxy(1, 10);
  printf("DESTINATION:");
}

void ui_screen_destination_menu_default()
{
  gotoxy(4, 23);
  printf("ESC:Settings  RETURN:Continue");
}

void ui_screen_origin()
{
  clrscr();
  print_logo();
  gotoxy(1, 10);
  printf("STARTING POINT:\n\n");
}

void ui_screen_origin_menu_default()
{
  gotoxy(1, 23);
  printf("ESC:Back  RETURN:Continue");
}

uint8_t ui_screen_location_input_query(char *query)
{
  gotoxy(1, 12);
  return readline(query);
}

void ui_screen_location_show_searching()
{
  gotoxy(1, 14);
  puts("Searching...    ");
}

void ui_screen_location_show_no_matches()
{
  gotoxy(1, 14);
  puts("No matches found");
}

uint8_t ui_screen_location_choose_result(uint8_t *choice, struct Location *results[], uint8_t num_results)
{
  uint8_t i;
  uint8_t err;
  char c;

  clrscr();
  gotoxy(1, 4);
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
  clrscr();
  gotoxy(0,1);
  printf("FROM: %s\n", fromLoc.desc);
  printf("TO:   %s\n", toLoc.desc);
}

void ui_screen_directions_show_routing()
{
  gotoxy(0,4);
  puts("Routing...");
}

void ui_screen_directions_show_results()
{
  uint8_t i;
  gotoxy(0,4);
  printf("%s | %s | %s\n\n", routeOptions.mode, directions.duration, directions.distance);

  for (i = 0; i < directions.num_steps; i++) {
    printf("] %s\n",directions.steps[i].instructions);
  }
}

void ui_screen_directions_menu_default()
{
  gotoxy(9, 22);
  puts("ESC:Back  C/T/W/B:Mode");
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
