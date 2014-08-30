#ifndef __json_h
#define __json_h

#include <inttypes.h>

enum JSON_TYPE{
    JSON_START,             // {
    JSON_END,               // }
    JSON_PUT_OBJECT,        //"name":{
    JSON_PUT_FLOAT,         //"name":float_val
    JSON_PUT_FLOAT_COMMA,   //"name":float_val,
    JSON_PUT_FLOAT_END,     //"name":float_val}
};

uint16_t put_json(char *buf, uint16_t len, uint8_t type, char *name, float value, uint8_t precision);

#endif
