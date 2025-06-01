#include <conio.h>
#include <stdio.h>
#include <string.h>
#include <fujinet-fuji.h>
#include "check_settings.h"
#include "typedefs.h"
#include "globals.h"

void init_defaults()
{
    strcpy(routeOptions.mode, "transit");
    strcpy(routeOptions.country, "us");
    strcpy(routeOptions.units, "mi");
    strcpy(settings.server, "http://localhost:8080");
}

int load_settings()
{
    uint8_t size = 0;
    bool ok = false;
    char buf[66];
    printf("Loading settings...\n");
    fuji_set_appkey_details(APPKEY_CREATOR_ID, APPKEY_APP_ID, DEFAULT);

    ok = fuji_read_appkey(APPKEY_ID_API_URL, &size, buf);
    if (!ok || size == 0) {
        return ERR_NOT_FOUND;
    }
    strcpy(settings.server, buf);
    printf("Server: %s\n", settings.server);
    ok = fuji_read_appkey(APPKEY_ID_COUNTRY, &size, buf);
    if (ok) {
        strcpy(routeOptions.country, buf);
    }
    printf("Country: %s\n", routeOptions.country);
    ok = fuji_read_appkey(APPKEY_ID_UNITS, &size, buf);
    if (ok) {
        strcpy(routeOptions.units, buf);
    }
    printf("Units: %s\n", routeOptions.units);
    return ERR_OK;
}

void check_settings(void) {
    uint8_t result;
    init_defaults();

    result = load_settings();
    if (result == ERR_OK) {
        state = SET_DESTINATION;
    }
    else {
        state = EDIT_SETTINGS;
    }

    state = SET_DESTINATION;
}
