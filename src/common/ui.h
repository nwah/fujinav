#ifndef UI_H
#define UI_H

#include <stdint.h>
#include "api.h"
#include "globals.h"

void ui_init(void);

void ui_screen_splash();

void ui_screen_settings();
void ui_screen_settings_menu_default();

void ui_screen_destination();
void ui_screen_destination_menu_default();
void ui_screen_origin();
void ui_screen_origin_menu_default();
uint8_t ui_screen_location_input_query(char *query);
void ui_screen_location_show_searching();
void ui_screen_location_show_no_matches();
uint8_t ui_screen_location_choose_result(uint8_t *choice, struct Location *results[], uint8_t num_results);

void ui_screen_route_options(RouteOptions *options);
void ui_screen_routing();

void ui_screen_directions();
void ui_screen_directions_show_routing();
void ui_screen_directions_show_results();
void ui_screen_directions_menu_default();
void ui_screen_directions_scroll_up();
void ui_screen_directions_scroll_down();

void ui_screen_print();
void ui_screen_print_show_printing();
void ui_screen_print_show_finished();

#endif // UI_H
