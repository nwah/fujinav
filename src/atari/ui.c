#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <atari.h>
#include <conio.h>
#include <peekpoke.h>
#include <sys/types.h>
#include "api.h"
#include "util.h"
#include "globals.h"
#include "font.h"
#include "ui.h"

#define LINE_LENGTH 40
#define KEY_BACKSPACE 0x08
// #define KEY_ESC 0x1B
// #define KEY_RETURN 0x9B

uint8_t row = 0;
uint8_t col = 0;
uint8_t min_col = 0;
uint8_t max_col = 39;
uint8_t color = CLR_RED;

unsigned char *cursor_ptr = scr_mem;
unsigned char *font_ptr = 0;

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
    DL_BLK8, DL_BLK8, DL_BLK8,
    DL_LMS(DL_CHR40x8x1), scr_mem,
    DL_CHR40x8x1, DL_CHR40x8x1, DL_CHR40x8x1,
    DL_LMS(DL_CHR40x8x1), scr_mem + 4 * 40,
    DL_CHR40x8x1, DL_CHR40x8x1, DL_CHR40x8x1,
    DL_CHR40x8x1, DL_CHR40x8x1, DL_CHR40x8x1, DL_CHR40x8x1,
    DL_CHR40x8x1, DL_CHR40x8x1, DL_CHR40x8x1, DL_CHR40x8x1,
    DL_CHR40x8x1, DL_CHR40x8x1, DL_CHR40x8x1, DL_CHR40x8x1,
    DL_CHR40x8x1, DL_CHR40x8x1, DL_CHR40x8x1, DL_CHR40x8x1,
    DL_JVB, dlist_mem
};

void wait_for_vblank(void)
{
    asm("lda $14");
wvb:
    asm("cmp $14");
    asm("beq %g", wvb);
}

void start_dli(void)
{
  ANTIC.nmien = NMIEN_DLI | NMIEN_VBI;
}

void stop_dli(void)
{
  ANTIC.nmien = NMIEN_VBI;
}

void screen_clear(void)
{
  // row = 0;
  // col = 0;
  // cursor_ptr = scr_mem;
  memset(scr_mem, 0, LINE_LENGTH * 25); // TODO: smarter size calculation
}

void screen_gotoxy(uint8_t x, uint8_t y)
{
  col = x;
  row = y;
  cursor_ptr = scr_mem + LINE_LENGTH * row + col; // TODO: Dynamic max column
}

void screen_set_margins(uint8_t left, uint8_t right)
{
  min_col = left;
  max_col = LINE_LENGTH - 1 - right;
}

void screen_default_margins(void)
{
  screen_set_margins(1, 1);
}

void screen_newline() {
  // TODO: wrap around to top? scroll? ignore?
  cursor_ptr += LINE_LENGTH - col + min_col;
  col = min_col;
  row++;
}

void screen_clear_line(uint8_t y) {
  memset(scr_mem + y * LINE_LENGTH, 0, LINE_LENGTH);
}

// char screen_getkey(void)
// {
//   char c;
//   POKE(764, 255);
//   while ((c = PEEK(764)) == 255)
//     ;

//   if (c > 127)
//     c -= 127;

//   if (c < 65)
//     return c - 64;
//   else if (c < 95)
//     return c;
//   else
//     return c - 32;
// }

void screen_putc(char c)
{
  col++;
  if (col > max_col)
    screen_newline();
  if (c == CH_NEWLINE)
    screen_newline();
  else if (c < 32)
    POKE(cursor_ptr++, c+64);
  else if (c < 96)
    POKE(cursor_ptr++, c-32);
  else
    POKE(cursor_ptr++, c);
}

void screen_puts(char *s) {
  char c;
  while ((c = *s++) != '\0')
    screen_putc(c);
}

void screen_puts_max(char *s, uint8_t max_length)
{
  uint8_t i = 0;
  char c;
  while ((c = *s++) != '\0' && i < max_length) {
    screen_putc(c);
    i++;
  }
}

void screen_puts_center(uint8_t y, char *s) {
  uint8_t len = strlen(s);
  uint8_t x = 0;
  if (len < 39) x = (40 - len) / 2;
  screen_gotoxy(x, y);
  screen_puts(s);
}

void screen_hr(uint8_t length) {
  screen_newline();
  memset(cursor_ptr, SCR_ICON_HLINE, length);
  screen_newline();
}

void screen_pm_draw_icon(uint8_t icon, uint8_t p, uint8_t y) {
  uint8_t *src = font_ptr + icon * 8;
  uint8_t *dst = pmg_mem + 0x200 + p * 128 + y;
  memcpy(dst, src, 8);
  // memcpy(pmg_mem + 40, font_ptr + 40, 24);
}

void screen_pm_clear_icon(uint8_t p, uint8_t y) {
  memset(pmg_mem + 0x200 + p * 128 + y, 0, 8);
}

uint8_t screen_input_default(char *result, uint8_t max_length, char *start_text)
{
  uint8_t err;
  char c;
  char *tmp = malloc(max_length + 2);
  uint8_t i = strlen(start_text);

  strcpy(tmp, start_text);

  while (1) {
    while (!kbhit());
    c = cgetc();
    if (c == CH_ENTER) {
      err = ERR_OK;
      break;
    }
    else if (c == CH_ESC)
    {
      err = ERR_ABORTED;
      break;
    }
    else if (c == CH_DEL || c == CH_CURS_LEFT) {
      if (i > 0) {
        i--;
        cursor_ptr--;
        tmp[i] = '\0';
      }
      POKE(cursor_ptr, 0);
    }
    else {
      screen_putc(c);
      tmp[i++] = c;
      // screen_putc('X');
    }
  }

  if (err == ERR_OK) {
    tmp[i] = '\0';
    strcpy(result, tmp);
  }

  free(tmp);
  return err;
}

uint8_t screen_input(char *result, uint8_t max_length)
{
  return screen_input_default(result, max_length, "");
}

// void dli_foo(void);
void dli_logo_top(void);
void dli_logo_bottom(void);
void dli_location_logo_top(void);
void dli_location_logo_bottom(void);
void dli_location_text_middle(void);
void dli_location_text_background_dark(void);
void dli_location_text_background_light(void);
void dli_location_text_bottom(void);

// void dli_bar(void)
// {
//   asm("pha");
//   asm("lda #$D8");
//   asm("sta $D40A"); // WSYNC
//   asm("sta $D018"); // COLOR2
//   OS.vdslst = &dli_foo;
//   asm("pla");
//   asm("rti");
// }

// void dli_foo(void)
// {
//   asm("pha");
//   asm("lda #$A8");
//   asm("sta $D40A"); // WSYNC
//   asm("sta $D018"); // COLOR2
//   OS.vdslst = &dli_bar;
//   asm("pla");
//   asm("rti");
// }

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
  asm("lda #$08");
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

void set_dlist_default(void)
{
  memcpy((void *)dlist_mem, &default_dlist, sizeof(default_dlist));
}

void set_dlist_title_text(void)
{
  memcpy((void *)dlist_mem, &title_text_dlist, sizeof(title_text_dlist));
}

void set_dlist_logo_with_text(void)
{
  memcpy((void *)dlist_mem, &logo_with_text_dlist, sizeof(logo_with_text_dlist));
}

void set_dlist_location(void)
{
  memcpy((void *)dlist_mem, &destination_dlist, sizeof(destination_dlist));
}

void set_dlist_location_choose_result(void)
{
  memcpy((void *)dlist_mem, &destination_choose_result_dlist, sizeof(destination_choose_result_dlist));
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
  // OS.sdmctl = 62;
  OS.sdmctl = 46;

  // Normal
  OS.gprior = 1;
  // OS.gprior = 1 + 32;

  bzero(pmg_mem, 2048);
}

void ui_init(void)
{
  init_pmg();

  patch_font();
  font_ptr = (void *)(PEEK(756) << 8);

  bzero(scr_mem, 40*25);

  set_dlist_default();
  OS.sdlst = (void *)dlist_mem;

  screen_default_margins();

  OS.color4 = CLR_GRAY_DARK;
  OS.color0 = CLR_GRAY;
  OS.color1 = CLR_WHITE;
  OS.color2 = CLR_GRAY_DARK;
}

void start_dli_logo_with_text(void)
{
  // unsigned char prevVal = 0;
  // save previous val of 0x22F
  // prevVal = *(unsigned char*)0x22F;
  // // shut off ANTIC
  // *(unsigned char*)0X22F = 0;

  // // set the dlist screen
  // memcpy((void *)DISPLAY_LIST, &logo_with_text_dlist, sizeof(logo_with_text_dlist));
  OS.vdslst = &dli_logo_top;

  // // restore ANTIC
  // *(unsigned char*)0x22F = prevVal;

  wait_for_vblank();
  start_dli();
}

void start_dli_location()
{
  // unsigned char prevVal = 0;
  // save previous val of 0x22F
  // prevVal = *(unsigned char*)0x22F;
  // // shut off ANTIC
  // *(unsigned char*)0X22F = 0;

  // // set the dlist screen
  // memcpy((void *)DISPLAY_LIST, &logo_with_text_dlist, sizeof(logo_with_text_dlist));

  OS.vdslst = &dli_location_logo_top;
  // OS.vdslst = &dli_foo;
  //
  // OS.vdslst = &dli_logo_top;

  // // restore ANTIC
  // *(unsigned char*)0x22F = prevVal;

  wait_for_vblank();
  start_dli();
}

void ui_screen_splash() {
  screen_clear();
  set_dlist_logo_with_text();
  start_dli_logo_with_text();
}

void ui_screen_settings() {
  screen_clear();
  set_dlist_logo_with_text();
  start_dli_logo_with_text();

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
  stop_dli();
  start_dli_location();
  set_dlist_location();

  screen_clear();
  screen_puts_center(5, "DESTINATION");
  screen_gotoxy(2, 7);
}

void ui_screen_origin() {
  color = CLR_BLUE;
  stop_dli();
  start_dli_location();
  set_dlist_location();

  screen_clear();
  screen_puts_center(5, "STARTING POINT");
  screen_gotoxy(2, 7);
}

void ui_screen_destination_menu_default()
{
  // screen_clear_line(12);
  screen_puts_center(18, CH_KEY_LABEL_L CH_INV_C CH_KEY_LABEL_R "Config " CH_KEY_RETURN "Search");
}

void ui_screen_origin_menu_default()
{
  // screen_clear_line(12);
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

  stop_dli();
  set_dlist_location_choose_result();
  start_dli_location();

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
    // printf("%d: %s\n", i + 1, *results[i].desc);
      // printf("   %s\n", *results[i].addr);
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

  set_dlist_location();
  return err;
}

void ui_screen_route_options(struct RouteOptions *options) {
  // char input[80];
  // char c;

  screen_clear();
  screen_puts("ROUTE OPTIONS");

  screen_puts("Mode: ");
  screen_puts(options->mode);
  // readline(&input);
  // if (input[0] != '\0') {
  //   strcpy(options->mode, input);
  // }
}

void ui_screen_routing() {
  screen_clear();
  screen_puts("ROUTING...\n");
}

void ui_screen_directions() {
  uint8_t i;
  screen_clear();
  screen_puts("From: ");
  screen_puts(fromLoc.desc);
  screen_puts("To: ");
  screen_puts(toLoc.desc);
  screen_puts(directions.duration);
  screen_puts(" | ");
  screen_puts(directions.distance);

  for (i = 0; i < directions.num_steps; i++) {
    if (i > 0) {
      // chline(40);
    }
    screen_puts(directions.steps[i]->instructions);
  }
}
