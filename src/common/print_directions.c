#include <conio.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "globals.h"
#include "typedefs.h"
#include "ui.h"
#include "print_directions.h"

char output[2048];

void print_directions(void) {
    char c;
    FILE *printer;
    uint8_t i = 0;
    char *outp = &output[0];

    ui_screen_print();

    c = cgetc();
    if (c == CH_ESC) {
      state = VIEW_DIRECTIONS;
      return;
    }

    ui_screen_print_show_printing();

    printer = fopen("P1:", "w");

    memset(output, 0, sizeof(output));

    // fprintf(printer, "FujiNav Directions\n");
    // fprintf(printer, "\n");
    // fprintf(printer, "MODE:  %s\n", routeOptions.mode);
    // fprintf(printer, "FROM:  %s\n", fromLoc.desc);
    // fprintf(printer, "TO:    %s\n", toLoc.desc);
    // fprintf(printer, "\n");
    // fprintf(printer, "%s  |  %s \n", directions.distance, directions.duration);
    // fprintf(printer, "\n");

    outp += sprintf(outp, "FujiNav Directions\n");
    outp += sprintf(outp, "\n");
    outp += sprintf(outp, "MODE:  %s\n", routeOptions.mode);
    outp += sprintf(outp, "FROM:  %s\n", fromLoc.desc);
    outp += sprintf(outp, "TO:    %s\n", toLoc.desc);
    outp += sprintf(outp, "\n");
    outp += sprintf(outp, "%s  |  %s \n", directions.distance, directions.duration);
    outp += sprintf(outp, "\n");

    for (i = 0; i < directions.num_steps; i++) {
      outp += sprintf(outp, "%s\n", directions.steps[i].instructions);
    }

    fprintf(printer, "%s", output);
    fprintf(printer, "\n\n\n\n\n\n\n\n\n\n");
    fclose(printer);

    ui_screen_print_show_finished();

    cgetc();

    state = VIEW_DIRECTIONS;
}
