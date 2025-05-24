#include <stdio.h>
#include <string.h>
#include <atari.h>
#include <conio.h>
#include "api.h"
#include "util.h"
#include "globals.h"

void ui_screen_splash() {
  clrscr();
  printf("FujiNav");
}

void ui_screen_settings() {
  clrscr();
  printf("Settings");
}

void ui_screen_destination() {
  clrscr();
  printf("DESTINATION\n\n");
}

void ui_screen_origin() {
  clrscr();
  printf("STARTING POINT\n\n");
}

void ui_screen_route_options(struct RouteOptions *options) {
  // char input[80];
  char c;

  clrscr();
  printf("ROUTE OPTIONS\n");

  printf("\nMode (%s): ", options->mode);
  // readline(&input);
  // if (input[0] != '\0') {
  //   strcpy(options->mode, input);
  // }
}

void ui_screen_routing() {
  clrscr();
  printf("ROUTING...\n");
}

void ui_screen_directions() {
  uint8_t i;
  clrscr();
  printf("From: %s\n", fromLoc.desc);
  printf("To: %s\n", toLoc.desc);
  printf("%s | %s\n\n", directions.duration, directions.distance);

  for (i = 0; i < directions.num_steps; i++) {
    if (i > 0) {
      chline(40);
    }
    printf("%s\n", directions.steps[i]->instructions);
  }
}
