#include <conio.h>
#include <stdio.h>
#include "view_directions.h"
#include "api.h"
#include "globals.h"
#include "typedefs.h"
#include "ui.h"

void view_directions(void) {
    clrscr();
    ui_screen_routing();
    api_route(fromLoc.latlng, toLoc.latlng, &routeOptions);
    ui_screen_directions();
    cgetc();
    state = SET_DESTINATION;
}
