#include "ui_core.h"
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

uint8_t highlighted_row = 0xFF;

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

void dli_text(void);
void dli_logo_top(void);
void dli_logo_bottom(void);
void dli_highlight_start(void);
void dli_highlight_stop(void);

void dli_text(void)
{
 	asm("pha");
  asm("txa");
  asm("pha");
  asm("lda #$02");  // dark grey
  asm("sta $D40A"); // WSYNC
  asm("sta $D018"); // COLOR2
  if (highlighted_row == 0xFF) {
    OS.vdslst = &dli_logo_top;
  } else {
    OS.vdslst = &dli_highlight_start;
  }
  asm("pla");
  asm("tax");
  asm("pla");
  asm("rti");
}

void dli_logo_top(void)
{
 	asm("pha");
  asm("txa");
  asm("pha");
  asm("lda #$96");  // blue
  asm("sta $D40A"); // WSYNC
  asm("sta $D018"); // COLOR2
  // asm("lda #$66");
  // asm("sta $D017"); //COLOR2
  OS.vdslst = &dli_logo_bottom;
  asm("pla");
  asm("tax");
  asm("pla");
  asm("rti");
}

void dli_logo_bottom(void)
{
 	asm("pha");
  asm("txa");
  asm("pha");
  asm("lda #$36");  // red
  asm("sta $D40A"); // WSYNC
  asm("sta $D018"); //COLOR2
  OS.vdslst = &dli_text;
  asm("pla");
  asm("tax");
  asm("pla");
  asm("rti");
}

void dli_highlight_start(void)
{
 	asm("pha");
  asm("txa");
  asm("pha");
  asm("lda #$04");  // medium grey
  asm("sta $D40A"); // WSYNC
  asm("sta $D018"); // COLOR2
  OS.vdslst = &dli_highlight_stop;
  asm("pla");
  asm("tax");
  asm("pla");
  asm("rti");
}

void dli_highlight_stop(void)
{
 	asm("pha");
  asm("txa");
  asm("pha");
  asm("lda #$02");  // dark grey
  asm("sta $D40A"); // WSYNC
  asm("sta $D018"); // COLOR2
  OS.vdslst = &dli_logo_top;
  asm("pla");
  asm("tax");
  asm("pla");
  asm("rti");
}

void set_dlist(void *dlist_ptr, uint8_t size)
{
  memcpy((void *)dlist_mem, dlist_ptr, size);
}

void set_default_dlist(void)
{
  set_dlist(&default_dlist, sizeof(default_dlist));
}

void start_dli(void *dli)
{
  unsigned char prevVal = 0;
  // save previous val of 0x22F
  prevVal = *(unsigned char*)0x22F;
  // shut off ANTIC
  *(unsigned char*)0X22F = 0;

  OS.vdslst = dli;

  // restore ANTIC
  *(unsigned char*)0x22F = prevVal;

  wait_for_vblank();
  dli_start();
}

void set_dlist_dli_logo_with_text(void)
{
  dli_stop();
  set_dlist(&logo_with_text_dlist, sizeof(logo_with_text_dlist));
  start_dli(&dli_logo_top);
}

void highlight_row(uint8_t row)
{
  uint8_t *row_addr = dlist_mem + 24 + row;
  highlighted_row = row;

  if (row == 0xFF) {
    set_dlist_dli_logo_with_text();
    return;
  }

  dli_stop();
  set_dlist(&logo_with_text_dlist, sizeof(logo_with_text_dlist));

  POKE(row_addr, DL_DLI(DL_CHR40x8x1));
  POKE(row_addr + 1, DL_DLI(DL_CHR40x8x1));

  start_dli(&dli_logo_top);
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
