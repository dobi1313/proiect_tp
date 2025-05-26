
#ifndef SDL_UTILS_H
#define SDL_UTILS_H

#include <SDL2/SDL.h>
#include "game_object.h"
#include <SDL2/SDL_ttf.h>




int initialize(SDL_Window **window, SDL_Renderer **rend);
SDL_Texture* load_texture(SDL_Renderer *rend, const char *file);
void handle_input(int *up, int *down, int *left, int *right, int *close_requested, int *paused);
void render_ship(SDL_Renderer *rend, ship *main_ship);
void cleanup(TTF_Font *font, SDL_Renderer *rend, SDL_Window *window);

#endif
