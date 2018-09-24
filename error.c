#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_net.h>
#include <stdio.h>

#include "cJSON.h"
#include "error.h"

static Error_type current_error_type = ERROR_TYPE_OK;

Error_type current_error(void)
{
    return current_error_type;
}

void print_error_msg(Error_type error_type, const char *error_msg)
{
    switch(error_type) {
        case ERROR_TYPE_OK:
        case ERROR_TYPE_N:
            break;
        case ERROR_TYPE_SDL2:
            fprintf(stderr, "SDL2 error: %s: %s\n", error_msg, SDL_GetError());
            break;
        case ERROR_TYPE_IMAGE:
            fprintf(stderr, "SDL2_image error: %s: %s\n", error_msg, IMG_GetError());
            break;
        case ERROR_TYPE_NET:
            fprintf(stderr, "SDL2_net error: %s: %s\n", error_msg, SDLNet_GetError());
            break;
        case ERROR_TYPE_JSON:
            fprintf(stderr, "cJSON error: %s: %s\n", error_msg, cJSON_GetErrorPtr());
            break;
    }
}