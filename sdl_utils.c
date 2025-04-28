
#include "sdl_utils.h"
#include <SDL2/SDL_image.h>
#include <stdio.h>



int initialize(SDL_Window **window, SDL_Renderer **rend) {
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) != 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    *window = SDL_CreateWindow("SDL2 Pixel Drawing", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    if (!*window) {
        printf("Window Error: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    *rend = SDL_CreateRenderer(*window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!*rend) {
        SDL_DestroyWindow(*window);
        SDL_Quit();
        return 1;
    }

    return 0;
}


SDL_Texture* load_texture(SDL_Renderer *rend, const char *file) {
    SDL_Surface *surface = IMG_Load(file);
    if (!surface) {
        printf("Image Load Error: %s\n", SDL_GetError());
        return NULL;
    }
    SDL_Texture *tex = SDL_CreateTextureFromSurface(rend, surface);
    SDL_FreeSurface(surface);
    if (!tex) {
        printf("Texture Creation Error: %s\n", SDL_GetError());
        return NULL;
    }
    return tex;
}


void handle_input(int *up, int *down, int *left, int *right, int *close_requested) {
    SDL_Event event;
    
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    *close_requested = 1;
                    break;

                case SDL_KEYDOWN:
                    switch (event.key.keysym.scancode) {
                        case SDL_SCANCODE_UP:
                        case SDL_SCANCODE_W:
                            *up = 1;
                            break;
                        case SDL_SCANCODE_DOWN:
                        case SDL_SCANCODE_S:
                            *down = 1;
                            break;
                        case SDL_SCANCODE_LEFT:
                        case SDL_SCANCODE_A:
                            *left = 1;
                            break;
                        case SDL_SCANCODE_RIGHT:
                        case SDL_SCANCODE_D:
                            *right = 1;
                            break;
                        default:
                            break;
                    }
                    break;

                case SDL_KEYUP:
                    switch (event.key.keysym.scancode) {
                        case SDL_SCANCODE_UP:
                        case SDL_SCANCODE_W:
                            *up = 0;
                            break;
                        case SDL_SCANCODE_DOWN:
                        case SDL_SCANCODE_S:
                            *down = 0;
                            break;
                        case SDL_SCANCODE_LEFT:
                        case SDL_SCANCODE_A:
                            *left = 0;
                            break;
                        case SDL_SCANCODE_RIGHT:
                        case SDL_SCANCODE_D:
                            *right = 0;
                            break;
                        default:
                            break;
                    }
                    break;
            }
    }    
}


void render_ship(SDL_Renderer *rend, ship *main_ship) {
    //printf("ship_hp: %d\n", main_ship->max_hp);
    if (main_ship->is_hit) 
        SDL_SetRenderDrawColor(rend, 255, 0, 0, 255); 
    else 
        SDL_SetRenderDrawColor(rend, 0, 255, 0, 255);

    SDL_RenderFillRect(rend, &main_ship->rect);
    if(main_ship->is_hit) {
        main_ship->is_hit = 0;
    }
}
void cleanup(TTF_Font *font, SDL_Renderer *rend, SDL_Window *window) {
    if (font) {
        TTF_CloseFont(font);
    }
    TTF_Quit(); 
    if (rend) {
        SDL_DestroyRenderer(rend);
    }
    if (window) {
        SDL_DestroyWindow(window);
    }
    SDL_Quit();
}

