#ifndef UI_H
#define UI_H

#include "api.h"
#include "globals.h"

void ui_init(void);
void ui_screen_splash();
void ui_screen_settings();
void ui_screen_destination();
void ui_screen_origin();
void ui_screen_route_options(RouteOptions *options);
void ui_screen_routing();
void ui_screen_directions();
// void ui_screen_print();

#endif // UI_H
