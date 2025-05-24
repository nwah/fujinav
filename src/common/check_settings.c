#include <conio.h>
#include <stdio.h>
#include <string.h>
#include "check_settings.h"
#include "typedefs.h"
#include "globals.h"

void init_defaults()
{
    strcpy(routeOptions.mode, "transit");
    strcpy(routeOptions.country, "us");
    strcpy(routeOptions.units, "mi");
}

void check_settings(void) {
    init_defaults();
    state = SET_DESTINATION;
}
