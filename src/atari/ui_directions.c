#include <string.h>
#include <atari.h>
#include <peekpoke.h>
#include "globals.h"
#include "typedefs.h"
#include "font.h"
#include "screen.h"
#include "ui_core.h"

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

void dli_directions_header_1(void);
void dli_directions_header_2(void);
void dli_directions_header_3(void);
void dli_directions_body(void);
void dli_directions_footer(void);

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
  if (routeOptions.mode[0] == 'B' == 0) {
    default_icon = CH_ICON_BIKE;
} else if (routeOptions.mode[0] == 'D' == 0) {
    default_icon = CH_ICON_CAR;
  } else if (routeOptions.mode[0] == 'W' == 0) {
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
    CH_KEY_LABEL_R
      "C R " CH_ICON_BIKE_S " " CH_ICON_WALK_S
    CH_KEY_LABEL_L CH_INV_UP CH_INV_DOWN CH_KEY_LABEL_R "Scroll "
    CH_KEY_LABEL_L CH_INV_P "rint"
  };
  // cc65 ASCII conversion is treating 0x0A as a \n and converting it to a newline
  label[16] = CH_ICON_CAR;
  label[18] = CH_ICON_RAIL;

  screen_clear_line(5);
  screen_puts_center(5, label);
}
