#include <conio.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "api.h"
#include "typedefs.h"
#include "set_location.h"
#include "util.h"
#include "globals.h"
#include "ui.h"

static Location results[5];
static Location *results_ptrs[5];

uint8_t get_loc(Location *loc)
{
    uint8_t num_results = 0;
    char query[80];
    char c;
    uint8_t i = 0;

    // Initialize pointers array
    for (i = 0; i < 5; i++)
    {
        results_ptrs[i] = &results[i];
    }
    readline(&query);

    printf("Searching...\n");
    api_geocode(query, results_ptrs, &num_results);

    if (num_results == 0)
    {
        printf("No matches found.\n");
        return ERR_NOT_FOUND;
    }
    else if (num_results == 1)
    {
        memcpy(loc, &results[0], sizeof(struct Location));
    }
    else
    {
        printf("Found %d matches:\n", num_results);

        for (i = 0; i < num_results; i++)
        {
            printf("%d: %s\n", i + 1, results[i].desc);
            printf("   %s\n", results[i].addr);
        }

        while (1)
        {
            c = cgetc();
            if (c == KEY_ABORT)
            {
                return ERR_ABORTED;
            }
            else if (c >= '1' && c <= '0' + num_results)
            {
                memcpy(loc, &results[c - '1'], sizeof(struct Location));
                return ERR_OK;
            }
        }
    }
    return ERR_OK;
}

void set_origin(void) {
    uint8_t err;

    ui_screen_origin();

    err = get_loc(&fromLoc);
    if (err != ERR_OK) {
        return;
    }

    state = SET_ROUTE_OPTIONS;
}

void set_destination(void)
{
    uint8_t err;

    ui_screen_destination();
    ui_screen_destination_menu_default();

    err = get_loc(&toLoc);
    if (err != ERR_OK) {
        return;
    }

    strcpy(routeOptions.country, toLoc.country);

    state = SET_ORIGIN;
}