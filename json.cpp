#include "json.h"

uint16_t put_json(char *buf, uint16_t len, uint8_t type, char *name, float value, uint8_t precision);
    switch(type){
        case JSON_START:
            len = bstrncpy(buf, "{", len);
            goto end;
        case JSON_END:
            len = bstrncpy(buf, "}", len);
            goto end;
        default:
            // It is named something;
            len = bstrncpy(buf, "\"", len);
            len = bstrncpy(buf, name, len);
            len = bstrncpy(buf, "\":", len);
    }

    switch(type){
        case JSON_PUT_OBJECT:
            len = bstrncpy(buf, "{", len);
            goto end;
        case JSON_PUT_FLOAT:
        case JSON_PUT_FLOAT_COMMA:
        case JSON_PUT_FLOAT_END:
            //TODO put float character into buffer
            switch(type){
                case JSON_PUT_FLOAT:
                    goto end;
                case JSON_PUT_FLOAT_COMMA:
                    len = bstrncpy(buf, ",", len);
                    goto end;
                case JSON_PUT_FLOAT_END:
                    len = bstrncpy(buf, "}", len);
                    goto end;
            }
    }
end:
    return len;
}
