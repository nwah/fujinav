#ifndef TYPEDEFS_H
#define TYPEDEFS_H

#define KEY_ABORT 27

#define ERR_OK 0
#define ERR_ABORTED 1
#define ERR_NOT_FOUND 2

typedef enum _state
{
    CHECK_SETTINGS,
    EDIT_SETTINGS,
    SET_DESTINATION,
    SET_ORIGIN,
    SET_ROUTE_OPTIONS,
    VIEW_DIRECTIONS,
    PRINT_DIRECTIONS,
    VIEW_QR_CODE,
    DONE
} State;

#endif // TYPEDEFS_H
