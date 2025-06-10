#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <atari.h>
#include <peekpoke.h>
#include <conio.h>
#include "typedefs.h"
#include "screen.h"
#include "font.h"

uint8_t row = 0;
uint8_t col = 0;
uint8_t min_col = 0;
uint8_t max_col = 39;
uint8_t color = CLR_RED;
uint8_t visible_rows = 14;
uint8_t total_rows = 0;
uint8_t scrolled_rows = 0;

unsigned char *cursor_ptr = scr_mem;
unsigned char *font_ptr = 0;

void wait_for_vblank(void)
{
    asm("lda $14");
wvb:
    asm("cmp $14");
    asm("beq %g", wvb);
}

void dli_start(void)
{
  ANTIC.nmien = NMIEN_DLI | NMIEN_VBI;
}

void dli_stop(void)
{
  ANTIC.nmien = NMIEN_VBI;
}

void screen_clear(void)
{
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
  // TODO: optimize by just moving forward based on current position
  screen_gotoxy(min_col, row + 1);
}

void screen_clear_line(uint8_t y) {
  memset(scr_mem + y * LINE_LENGTH, 0, LINE_LENGTH);
}

void screen_back(uint8_t steps)
{
  if (col == 0)
    return;
  if (steps > col)
    steps = col;
  col -= steps;
  cursor_ptr -= steps;
}

void screen_putc(char c)
{
  if (col > max_col)
    screen_newline();
  else
    col++;

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
  memset(cursor_ptr, SCR_ICON_HLINE, length);
}

void screen_pm_draw_icon(uint8_t icon, uint8_t p, uint8_t y) {
  uint8_t *src = font_ptr + icon * 8;
  uint8_t *dst = pmg_mem + 0x200 + p * 128 + y;
  memcpy(dst, src, 8);
}

void screen_pm_clear_icon(uint8_t p, uint8_t y) {
  memset(pmg_mem + 0x200 + p * 128 + y, 0, 8);
}

uint8_t screen_input_default(char *result, uint8_t max_length, char *start_text)
{
  uint8_t err = ERR_OK;
  char c;
  char *tmp = malloc(max_length + 2);
  uint8_t i = strlen(start_text);

  screen_puts(start_text);
  // screen_gotoxy(col + i, row);
  POKE(cursor_ptr, 128);

  strcpy(tmp, start_text);

  while (1) {
    // For some reason kbhit() was letting garbage through
    // while (OS.ch == 255);
    while (!kbhit());
    c = cgetc();
    // OS.ch = 255;

    if (c == CH_ENTER) {
      POKE(cursor_ptr, 0);
      break;
    }
    else if (c == CH_ESC)
    {
      POKE(cursor_ptr, 0);
      err = ERR_ABORTED;
      break;
    }
    else if (i > 0 && (c == CH_DEL || c == CH_CURS_LEFT)) {
      POKE(cursor_ptr, 0);
      i--;
      cursor_ptr--;
      tmp[i] = '\0';
      POKE(cursor_ptr, 128);

      if (col == 0) {
        col = max_col;
      } else {
        col--;
      }
    }
    else if (i < max_length && c >= ' ' && c <= '|') {
      screen_putc(c);
      POKE(cursor_ptr, 128);
      tmp[i++] = c;
      tmp[i] = '\0';
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
