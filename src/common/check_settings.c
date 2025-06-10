#include <conio.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <fujinet-fuji.h>
#include "check_settings.h"
#include "typedefs.h"
#include "globals.h"

void init_defaults()
{
    strcpy(settings.server, "http://localhost:8080");
    strcpy(routeOptions.mode, "driving");
    strcpy(routeOptions.country, "us");
    strcpy(routeOptions.units, "mi");
}

int load_settings()
{
    uint8_t size = 0;
    bool ok = false;
    char buf[66];
    fuji_set_appkey_details(APPKEY_CREATOR_ID, APPKEY_APP_ID, DEFAULT);

    ok = fuji_read_appkey(APPKEY_ID_API_URL, &size, buf);
    if (!ok || size == 0) {
        return ERR_NOT_FOUND;
    }
    strcpy(settings.server, buf);
    settings.server[size] = '\0';

    ok = fuji_read_appkey(APPKEY_ID_COUNTRY, &size, buf);
    if (ok) {
        strcpy(routeOptions.country, buf);
    }

    ok = fuji_read_appkey(APPKEY_ID_UNITS, &size, buf);
    if (ok) {
        strcpy(routeOptions.units, buf);
    }

    ok = fuji_read_appkey(APPKEY_ID_MODE, &size, buf);
    if (ok) {
        strcpy(routeOptions.mode, buf);
    }

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
    // state = EDIT_SETTINGS;
}
