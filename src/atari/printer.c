#include <string.h>
#include <stdint.h>
#include <atari.h>
#include <_atarios.h>
#include "printer.h"

#define PRNT_CHAN 5
#define PRNT_DEV 2

extern char callciov(char);
extern char channel;
extern char result;

const char P[2] = "P:";

// struct __iocb
// {
//     unsigned char handler; /* handler index number (0xff free) */
//     unsigned char drive;   /* device number (drive) */
//     unsigned char command; /* command */
//     unsigned char status;  /* status of last operation */
//     void *buffer;          /* pointer to buffer */
//     void *put_byte;        /* pointer to device's PUT BYTE routine */
//     unsigned int buflen;   /* length of buffer */
//     unsigned char aux1;    /* 1st auxiliary byte */
//     unsigned char aux2;    /* 2nd auxiliary byte */
//     unsigned char aux3;    /* 3rd auxiliary byte */
//     unsigned char aux4;    /* 4th auxiliary byte */
//     unsigned char aux5;    /* 5th auxiliary byte */
//     unsigned char spare;   /* spare byte */
// };

void printer_open()
{
  OS.iocb[PRNT_CHAN].buffer = P;
  OS.iocb[PRNT_CHAN].buflen = sizeof(P);
  OS.iocb[PRNT_CHAN].drive = PRNT_DEV;
  OS.iocb[PRNT_CHAN].command = IOCB_OPEN;

  callciov(PRNT_CHAN);
}

void printer_close()
{
  OS.iocb[PRNT_CHAN].command = IOCB_CLOSE;

  callciov(PRNT_CHAN);
}

uint8_t printer_print(char *text)
{
  OS.iocb[PRNT_CHAN].command = IOCB_PUTCHR;
  OS.iocb[PRNT_CHAN].buffer = text;
  OS.iocb[PRNT_CHAN].buflen = strlen(text);

  callciov(PRNT_CHAN);

  return OS.iocb[PRNT_CHAN].status;
}

// void printer_print_directions(struct Directions *directions)
// {

// }
