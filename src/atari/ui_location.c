#include <conio.h>
#include <atari.h>
#include "globals.h"
#include "typedefs.h"
#include "screen.h"
#include "ui_core.h"

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

void dli_location_logo_top(void);
void dli_location_logo_bottom(void);
void dli_location_text_middle(void);
void dli_location_text_background_dark(void);
void dli_location_text_background_light(void);
void dli_location_text_bottom(void);

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
