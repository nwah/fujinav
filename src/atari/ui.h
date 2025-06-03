#ifndef UI_H
#define UI_H

#include <stdint.h>
#include "api.h"
#include "globals.h"

#define INV(a) ((a)|128)

#define CLR_GRAY_DARK 0x02
#define CLR_GRAY 0x04
#define CLR_WHITE 0x0E
#define CLR_RED 0x34
#define CLR_BLUE 0x96

#define CH_KEY_LABEL_L "\x02" // Left arrow on the keyboard
#define CH_KEY_LABEL_R "\x16" // Right arrow on the keyboard
#define CH_NEWLINE 0x9B

#define CH_INV_A "\xA1"
#define CH_INV_B "\xA2"
#define CH_INV_C "\xA3"
#define CH_INV_D "\xA4"
#define CH_INV_E "\xA5"
#define CH_INV_F "\xA6"
#define CH_INV_G "\xA7"
#define CH_INV_H "\xA8"
#define CH_INV_I "\xA9"
#define CH_INV_J "\xAA"
#define CH_INV_K "\xAB"
#define CH_INV_L "\xAC"
#define CH_INV_M "\xAD"
#define CH_INV_N "\xAE"
#define CH_INV_O "\xAF"
#define CH_INV_P "\xB0"
#define CH_INV_Q "\xB1"
#define CH_INV_R "\xB2"
#define CH_INV_S "\xB3"
#define CH_INV_T "\xB4"
#define CH_INV_U "\xB5"
#define CH_INV_V "\xB6"
#define CH_INV_W "\xB7"
#define CH_INV_X "\xB8"
#define CH_INV_Y "\xB9"
#define CH_INV_Z "\xBA"

#define CH_INV_1 "\x91"
#define CH_INV_2 "\x92"
#define CH_INV_3 "\x93"
#define CH_INV_4 "\x94"
#define CH_INV_5 "\x95"
#define CH_INV_6 "\x96"
#define CH_INV_7 "\x97"
#define CH_INV_8 "\x98"
#define CH_INV_9 "\x99"
#define CH_INV_UP "\xDC"
#define CH_INV_DOWN "\xDD"
#define CH_INV_LEFT "\xDE"
#define CH_INV_RIGHT "\xDF"

#define CH_KEY_1TO8 CH_KEY_LABEL_L CH_INV_1 CH_INV_MINUS CH_INV_8 CH_KEY_LABEL_R
#define CH_KEY_ESC CH_KEY_LABEL_L CH_INV_E CH_INV_S CH_INV_C CH_KEY_LABEL_R
#define CH_KEY_TAB CH_KEY_LABEL_L CH_INV_T CH_INV_A CH_INV_B CH_KEY_LABEL_R
#define CH_KEY_DELETE CH_KEY_LABEL_L CH_INV_D CH_INV_E CH_INV_L CH_INV_E CH_INV_T CH_INV_E CH_KEY_LABEL_R
#define CH_KEY_LEFT CH_KEY_LABEL_L CH_INV_LEFT CH_KEY_LABEL_R
#define CH_KEY_RIGHT CH_KEY_LABEL_L CH_INV_RIGHT CH_KEY_LABEL_R
#define CH_KEY_RETURN CH_KEY_LABEL_L CH_INV_R CH_INV_E CH_INV_T CH_INV_U CH_INV_R CH_INV_N CH_KEY_LABEL_R
#define CH_KEY_OPTION CH_KEY_LABEL_L CH_INV_O CH_INV_P CH_INV_T CH_INV_I CH_INV_O CH_INV_N CH_KEY_LABEL_R
#define CH_KEY_C CH_KEY_LABEL_L CH_INV_C CH_KEY_LABEL_R
#define CH_KEY_N CH_KEY_LABEL_L CH_INV_N CH_KEY_LABEL_R
#define CH_KEY_F CH_KEY_LABEL_L CH_INV_F CH_KEY_LABEL_R
#define CH_KEY_LT CH_KEY_LABEL_L CH_INV_LT CH_KEY_LABEL_R
#define CH_KEY_GT CH_KEY_LABEL_L CH_INV_GT CH_KEY_LABEL_R
#define CH_KEY_ESC CH_KEY_LABEL_L CH_INV_E CH_INV_S CH_INV_C CH_KEY_LABEL_R

extern unsigned char dlist_mem[];
extern unsigned char scr_mem[];
extern unsigned char pmg_mem[];
extern unsigned char logo_data[640];

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
// void ui_screen_print();

#endif // UI_H
