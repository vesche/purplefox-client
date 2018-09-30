#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_net.h>
#include <stdio.h>
#include <stdbool.h>

#include "error.h"
#include "networking.h"
#include "payloads.h"

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

int main()
{
    // declare pointers
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Surface *surface;
    SDL_Texture *texture;

    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        print_error_msg(ERROR_TYPE_SDL2, "Couldn't initialize SDL");
        return 1;
    }

    window = SDL_CreateWindow(
        "purplefox",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        SCREEN_WIDTH,
        SCREEN_HEIGHT,
        SDL_WINDOW_OPENGL
    );

    if (window == NULL) {
        print_error_msg(ERROR_TYPE_SDL2, "Couldn't create SDL window");
        SDL_Quit();
        return 1;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    
    if (renderer == NULL) {
        print_error_msg(ERROR_TYPE_SDL2, "Couldn't create SDL renderer");
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    surface = IMG_Load("wizard.png");

    if (surface == NULL) {
        print_error_msg(ERROR_TYPE_IMAGE, "Couldn't create SDL surface");
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    if (texture == NULL) {
        printf("error create texture: %s\n", SDL_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    connect_to_server();
    
    /* testing networking.h
    
    SDL_Delay(1000);

    char *message_a = payload_login("test");
    client_send(message_a);

    // NOTE: there needs to be a SDL_Delay before sending new messaages to the server
    SDL_Delay(10);

    char *message_b = payload_move(13, 37);
    client_send(message_b);

    char *response = client_recv();
    handle_incoming(response);
    */

    // THREADING
    // https://github.com/raduprv/Eternal-Lands/blob/d277e1f8ff3cc257ac394e7393aa0d1442295b2a/main.c#L179
    // ------
    // static void *network_thread_data = NULL;
    SDL_Thread *network_thread;
    network_thread = SDL_CreateThread(client_loop, "client_loop", (void *)NULL);
    if (network_thread == NULL) {
        print_error_msg(ERROR_TYPE_SDL2, "Couldn't create thread");
        return 1;
    }
    // ------

    int x;
    int y;
    x = 0;
    y = 0;

    bool quit = false;

    SDL_Event event;

    while (!quit)
    {
        SDL_WaitEvent(&event);
        bool moved = false;

        switch (event.type)
        {
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym)
                {
                    case SDLK_q:
                        quit = true;
                        break;
                    case SDLK_LEFT:
                        x -= 1;
                        moved = true;
                        break;
                    case SDLK_RIGHT:
                        x += 1;
                        moved = true;
                        break;
                    case SDLK_UP:
                        y += 1;
                        moved = true;
                        break;
                    case SDLK_DOWN:
                        y -= 1;
                        moved = true;
                        break;
                }
        }

        if (moved) {
            char *message = payload_move(x, y);
            client_send(message);
        }

        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, texture, NULL, NULL);
        SDL_RenderPresent(renderer);
    }

    disconnect_from_server();

    // tear down graphics
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    
    // THREADING
    int thread_return_value;
    SDL_WaitThread(network_thread, &thread_return_value);
    printf("Thread returned: %d\n", thread_return_value);

    SDL_Quit();

    return 0;
}