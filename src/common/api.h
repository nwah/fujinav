#ifndef API_H
#define API_H

#include <stdint.h>

typedef struct Location {
    char latlng[21];
    char desc[32];
    char addr[128];
    char country[3];
} Location;

typedef struct RouteOptions {
    char mode[16];
    char country[3];
    char units[3];
} RouteOptions;

typedef struct Step {
    char instructions[128];
    char icon;
} Step;

typedef struct Directions {
    char duration[16];
    char distance[16];
    uint8_t num_steps;
    Step steps[32];
} Directions;

uint8_t api_geocode(char *query, struct Location *result[], uint8_t *num_results);
uint8_t api_route(char *fromLatLng, char *toLatLng, struct RouteOptions *options);

#endif // API_H
