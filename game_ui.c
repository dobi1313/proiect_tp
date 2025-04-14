#include "game_ui.h"

void render_hp_bar(SDL_Renderer *rend, ship *main_ship) {
    SDL_Rect hp_bar = {HP_BAR_X, HP_BAR_Y, HP_BAR_WIDTH, HP_BAR_HEIGHT};
    SDL_SetRenderDrawColor(rend, 255, 0, 0, 255); 
    SDL_RenderFillRect(rend, &hp_bar);
    
    float hp_ratio = (float)main_ship->ship_hp / 10.0; 
    SDL_Rect hp_fill = {HP_BAR_X, HP_BAR_Y, (int)(HP_BAR_WIDTH * hp_ratio), HP_BAR_HEIGHT};
    SDL_SetRenderDrawColor(rend, 0, 255, 0, 255); 
    SDL_RenderFillRect(rend, &hp_fill);
}