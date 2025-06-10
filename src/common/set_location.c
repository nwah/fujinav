#include <conio.h>
#include <stdint.h>
#include <string.h>
#include "api.h"
#include "typedefs.h"
#include "set_location.h"
#include "globals.h"
#include "ui.h"

static Location results[5];
static Location *results_ptrs[5];

uint8_t get_loc(Location *loc)
{
    uint8_t num_results = 0;
    char query[40];
    char c;
    uint8_t i = 0;
    uint8_t choice = 0;
    uint8_t err = 0;

    // Initialize pointers array
    for (i = 0; i < 5; i++)
    {
        results_ptrs[i] = &results[i];
    }

    err = ui_screen_location_input_query(&query);
    if (err == ERR_ABORTED) {
      return err;
    }

    ui_screen_location_show_searching();
    api_geocode(query, results_ptrs, &num_results);

    if (num_results == 0)
    {
        ui_screen_location_show_no_matches();
        cgetc();
        return ERR_NOT_FOUND;
    }
    else if (num_results == 1)
    {
        memcpy(loc, &results[0], sizeof(struct Location));
    }
    else
    {
        err = ui_screen_location_choose_result(&choice, results_ptrs, num_results);
        if (err == ERR_OK) {
            memcpy(loc, &results[choice], sizeof(struct Location));
        }
        return err;
    }
    return ERR_OK;
}

void set_origin(void) {
    uint8_t err;

    ui_screen_origin();
    ui_screen_origin_menu_default();

    err = get_loc(&fromLoc);

    if (err == ERR_ABORTED) {
      state = SET_DESTINATION;
    }

    if (err != ERR_OK) {
        return;
    }

    strcpy(routeOptions.country, fromLoc.country);

    state = VIEW_DIRECTIONS;
}

void set_destination(void)
{
    uint8_t err;

    ui_screen_destination();
    ui_screen_destination_menu_default();

    err = get_loc(&toLoc);

    if (err == ERR_ABORTED) {
      state = EDIT_SETTINGS;
    }

    if (err != ERR_OK) {
        return;
    }

    strcpy(routeOptions.country, toLoc.country);

    state = SET_ORIGIN;
}
