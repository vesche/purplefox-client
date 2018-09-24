#ifndef ERROR_H_
#define ERROR_H_

typedef enum Error_type {
    ERROR_TYPE_OK = 0,
    ERROR_TYPE_SDL2,
    ERROR_TYPE_IMAGE,
    ERROR_TYPE_NET,
    ERROR_TYPE_JSON,
    ERROR_TYPE_N
} Error_type;

Error_type current_error(void);

void print_error_msg(Error_type error_type, const char *error_msg);

#endif