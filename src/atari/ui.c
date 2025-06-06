#include <stdint.h>
#include <string.h>
#include <atari.h>
#include <conio.h>
#include <peekpoke.h>
#include <sys/types.h>
#include "api.h"
#include "globals.h"
#include "font.h"
#include "ui.h"
#include "screen.h"

void default_dlist = {
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

void logo_with_text_dlist = {
    DL_BLK8, DL_BLK8, DL_BLK8,
    DL_LMS(DL_CHR40x8x1), scr_mem, // 1
    DL_DLI(DL_LMS(DL_MAP160x2x4)), &logo_data,
    DL_MAP160x2x4, DL_MAP160x2x4, DL_MAP160x2x4, // 2
    DL_MAP160x2x4, DL_MAP160x2x4, DL_MAP160x2x4, DL_MAP160x2x4, // 3
    DL_DLI(DL_MAP160x2x4),
    DL_MAP160x2x4, DL_MAP160x2x4, DL_MAP160x2x4, // 4
    DL_MAP160x2x4, DL_MAP160x2x4, DL_MAP160x2x4,
    DL_DLI(DL_MAP160x2x4), // 5
    DL_LMS(DL_CHR40x8x1), scr_mem + LINE_LENGTH, // 6
    DL_CHR40x8x1, DL_CHR40x8x1, DL_CHR40x8x1, DL_CHR40x8x1, // 10
    DL_CHR40x8x1, DL_CHR40x8x1, DL_CHR40x8x1, DL_CHR40x8x1, // 14
    DL_CHR40x8x1, DL_CHR40x8x1, DL_CHR40x8x1, DL_CHR40x8x1, // 18
    DL_CHR40x8x1, DL_CHR40x8x1, DL_CHR40x8x1, DL_CHR40x8x1, // 22
    DL_CHR40x8x1, DL_CHR40x8x1, // 24
    DL_JVB, dlist_mem
};

void destination_dlist = {
    DL_BLK8, DL_BLK8, DL_BLK8,
    DL_LMS(DL_CHR40x8x1), scr_mem, // 1
    DL_DLI(DL_LMS(DL_MAP160x2x4)), &logo_data,
    DL_MAP160x2x4, DL_MAP160x2x4, DL_MAP160x2x4,                // 2
    DL_MAP160x2x4, DL_MAP160x2x4, DL_MAP160x2x4, DL_MAP160x2x4, // 3
    DL_DLI(DL_MAP160x2x4),
    DL_MAP160x2x4, DL_MAP160x2x4, DL_MAP160x2x4, // 4
    DL_MAP160x2x4, DL_MAP160x2x4, DL_MAP160x2x4,
    DL_DLI(DL_MAP160x2x4),                       // 5
    DL_LMS(DL_CHR40x8x1), scr_mem + LINE_LENGTH, // 6
    DL_CHR40x8x1,
    DL_DLI(DL_CHR40x8x1), DL_CHR40x8x1,
    DL_DLI(DL_CHR40x8x1),
    DL_CHR40x8x1, DL_CHR40x8x1, // 14
    DL_DLI(DL_CHR40x8x1), DL_CHR40x8x1, DL_CHR40x8x1,
    DL_CHR40x8x1, DL_CHR40x8x1, DL_CHR40x8x1,               // 18
    DL_CHR40x8x1, DL_CHR40x8x1, DL_CHR40x8x1, DL_CHR40x8x1, // 22
    DL_CHR40x8x1, DL_CHR40x8x1,                             // 24
    DL_JVB, dlist_mem};

void destination_choose_result_dlist = {
    DL_BLK8, DL_BLK8, DL_BLK8,
    DL_LMS(DL_CHR40x8x1), scr_mem, // 1
    DL_DLI(DL_LMS(DL_MAP160x2x4)), &logo_data,
    DL_MAP160x2x4, DL_MAP160x2x4, DL_MAP160x2x4,                // 2
    DL_MAP160x2x4, DL_MAP160x2x4, DL_MAP160x2x4, DL_MAP160x2x4, // 3
    DL_DLI(DL_MAP160x2x4),
    DL_MAP160x2x4, DL_MAP160x2x4, DL_MAP160x2x4, // 4
    DL_MAP160x2x4, DL_MAP160x2x4, DL_MAP160x2x4,
    DL_DLI(DL_MAP160x2x4), DL_CHR40x8x1,                       // 5
    DL_DLI(DL_LMS(DL_CHR40x8x1)), scr_mem + LINE_LENGTH, // 6
    DL_DLI(DL_CHR40x8x1),
    DL_CHR40x8x1, DL_CHR40x8x1, // 10
    DL_CHR40x8x1, DL_CHR40x8x1, DL_CHR40x8x1, DL_CHR40x8x1, // 14
    DL_CHR40x8x1, DL_CHR40x8x1, // 16
    DL_CHR40x8x1, DL_CHR40x8x1,
    DL_CHR40x8x1,
    DL_DLI(DL_CHR40x8x1),  DL_CHR40x8x1, // 21
    DL_CHR40x8x1, DL_CHR40x8x1, DL_CHR40x8x1, // 24
    DL_JVB, dlist_mem};

void title_text_dlist = {
    DL_BLK8, DL_BLK8,
    DL_DLI(DL_BLK8),
    DL_DLI(DL_LMS(DL_CHR20x16x2)), scr_mem,
    DL_LMS(DL_CHR40x8x1), scr_mem + 40,
    DL_CHR40x8x1, DL_CHR40x8x1,
    DL_CHR40x8x1, DL_CHR40x8x1, DL_CHR40x8x1,
    DL_CHR40x8x1, DL_CHR40x8x1, DL_CHR40x8x1, DL_CHR40x8x1,
    DL_CHR40x8x1, DL_CHR40x8x1, DL_CHR40x8x1, DL_CHR40x8x1,
    DL_CHR40x8x1, DL_CHR40x8x1, DL_CHR40x8x1, DL_CHR40x8x1,
    DL_CHR40x8x1, DL_CHR40x8x1, DL_CHR40x8x1, DL_CHR40x8x1,
    DL_JVB, dlist_mem};

void directions_dlist = {
    DL_BLK8, DL_BLK8, DL_DLI(DL_BLK8),
    DL_DLI(DL_LMS(DL_CHR40x8x1)), scr_mem,           // 0
    DL_DLI(DL_CHR40x8x1),                            // 40
    DL_DLI(DL_CHR40x8x1), DL_CHR40x8x1,              // 80, 120
    DL_LMS(DL_CHR40x8x1), scr_mem + 6 * LINE_LENGTH, // 240
    DL_LMS(DL_CHR40x8x1), scr_mem + 7 * LINE_LENGTH,
    DL_LMS(DL_CHR40x8x1), scr_mem + 8 * LINE_LENGTH,
    DL_LMS(DL_CHR40x8x1), scr_mem + 9 * LINE_LENGTH,
    DL_LMS(DL_CHR40x8x1), scr_mem + 10 * LINE_LENGTH,
    DL_LMS(DL_CHR40x8x1), scr_mem + 11 * LINE_LENGTH,
    DL_LMS(DL_CHR40x8x1), scr_mem + 12 * LINE_LENGTH,
    DL_LMS(DL_CHR40x8x1), scr_mem + 13 * LINE_LENGTH,
    DL_LMS(DL_CHR40x8x1), scr_mem + 14 * LINE_LENGTH,
    DL_LMS(DL_CHR40x8x1), scr_mem + 15 * LINE_LENGTH,
    DL_LMS(DL_CHR40x8x1), scr_mem + 16 * LINE_LENGTH,
    DL_LMS(DL_CHR40x8x1), scr_mem + 17 * LINE_LENGTH,
    DL_LMS(DL_CHR40x8x1), scr_mem + 18 * LINE_LENGTH,
    DL_LMS(DL_CHR40x8x1), scr_mem + 19 * LINE_LENGTH,
    DL_LMS(DL_CHR40x8x1), scr_mem + 20 * LINE_LENGTH,
    DL_LMS(DL_CHR40x8x1), scr_mem + 21 * LINE_LENGTH,
    DL_LMS(DL_CHR40x8x1), scr_mem + 22 * LINE_LENGTH,
    DL_DLI(DL_LMS(DL_CHR40x8x1)), scr_mem + 23 * LINE_LENGTH,
    DL_LMS(DL_CHR40x8x1), scr_mem + 4 * LINE_LENGTH, // 160
    DL_CHR40x8x1,                                    // 200
    DL_JVB, dlist_mem};

void dli_text(void);
void dli_logo_top(void);
void dli_logo_bottom(void);

void dli_location_logo_top(void);
void dli_location_logo_bottom(void);
void dli_location_text_middle(void);
void dli_location_text_background_dark(void);
void dli_location_text_background_light(void);
void dli_location_text_bottom(void);

void dli_directions_header_1(void);
void dli_directions_header_2(void);
void dli_directions_header_3(void);
void dli_directions_body(void);
void dli_directions_footer(void);

void dli_text(void)
{
 	asm("pha");
  asm("lda #$02");  // dark grey
  asm("sta $D40A"); // WSYNC
  asm("sta $D018"); // COLOR2
  OS.vdslst = &dli_logo_top;
  asm("pla");
  asm("rti");
}

void dli_logo_top(void)
{
 	asm("pha");
  asm("lda #$96");  // blue
  asm("sta $D40A"); // WSYNC
  asm("sta $D018"); // COLOR2
  // asm("lda #$66");
  // asm("sta $D017"); //COLOR2
  OS.vdslst = &dli_logo_bottom;
  asm("pla");
  asm("rti");
}

void dli_logo_bottom(void)
{
 	asm("pha");
  asm("lda #$36");  // red
  asm("sta $D40A"); // WSYNC
  asm("sta $D018"); //COLOR2
  OS.vdslst = &dli_text;
  asm("pla");
  asm("rti");
}

void dli_location_text_bottom(void)
{
  asm("pha");
  asm("txa");
  asm("pha");
  asm("lda #$02");  // dark grey
  asm("sta $D40A"); // WSYNC
  asm("sta $D018"); // COLOR2
  OS.vdslst = &dli_location_logo_top;
  asm("pla");
  asm("tax");
  asm("pla");
  asm("rti");
}

void dli_location_logo_top(void)
{
  asm("pha");
  asm("txa");
  asm("pha");
  asm("lda #$96");  // blue
  asm("sta $D40A"); // WSYNC
  asm("sta $D018"); // COLOR2
  // asm("lda #$66");
  // asm("sta $D017"); //COLOR2
  OS.vdslst = &dli_location_logo_bottom;
  asm("pla");
  asm("tax");
  asm("pla");
  asm("rti");
}

void dli_location_logo_bottom(void)
{
  asm("pha");
  asm("txa");
  asm("pha");
  asm("lda #$36");  // red
  asm("sta $D40A"); // WSYNC
  asm("sta $D018"); // COLOR2
  OS.vdslst = &dli_location_text_middle;
  asm("pla");
  asm("tax");
  asm("pla");
  asm("rti");
}

void dli_location_text_middle(void)
{
  asm("pha");
  asm("txa");
  asm("pha");
  asm("lda #$02");  // dark grey
  asm("sta $D40A"); // WSYNC
  asm("sta $D018"); // COLOR2
  OS.vdslst = &dli_location_text_background_dark;
  asm("pla");
  asm("tax");
  asm("pla");
  asm("rti");
}

void dli_location_text_background_dark(void)
{
  asm("pha");
  asm("txa");
  asm("pha");
  asm("lda %v", color);  // red
  asm("sta $D40A"); // WSYNC
  asm("sta $D018"); // COLOR2
  asm("lda #$0C");
  asm("sta $D017"); // COLOR1
  OS.vdslst = &dli_location_text_background_light;
  asm("pla");
  asm("tax");
  asm("pla");
  asm("rti");
}

void dli_location_text_background_light(void)
{
  asm("pha");
  asm("txa");
  asm("pha");
  asm("lda #$0E");
  asm("sta $D40A"); // WSYNC
  asm("sta $D017"); // COLOR1
  OS.vdslst = &dli_location_text_bottom;
  asm("pla");
  asm("tax");
  asm("pla");
  asm("rti");
}

void dli_directions_header_1(void)
{
  asm("pha");
  asm("txa");
  asm("pha");
  asm("lda #$94");  // blue
  asm("sta $D40A"); // WSYNC
  asm("sta $D018"); // COLOR2
  OS.vdslst = &dli_directions_header_2;
  asm("pla");
  asm("tax");
  asm("pla");
  asm("rti");
}

void dli_directions_header_2(void)
{
  asm("pha");
  asm("txa");
  asm("pha");
  asm("lda #$34");  // red
  asm("sta $D40A"); // WSYNC
  asm("sta $D018"); // COLOR2
  OS.vdslst = &dli_directions_header_3;
  asm("pla");
  asm("tax");
  asm("pla");
  asm("rti");
}

void dli_directions_header_3(void)
{
  asm("pha");
  asm("txa");
  asm("pha");
  asm("lda #$02");  // dark gray
  asm("sta $D40A"); // WSYNC
  asm("sta $D018"); // COLOR2
  OS.vdslst = &dli_directions_body;
  asm("pla");
  asm("tax");
  asm("pla");
  asm("rti");
}

void dli_directions_body(void)
{
  asm("pha");
  asm("txa");
  asm("pha");
  // asm("lda #$00");  // black
  asm("lda #$02");  // dark gray
  asm("sta $D40A"); // WSYNC
  asm("sta $D018"); // COLOR2
  OS.vdslst = &dli_directions_footer;
  asm("pla");
  asm("tax");
  asm("pla");
  asm("rti");
}

void dli_directions_footer(void)
{
  asm("pha");
  asm("txa");
  asm("pha");
  asm("lda #$02");  // dark gray
  asm("sta $D40A"); // WSYNC
  asm("sta $D018"); // COLOR2
  OS.vdslst = &dli_directions_header_1;
  asm("pla");
  asm("tax");
  asm("pla");
  asm("rti");
}

void set_dlist(void *dlist_ptr, uint8_t size)
{
  memcpy((void *)dlist_mem, dlist_ptr, size);
}

void start_dli(void *dli)
{
  // unsigned char prevVal = 0;
  // save previous val of 0x22F
  // prevVal = *(unsigned char*)0x22F;
  // // shut off ANTIC
  // *(unsigned char*)0X22F = 0;

  OS.vdslst = dli;
  // OS.vdslst = &dli_foo;
  //
  // OS.vdslst = &dli_logo_top;

  // // restore ANTIC
  // *(unsigned char*)0x22F = prevVal;

  wait_for_vblank();
  dli_start();
}

void init_pmg(void) {
  ANTIC.pmbase = (uint16_t)pmg_mem >> 8;

  OS.pcolr0 = 0x96; // blue
  OS.pcolr1 = 0x36; // red

  GTIA_WRITE.hposp0 = 60;
  GTIA_WRITE.hposp1 = 120;
  // enable players
  GTIA_WRITE.gractl = 3;
  // enable single line PMG
  OS.sdmctl = 46;
  // Normal
  OS.gprior = 1;

  bzero(pmg_mem, 2048);
}

void ui_init(void)
{
  init_pmg();

  patch_font();
  font_ptr = (void *)(PEEK(756) << 8);

  bzero(scr_mem, 40*25);

  set_dlist(&default_dlist, sizeof(default_dlist));
  OS.sdlst = (void *)dlist_mem;

  screen_default_margins();

  OS.color4 = CLR_GRAY_DARK;
  OS.color0 = CLR_GRAY;
  OS.color1 = CLR_WHITE;
  OS.color2 = CLR_GRAY_DARK;
}

void ui_screen_splash() {
  screen_clear();
  set_dlist(&logo_with_text_dlist, sizeof(logo_with_text_dlist));
  start_dli(&dli_logo_top);
}

void ui_screen_settings() {
  screen_clear();
  set_dlist(&logo_with_text_dlist, sizeof(logo_with_text_dlist));
  start_dli(&dli_logo_top);

  screen_puts_center(6, "SERVER");
  screen_puts_center(8, settings.server);
}

void ui_screen_settings_menu_default() {
  // screen_clear_line(19);
  screen_puts_center(19, CH_KEY_LABEL_L CH_INV_C CH_KEY_LABEL_R "Config " CH_KEY_RETURN "Continue");
}

void ui_screen_destination()
{
  color = CLR_RED;
  dli_stop();
  start_dli(&dli_location_logo_top);
  set_dlist(&destination_dlist, sizeof(destination_dlist));

  screen_clear();
  screen_puts_center(5, "DESTINATION");
  screen_gotoxy(2, 7);
}

void ui_screen_origin() {
  color = CLR_BLUE;
  dli_stop();
  start_dli(&dli_location_logo_top);
  set_dlist(&destination_dlist, sizeof(destination_dlist));

  screen_clear();
  screen_puts_center(5, "STARTING POINT");
  screen_gotoxy(2, 7);
}

void ui_screen_destination_menu_default()
{
  screen_clear_line(12);
  screen_puts_center(18, CH_KEY_LABEL_L CH_INV_C CH_KEY_LABEL_R "Config " CH_KEY_RETURN "Search");
}

void ui_screen_origin_menu_default()
{
  screen_clear_line(12);
  screen_puts_center(18, CH_KEY_ESC "Back " CH_KEY_RETURN "Search");
}

uint8_t ui_screen_location_input_query(char *query) {
  uint8_t err;
  screen_gotoxy(2, 7);
  err = screen_input(query, 36);
  return ERR_OK;
}

void ui_screen_location_show_searching() {
  screen_clear_line(7);
  screen_puts_center(7, "Searching...");
}

void ui_screen_location_show_no_matches() {
  screen_clear_line(7);
  screen_puts_center(7, "No matches found.");
}

uint8_t ui_screen_location_choose_result(uint8_t *choice, struct Location *results[], uint8_t num_results) {
  uint8_t i;
  uint8_t err;
  char c;

  dli_stop();
  set_dlist(&destination_choose_result_dlist, sizeof(destination_choose_result_dlist));
  start_dli(&dli_location_logo_top);

  screen_clear();
  screen_set_margins(3, 0);

  for (i = 0; i < num_results; i++)
  {
    if (i>3) break;
    screen_gotoxy(1, 3 + i*3);
    screen_putc(128 + 17 + i);
    screen_putc(' ');
    screen_puts_max(results[i]->desc, 36);
    screen_newline();
    screen_puts_max(results[i]->addr, 36);
  }
  screen_default_margins();

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

  set_dlist(&destination_dlist, sizeof(destination_dlist));
  return err;
}

void ui_screen_route_options(struct RouteOptions *options) {
  screen_clear();
  screen_puts("ROUTE OPTIONS");

  screen_puts("Mode: ");
  screen_puts(options->mode);
}

void ui_screen_routing() {
  screen_clear();
  screen_puts("ROUTING...\n");
}

void ui_screen_directions_show_header() {
  screen_gotoxy(1, 0);
  screen_set_margins(1, 1);

  screen_putc(CH_ICON_PIN);
  screen_putc(' ');
  screen_puts(fromLoc.desc);
  screen_newline();
  screen_putc(CH_ICON_PIN);
  screen_putc(' ');
  screen_puts(toLoc.desc);
}

void ui_screen_directions() {
  dli_stop();
  set_dlist(&directions_dlist, sizeof(directions_dlist));
  start_dli(&dli_directions_header_1);

  screen_clear();
  ui_screen_directions_show_header();
}

void ui_screen_directions_show_routing()
{
  screen_clear_line(2);
  screen_gotoxy(1, 2);
  screen_puts("Routing...");
}

void ui_screen_directions_show_results()
{
  uint8_t i;
  char default_icon;

  screen_clear();
  ui_screen_directions_show_header();

  screen_gotoxy(1, 2);
  // Set default icon based on mode
  if (strcmp(routeOptions.mode, "biking") == 0) {
    default_icon = CH_ICON_BIKE;
  } else if (strcmp(routeOptions.mode, "driving") == 0) {
    default_icon = CH_ICON_CAR;
  } else if (strcmp(routeOptions.mode, "walking") == 0) {
    default_icon = CH_ICON_WALK;
  } else {
    default_icon = CH_ICON_RAIL;
  }

  screen_putc(default_icon);
  screen_putc(' ');
  screen_puts(directions.duration);
  screen_puts(" | ");
  screen_puts(directions.distance);

  screen_set_margins(0, 0);
  screen_newline();
  screen_hr(40);
  screen_newline();
  screen_hr(40);
  screen_newline();
  screen_newline();
  screen_set_margins(3, 0);
  screen_newline();

  for (i = 0; i < directions.num_steps; i++) {
    if (i > 0) {
      screen_newline();
    }

    screen_back(2);

    // Convert icon character to appropriate screen code
    switch(directions.steps[i].icon) {
      case 'R': // Right/sharp right
        screen_putc(CH_ICON_RIGHT_TURN);
        break;
      case 'r': // Slight right
        screen_putc(CH_ICON_SLIGHT_RIGHT);
        break;
      case 'L': // Left/sharp left
        screen_putc(CH_ICON_LEFT_TURN);
        break;
      case 'l': // Slight left
        screen_putc(CH_ICON_SLIGHT_LEFT);
        break;
      case 'M': // Merge
        screen_putc(CH_ICON_MERGE);
        break;
      case 'E': // Exit
        screen_putc(CH_ICON_EXIT);
        break;
      case 'S': // Straight
        screen_putc(default_icon); // Use mode-specific icon for continuing straight
        break;
      case 'W': // Walk
        screen_putc(CH_ICON_WALK);
        break;
      case 'T': // Rail/train/subway/trolley/streetcar
        screen_putc(CH_ICON_RAIL);
        break;
      case 'B': // Bus
        screen_putc(CH_ICON_BUS);
        break;
      case 'b': // building
        screen_putc(CH_ICON_BUILDING);
        break;
      case 'F': // Ferry/boat
        screen_putc(CH_ICON_BOAT);
        break;
      case 'C': // Cycle
        screen_putc(CH_ICON_BIKE);
        break;
      case 'D': // Drive
        screen_putc(CH_ICON_CAR);
        break;
      default:
        screen_putc(default_icon);
        break;
    }
    screen_putc(' ');
    screen_puts(directions.steps[i].instructions);
  }

  POKEW(&directions_dlist + 10, scr_mem);

  total_rows = row - 6;
  scrolled_rows = 0;
}

void ui_screen_directions_update_scroll()
{
  uint8_t i = 0;
  uint16_t screen_addr = &scr_mem[0] + (6 + scrolled_rows) * LINE_LENGTH;

  uint16_t dlist_addr = dlist_mem + 10;

  for (i = 0; i < 18; i++) {
    POKEW(dlist_addr, screen_addr);
    dlist_addr += 3;
    screen_addr += LINE_LENGTH;
  }

  // POKEW(dlist_addr, screen_addr);
  // POKE(&directions_dlist + 10, addr);
  // POKE(&directions_dlist + 11, addr >> 8);
  // screen_gotoxy(0, 0);
  // screen_putc('0' + scrolled_rows);
}

void ui_screen_directions_scroll_up()
{
  if (scrolled_rows > 0)
  {
    scrolled_rows--;
    ui_screen_directions_update_scroll();
  }
}

void ui_screen_directions_scroll_down()
{
  if (scrolled_rows < total_rows - visible_rows)
  // if (scrolled_rows < 10)
  {
    scrolled_rows++;
    ui_screen_directions_update_scroll();
  }
}

void ui_screen_directions_menu_default()
{
  char label[] = {
    CH_KEY_ESC "Back "
    CH_KEY_LABEL_L
      CH_INV_C CH_INV_T CH_INV_B CH_INV_W
    CH_KEY_LABEL_R "C R " CH_ICON_BIKE_S " " CH_ICON_WALK_S " "
    CH_KEY_LABEL_L CH_INV_UP CH_INV_DOWN CH_KEY_LABEL_R "Scroll"
  };
  // cc65 ASCII conversion is treating 0x0A as a \n and converting it to a newline
  label[16] = CH_ICON_CAR;
  label[18] = CH_ICON_RAIL;

  screen_clear_line(5);
  // screen_puts_center(5, CH_KEY_ESC "Back " CH_KEY_LABEL_L CH_INV_C CH_INV_T CH_INV_W CH_INV_B CH_KEY_LABEL_R "Mode " CH_KEY_LABEL_L CH_INV_UP CH_INV_DOWN CH_KEY_LABEL_R "Scroll");
  // screen_puts_center(5, CH_KEY_ESC "Back "
  //   CH_KEY_LABEL_L CH_INV_C CH_KEY_LABEL_R CH_ICON_CAR_S
  //   CH_KEY_LABEL_L CH_INV_T CH_KEY_LABEL_R CH_ICON_RAIL_S
  //   CH_KEY_LABEL_L CH_INV_W CH_KEY_LABEL_R CH_ICON_WALK_S
  //   CH_KEY_LABEL_L CH_INV_B CH_KEY_LABEL_R CH_ICON_BIKE_S
  //   CH_KEY_LABEL_L CH_INV_UP CH_INV_DOWN CH_KEY_LABEL_R "Scroll");
  //
  screen_puts_center(5, label);
  // screen_puts("|ESC|Back |DBWT|Mode |^v|Scroll |P|Print");
}

void ui_screen_print() {
  dli_stop();
  set_dlist(&default_dlist, sizeof(default_dlist));
  screen_clear();

  screen_gotoxy(0, 0);
  // screen_puts("PRINT DIRECTIONS");

  screen_clear_line(8);
  screen_puts_center(8, "Press any key to print");
}

void ui_screen_print_show_printing()
{
  screen_clear_line(8);
  screen_puts_center(8, "Printing...");
}

void ui_screen_print_show_finished()
{
  screen_clear_line(8);
  screen_puts_center(8, "Finished...");
}
