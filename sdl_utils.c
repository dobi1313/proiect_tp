// sdl_utils.c
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
/*
void update_position(float *x_pos, float *y_pos, int *x_vel, int *y_vel, int up, int down, int left, int right, SDL_Rect *dest) {
    if(up && !down) *y_vel = -SPEED / 60.0;
    if(down && !up) *y_vel = SPEED / 60.0;
    //if(!up && !down) *y_vel = 0;
    //if(up && down) *y_vel = 0;

    if(left && !right) *x_vel = -SPEED / 60.0;
    if(right && !left) *x_vel = SPEED / 60.0;
    //if(!left && !right) *x_vel = 0;
    //if(left && right) *x_vel = 0;

    *x_pos += *x_vel;
    *y_pos += *y_vel;

    if (*x_pos < 0) *x_pos = 0;
    if (*x_pos > WINDOW_WIDTH - dest->w) *x_pos = WINDOW_WIDTH - dest->w;
    if (*y_pos < 0) *y_pos = 0;
    if (*y_pos > WINDOW_HEIGHT - dest->h) *y_pos = WINDOW_HEIGHT - dest->h;

    dest->x = (int)*x_pos;
    dest->y = (int)*y_pos;
}
*/

void render(SDL_Renderer *rend, ship *main_ship, int is_hit) {
    if (is_hit) 
        SDL_SetRenderDrawColor(rend, 255, 0, 0, 255); // Red if hit
    else 
        SDL_SetRenderDrawColor(rend, 0, 255, 0, 255); // Green normally

    SDL_RenderFillRect(rend, &main_ship->rect);
}
void cleanup(SDL_Texture *tex, SDL_Renderer *rend, SDL_Window *window) {
    SDL_DestroyTexture(tex);
    SDL_DestroyRenderer(rend);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

