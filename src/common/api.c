#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdio.h>
#include <fujinet-network.h>
#include "api.h"
#include "globals.h"
#include "typedefs.h"

// #define GEOCODE_URL "N:HTTP://localhost:8080/nav/geocode"
// #define ROUTE_URL "N:HTTP://localhost:8080/nav/route"
#define GEOCODE_URL "N:HTTP://svart.local:8080/nav/geocode"
#define ROUTE_URL "N:HTTP://svart.local:8080/nav/route"
#define CHAR_NL 0x9B

char buf[3072];
char reqBody[128];
uint16_t bufsize = 0;

uint16_t get_until(char delimiter, char *buf, char *result) {
  uint16_t len = 0;
  while (*buf != delimiter && *buf != '\0') {
    *result++ = *buf++;
    len++;
  }
  *result = '\0';
  return len;
}

uint16_t get_line(char *buf, char *line) {
  return get_until((char)CHAR_NL, buf, line);
}

void parse_geocode_response(uint8_t *num_results, struct Location *results[]) {
  uint16_t pos = 0;
  uint8_t i = 0;
  char line[80];  // Only needed for first line with count
  char *bufp = buf;  // Start from beginning of buffer

  // Get number of results from first line
  bufp += get_line(bufp, line) + 1;
  *num_results = atoi(line);

  // Ensure we don't exceed array bounds
  if (*num_results > 5) {
    *num_results = 5;
  }

  // Parse each location
  for (i = 0; i < *num_results; i++) {
    bufp += get_line(bufp, results[i]->latlng) + 1;
    bufp += get_line(bufp, results[i]->desc) + 1;
    bufp += get_line(bufp, results[i]->addr) + 1;
    bufp += get_line(bufp, results[i]->country) + 1;
  }
}

uint8_t api_geocode(char *query, struct Location *results[], uint8_t *num_results) {
  uint8_t err = 0;
  uint8_t status;
  uint16_t bw;
  char *c;

  bufsize = 0;
  memset(buf, 0, sizeof(buf));

  err = network_open(GEOCODE_URL, OPEN_MODE_HTTP_POST, OPEN_TRANS_LF);
  if (err) {
    return err;
  }

  err = network_http_post(GEOCODE_URL, query);
  if (err) {
    network_close(GEOCODE_URL);
    return err;
  }

  network_status(GEOCODE_URL, &bw, &status, &err);
  if (err) {
    network_close(GEOCODE_URL);
    return err;
  }

  err = network_read(GEOCODE_URL, &buf, bw);
  if (err < 0) {
    network_close(GEOCODE_URL);
    return -err;
  }

  network_close(GEOCODE_URL);

  bufsize += bw;
  parse_geocode_response(num_results, results);

  return err;
}

void parse_route_response() {
  char line[128];
  char *bufp = buf;
  uint8_t i;

  // Get duration
  bufp += get_line(bufp, directions.duration) + 1;
  
  // Get distance
  bufp += get_line(bufp, directions.distance) + 1;
  
  // Get number of steps
  bufp += get_line(bufp, line) + 1;
  directions.num_steps = atoi(line);
  if (directions.num_steps > 32) {
    directions.num_steps = 32;
  }
  
  // Parse each step
  for (i = 0; i < directions.num_steps; i++) {
    // Get icon
    bufp += get_line(bufp, line) + 1;
    directions.steps[i].icon = line[0];
    // Get instructions
    bufp += get_line(bufp, line) + 1;
    strcpy(directions.steps[i].instructions, line);
  }
}

uint8_t api_route(char *fromLatLng, char *toLatLng, RouteOptions *options) {
  uint8_t err = 0;
  uint8_t status;
  uint16_t bw;
  uint16_t to_read = 512;

  bufsize = 0;
  memset(buf, 0, sizeof(buf));
  memset(reqBody, 0, sizeof(reqBody));

  snprintf(reqBody, sizeof(reqBody),
           "%s\n%s\n%s\n%s\n%s\n",
           options->mode,
            options->country,
            options->units,
           fromLatLng,
           toLatLng);

  err = network_open(ROUTE_URL, OPEN_MODE_HTTP_POST, OPEN_TRANS_LF);
  if (err) {
    return err;
  }

  // printf("%s", reqBody);
  err = network_http_post(ROUTE_URL, reqBody);
  if (err) {
    network_close(ROUTE_URL);
    return err;
  }

  network_status(ROUTE_URL, &bw, &status, &err);
  if (err) {
    network_close(ROUTE_URL);
    return err;
  }

  while (bw > 0) {
    if (to_read > bw) {
      to_read = bw;
    }
    if (bufsize + to_read > sizeof(buf)) {
      to_read = sizeof(buf) - bufsize;
    }
    if (to_read == 0) {
      break;
    }
    err = network_read(ROUTE_URL, &buf[bufsize], to_read);
    if (err < 0) {
      network_close(ROUTE_URL);
      return -err;
    }
    bufsize += to_read;

    network_status(ROUTE_URL, &bw, &status, &err);
  }

  network_close(ROUTE_URL);

  parse_route_response();

  return err;
}
