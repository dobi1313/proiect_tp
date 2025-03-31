
#ifndef SDL_UTILS_H
#define SDL_UTILS_H

#include <SDL2/SDL.h>
#include "game_object.h"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 640


int initialize(SDL_Window **window, SDL_Renderer **rend);
SDL_Texture* load_texture(SDL_Renderer *rend, const char *file);
void handle_input(int *up, int *down, int *left, int *right, int *close_requested);
void render(SDL_Renderer *rend, ship *main_ship, int is_hit);
void cleanup(SDL_Texture *tex, SDL_Renderer *rend, SDL_Window *window);

#endif
