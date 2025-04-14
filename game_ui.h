#ifndef GAME_UI_H
#define GAME_UI_H

#include <SDL2/SDL.h>
#include "game_object.h"

#define HP_BAR_WIDTH 200
#define HP_BAR_HEIGHT 20
#define HP_BAR_X (WINDOW_WIDTH - HP_BAR_WIDTH - 10)
#define HP_BAR_Y 10

void render_hp_bar(SDL_Renderer *rend, ship *main_ship); 
/*void render_game_over(SDL_Renderer *rend) {
    SDL_SetRenderDrawColor(rend, 255, 255, 255, 255); 
    SDL_Rect game_over_rect = {WINDOW_WIDTH / 2 - 100, WINDOW_HEIGHT / 2 - 50, 200, 100};
    SDL_RenderFillRect(rend, &game_over_rect);
    
    // Render "Game Over" text here (not implemented)

}
*/

#endif