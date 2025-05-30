#include <stdio.h>
#include <string.h>
#include <atari.h>
#include <conio.h>
#include <peekpoke.h>
#include "api.h"
#include "util.h"
#include "globals.h"
#include "logo.c"

#define DISPLAY_LIST 0x0600              // Memory address to store DISPLAY_LIST.  0x0600 is the first address available for user space memory (1)
#define DISPLAY_MEMORY 0x7400

#include "logo.h"
// Picture data
const unsigned char logoData[640] = {
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 64, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 65, 80, 64, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 170, 149, 80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 42, 168, 32, 2, 0, 130, 0, 129, 144, 64, 32, 0, 32, 0, 128, 32, 0, 32, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 32, 0, 32, 2, 0, 130, 0, 128, 128, 64, 40, 0, 32, 0, 128, 32, 0, 32, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 32, 0, 32, 2, 0, 130, 3, 193, 145, 80, 34, 0, 32, 2, 32, 8, 0, 128, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 32, 0, 32, 2, 0, 130, 31, 245, 170, 149, 34, 0, 32, 2, 32, 8, 0, 128, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 32, 0, 32, 2, 0, 130, 15, 241, 80, 144, 32, 128, 32, 8, 8, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 42, 168, 32, 2, 0, 130, 3, 192, 64, 128, 32, 32, 32, 8, 8, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 32, 0, 32, 2, 0, 130, 0, 64, 64, 240, 32, 8, 32, 8, 8, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 32, 0, 32, 2, 0, 130, 5, 85, 87, 253, 32, 2, 32, 42, 170, 0, 136, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 32, 0, 32, 2, 0, 130, 0, 64, 67, 252, 32, 2, 32, 32, 2, 0, 136, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 32, 0, 8, 8, 0, 130, 0, 0, 64, 240, 32, 0, 160, 128, 0, 128, 32, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 32, 0, 2, 160, 42, 2, 0, 1, 85, 64, 32, 0, 32, 128, 0, 128, 32, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 64, 64, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

// Color data
const unsigned char colors[4] = {
    0, 4, 14, 170};

// Color data
const unsigned char colors2[4] = {
    0, 4, 14, 52};

void default_dlist = {
    DL_BLK8,              // 0x00 (8 Blank Scanlines)
    DL_BLK8,              // 0x01 (8 Blank Scanlines)
    DL_BLK8,              // 0x02 (8 Blank Scanlines)
    DL_LMS(DL_CHR40x8x1), // 0x03 Line 0 (first line of displayable text, will start at coordinates 0,0)
    DISPLAY_MEMORY,       // 0x04 and 0x05 This is the high order bit location of the display list.  Defined in screen.h
    DL_CHR40x8x1,         // 0x06  Line 1
    DL_CHR40x8x1,         // 0x07  Line 2
    DL_CHR40x8x1,         // 0x08  Line 3
    DL_CHR40x8x1,         // 0x09  Line 4
    DL_CHR40x8x1,         // 0x0a  Line 5
    DL_CHR40x8x1,         // 0x0b  Line 6
    DL_CHR40x8x1,         // 0x0c  Line 7
    DL_CHR40x8x1,         // 0x0d  Line 8
    DL_CHR40x8x1,         // 0x0e  Line 9
    DL_CHR40x8x1,         // 0x0f  Line 10
    DL_CHR40x8x1,         // 0x10  Line 11
    DL_CHR40x8x1,         // 0x11  Line 12
    DL_CHR40x8x1,         // 0x12  Line 13
    DL_CHR40x8x1,         // 0x13  Line 14
    DL_CHR40x8x1,         // 0x14  Line 15
    DL_CHR40x8x1,         // 0x15  Line 16
    DL_CHR40x8x1,         // 0x16  Line 17
    DL_CHR40x8x1,         // 0x17  Line 18
    DL_CHR40x8x1,         // 0x18  Line 19
    DL_CHR40x8x1,         // 0x19  Line 20
    DL_CHR40x8x1,         // 0x1a  Line 21
    DL_CHR40x8x1,         // 0x1b  Line 22
    DL_CHR40x8x1,         // 0x1c  Line 23
    DL_CHR40x8x1,         // 0x1d  Line 24
    DL_CHR40x8x1,         // 0x1e  Line 25
    DL_CHR40x8x1,         // 0x1f  Line 26
    DL_CHR40x8x1,         // 0x20  Line 27
    DL_CHR40x8x1,         // 0x21  Line 28
    DL_CHR40x8x1,         // 0x22  Line 29
    DL_CHR40x8x1,         // 0x23  Line 30
    DL_JVB,               // Signal to ANTIC end of DISPLAY_LIST has been reached and loop back to the beginning.  The jump to the begining is located at the next two bits defined below.
    DISPLAY_LIST          // 0x1f, 0x20  Memory address containing the entire display list.
};

void dli_text(void);
void dli_logo_top(void);
void dli_logo_bottom(void);

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
  asm("lda #$94");  // blue
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
  asm("lda #$34");  // red
  asm("sta $D40A"); // WSYNC
  asm("sta $D018"); //COLOR2
  OS.vdslst = &dli_text;
  asm("pla");
  asm("rti");
}


void dlist_splash(void)
{
  memcpy((void *)DISPLAY_LIST, &default_dlist, sizeof(default_dlist));

  // memcpy((void *)DISPLAY_MEMORY, &logoData, sizeof(logoData));
  // POKE(DISPLAY_LIST + 0x07, DL_MAP160x2x4);
  // POKE(DISPLAY_LIST + 0x08, DL_MAP160x2x4);
  // POKE(DISPLAY_LIST + 0x09, DL_MAP160x2x4);
  // POKE(DISPLAY_LIST + 0x0a, DL_MAP160x2x4);
  // POKE(DISPLAY_LIST + 0x0b, DL_MAP160x2x4);
  // POKE(DISPLAY_LIST + 0x0c, DL_MAP160x2x4);
  // POKE(DISPLAY_LIST + 0x0d, DL_MAP160x2x4);
  // POKE(DISPLAY_LIST + 0x0e, DL_MAP160x2x4);
  // POKE(DISPLAY_LIST + 0x0f, DL_MAP160x2x4);
  // POKE(DISPLAY_LIST + 0x10, DL_MAP160x2x4);
  // POKE(DISPLAY_LIST + 0x11, DL_MAP160x2x4);
  // POKE(DISPLAY_LIST + 0x12, DL_MAP160x2x4);
  // POKE(DISPLAY_LIST + 0x13, DL_MAP160x2x4);
  // POKE(DISPLAY_LIST + 0x14, DL_MAP160x2x4);

  POKE(DISPLAY_LIST + 0x06, DL_DLI(DL_LMS(DL_MAP160x2x4)));
  // POKE(DISPLAY_LIST + 0x06, DL_LMS(DL_MAP160x2x4));
  POKEW(DISPLAY_LIST + 0x07, &logoData);
  POKE(DISPLAY_LIST + 0x09, DL_MAP160x2x4);
  POKE(DISPLAY_LIST + 0x0a, DL_MAP160x2x4);
  POKE(DISPLAY_LIST + 0x0b, DL_MAP160x2x4);
  POKE(DISPLAY_LIST + 0x0c, DL_MAP160x2x4);
  POKE(DISPLAY_LIST + 0x0d, DL_MAP160x2x4);
  POKE(DISPLAY_LIST + 0x0e, DL_MAP160x2x4);
  POKE(DISPLAY_LIST + 0x0f, DL_MAP160x2x4);
  POKE(DISPLAY_LIST + 0x10, DL_DLI(DL_MAP160x2x4));
  POKE(DISPLAY_LIST + 0x11, DL_MAP160x2x4);
  POKE(DISPLAY_LIST + 0x12, DL_MAP160x2x4);
  POKE(DISPLAY_LIST + 0x13, DL_MAP160x2x4);
  POKE(DISPLAY_LIST + 0x14, DL_MAP160x2x4);
  POKE(DISPLAY_LIST + 0x15, DL_MAP160x2x4);
  POKE(DISPLAY_LIST + 0x16, DL_DLI(DL_MAP160x2x4));
  POKE(DISPLAY_LIST + 0x17, DL_LMS(DL_CHR40x8x1));
  POKEW(DISPLAY_LIST + 0x18, DISPLAY_MEMORY);
}

void dlist_settings(void)
{
  memcpy((void *)DISPLAY_LIST, &default_dlist, sizeof(default_dlist));
  // POKE(DISPLAY_LIST + 0x06, DL_CHR20x8x2);
}

void ui_init(void)
{
  memcpy((void *)DISPLAY_LIST, &default_dlist, sizeof(default_dlist));
  OS.sdlst = (void *)DISPLAY_LIST;                                   // and use it.
  // video_ptr = (unsigned char *)(DISPLAY_MEMORY);
}

void ui_screen_splash() {
  unsigned char prevVal = 0;

  OS.color4 = 0x02;
  OS.color0 = 0x04;
  OS.color1 = 0x0E;
  // OS.color2 = 0x36;
  OS.color2 = 0x02;

  // clrscr();
  // save previous val of 0x22F
  prevVal = *(unsigned char*)0x22F;
  // shut off ANTIC
  *(unsigned char*)0X22F = 0;

  // set the dlist screen
  dlist_splash();
  OS.vdslst = &dli_logo_top;

  // restore ANTIC
  *(unsigned char*)0x22F = prevVal;

  wait_for_vblank();
  start_dli();

  POKE(DISPLAY_MEMORY + 82, 65 - 32);

  // puts("SPLASH 1\n");
  // puts("SPLASH 2\n");
  // puts("SPLASH 3\n");
  // puts("SPLASH 4\n");
  // puts("SPLASH 5\n");
  // puts("SPLASH 6\n");
  // puts("SPLASH 7\n");
  // puts("SPLASH 8\n");
  // puts("SPLASH 8\n");
}

void ui_screen_settings() {
  clrscr();
  dlist_settings();
  printf("Settings");
}

void ui_screen_destination() {
  clrscr();
  // show_logo();
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
