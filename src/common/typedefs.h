#ifndef TYPEDEFS_H
#define TYPEDEFS_H

#define APPKEY_CREATOR_ID 0x4E42
#define APPKEY_APP_ID 0x02
#define APPKEY_ID_API_URL 0x01
#define APPKEY_ID_COUNTRY 0x02
#define APPKEY_ID_UNITS 0x03
#define APPKEY_ID_MODE 0x04

#define KEY_ABORT 27

#define ERR_OK 0
#define ERR_ABORTED 1
#define ERR_NOT_FOUND 2

#define MODE_TRANSIT "Transit"
#define MODE_DRIVING "Driving"
#define MODE_WALKING "Walking"
#define MODE_BIKING "Biking"

typedef enum _state
{
    CHECK_SETTINGS,
    EDIT_SETTINGS,
    SET_DESTINATION,
    SET_ORIGIN,
    VIEW_DIRECTIONS,
    PRINT_DIRECTIONS,
    VIEW_QR_CODE,
    DONE
} State;

typedef struct _settings
{
    char server[65];
} Settings;

#endif // TYPEDEFS_H
