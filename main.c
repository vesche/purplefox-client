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

// tmp until I have something better
SDL_Rect player_position;
#include "main.h"
void update_location(int x, int y)
{
    player_position.x = x;
    player_position.y = y;
}

int main()
{
    // declare pointers
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Surface *surface;
    SDL_Texture *texture;

    // sprite
    SDL_Rect player;

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

    // https://opengameart.org/content/tiny-16-basic
    surface = IMG_Load("sheet.png");

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
        print_error_msg(ERROR_TYPE_SDL2, "Couldn't create texture");
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    int frame_width, frame_height;
    int texture_width, texture_height;
    SDL_QueryTexture(texture, NULL, NULL, &texture_width, &texture_height);
    frame_width = texture_width / 16;   // 16 x 16 sprites on the sprite sheet
    frame_height = texture_height / 16;

    // player x, y, w, h
    player.x = 0;   // location of player on sprite sheet (0, 256)
    player.y = 256;
    player.w = frame_width;
    player.h = frame_height;

    player_position.x = player_position.y = 0;  // current player position (0, 0)
    player_position.w = player_position.h = 32; // size of player (32, 32)

    connect_to_server();

    // *********
    // Threading
    SDL_Thread *network_thread;
    network_thread = SDL_CreateThread(client_loop, "client_loop", (void *)NULL);
    if (network_thread == NULL) {
        print_error_msg(ERROR_TYPE_SDL2, "Couldn't create thread");
        return 1;
    }
    // *********

    bool quit = false;
    int frame_time = 0;
    char *direction = NULL;

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
                        player.y = 288;
                        moved = true;
                        direction = "left";
                        break;
                    case SDLK_RIGHT:
                        player.y = 320;
                        moved = true;
                        direction = "right";
                        break;
                    case SDLK_UP:
                        player.y = 352;
                        moved = true;
                        direction = "up";
                        break;
                    case SDLK_DOWN:
                        player.y = 256;
                        moved = true;
                        direction = "down";
                        break;
                }
        }

        if (moved) {
            char *message = payload_move(direction);
            client_send(message);

            frame_time++;
            if (frame_time == 4) {
                frame_time = 0;
                player.x += frame_width;
                if (player.x >= 96)
                    player.x = 0;
            }
        }

        SDL_RenderClear(renderer);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        // SDL_RenderCopy(renderer, texture, NULL, NULL);
        SDL_RenderCopy(renderer, texture, &player, &player_position);
        SDL_RenderPresent(renderer);
    }

    disconnect_from_server();

    // tear down graphics
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    
    // *********
    // Threading
    int thread_return_value;
    SDL_WaitThread(network_thread, &thread_return_value);
    printf("Thread returned: %d\n", thread_return_value);
    // *********

    IMG_Quit();
    SDL_Quit();

    return 0;
}