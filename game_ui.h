#ifndef GAME_UI_H
#define GAME_UI_H

#include <SDL2/SDL.h>
#include "game_object.h"
#include <SDL2/SDL_ttf.h>

#define HP_BAR_WIDTH 200
#define HP_BAR_HEIGHT 20
#define HP_BAR_X (WINDOW_WIDTH - HP_BAR_WIDTH - 11)
#define HP_BAR_Y 10




void render_hp_bar(SDL_Renderer *rend, ship *main_ship); 
void render_game_over(SDL_Renderer *rend);
void render_score(SDL_Renderer *rend, int score);
void render_level_up_bar(SDL_Renderer *rend, unsigned int current_exp, unsigned int lvl);

// power up functions
void spawn_power_up(powerup *powerups, int power_up_type);
void render_power_up_block(SDL_Renderer *rend, powerup *p);
void render_power_up_bar(SDL_Renderer *rend, int power_up_type);
void check_power_up_collision(ship *main_ship, powerup *powerups, Uint32 current_time);
void update_power_up(powerup *powerups);
void render_shield(SDL_Renderer *rend, ship *main_ship);

#endif