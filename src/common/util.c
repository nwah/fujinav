#include <conio.h>
#include <stdint.h>
#include <ctype.h>
#include <stdio.h>
#include "util.h"

void readline(char *s)
{
  uint16_t i = 0;
  uint8_t c;

  cursor(1);

  do {
    #ifdef __APPLE2__
    gotox(i);
    #endif

    c = cgetc();

    if (isprint(c)) {
      putchar(c);
      s[i++] = c;
    }
    else if ((c == CH_CURS_LEFT) || (c == CH_DEL)) {
      if (i) {
        putchar(CH_CURS_LEFT);
        putchar(' ');
        putchar(CH_CURS_LEFT);
        --i;
      }
    }
  } while (c != CH_ENTER);
  putchar('\n');
  s[i] = '\0';

  cursor(0);
}
