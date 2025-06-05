#ifndef PRINTER_H
#define PRINTER_H

#include <stdint.h>
#include <atari.h>

void printer_open();
void printer_close();
uint8_t printer_print(char *str);
// void printer_print_directions(struct Directions *directions);

#endif