#include "game_ui.h"


void render_hp_bar(SDL_Renderer *rend, ship *main_ship) {
    SDL_Rect hp_bar = {HP_BAR_X, HP_BAR_Y, HP_BAR_WIDTH, HP_BAR_HEIGHT};
    SDL_SetRenderDrawColor(rend, 255, 0, 0, 255); 
    SDL_RenderFillRect(rend, &hp_bar);

    float hp_ratio = (float)main_ship->ship_hp / main_ship->max_hp; 
    SDL_Rect hp_fill = {HP_BAR_X, HP_BAR_Y, (int)(HP_BAR_WIDTH * hp_ratio), HP_BAR_HEIGHT};
    SDL_SetRenderDrawColor(rend, 0, 255, 0, 255); 
    SDL_RenderFillRect(rend, &hp_fill);
}

void render_game_over(SDL_Renderer *rend) {
    SDL_SetRenderDrawColor(rend, 255, 255, 255, 255); 
    SDL_Rect game_over_rect = {WINDOW_WIDTH / 2 - 100, WINDOW_HEIGHT / 2 - 50, 200, 100};
    SDL_RenderFillRect(rend, &game_over_rect);
    
    if (TTF_Init() == -1) {
        printf("Failed to initialize SDL_ttf: %s\n", TTF_GetError());
        return;
    }

    TTF_Font *font = TTF_OpenFont("/home/dobi/proiect_tp/game_resources/HomeVideoBold-R90Dv.ttf", 38); 
    if (!font) {
        printf("Failed to load font: %s\n", TTF_GetError());
        TTF_Quit();
        return;
    }

    SDL_Color text_color = {0, 0, 0, 255}; 
    SDL_Surface *text_surface = TTF_RenderText_Solid(font, "Game Over", text_color);
    if (!text_surface) {
        printf("Failed to create text surface: %s\n", TTF_GetError());
        TTF_CloseFont(font);
        TTF_Quit();
        return;
    }

    SDL_Texture *text_texture = SDL_CreateTextureFromSurface(rend, text_surface);
    if (!text_texture) {
        printf("Failed to create text texture: %s\n", SDL_GetError());
        SDL_FreeSurface(text_surface);
        TTF_CloseFont(font);
        TTF_Quit();
        return;
    }

    SDL_Rect text_rect = {WINDOW_WIDTH / 2 - text_surface->w / 2, WINDOW_HEIGHT / 2 - text_surface->h / 2, text_surface->w, text_surface->h};

    SDL_RenderCopy(rend, text_texture, NULL, &text_rect);
    SDL_DestroyTexture(text_texture);
    SDL_FreeSurface(text_surface);
    TTF_CloseFont(font);
    TTF_Quit();
}
void render_score(SDL_Renderer *rend, int score) {
    if (TTF_Init() == -1) {
        printf("Failed to initialize SDL_ttf: %s\n", TTF_GetError());
        return;
    }

    TTF_Font *font = TTF_OpenFont("/home/dobi/proiect_tp/game_resources/HomeVideoBold-R90Dv.ttf", 24); 
    if (!font) {
        printf("Failed to load font: %s\n", TTF_GetError());
        TTF_Quit();
        return;
    }

    SDL_Color text_color = {255, 255, 255, 255}; 
    char score_text[50];
    snprintf(score_text, sizeof(score_text), "Score: %d", score);
    SDL_Surface *text_surface = TTF_RenderText_Solid(font, score_text, text_color);
    if (!text_surface) {
        printf("Failed to create text surface: %s\n", TTF_GetError());
        TTF_CloseFont(font);
        TTF_Quit();
        return;
    }

    SDL_Texture *text_texture = SDL_CreateTextureFromSurface(rend, text_surface);
    if (!text_texture) {
        printf("Failed to create text texture: %s\n", SDL_GetError());
        SDL_FreeSurface(text_surface);
        TTF_CloseFont(font);
        TTF_Quit();
        return;
    }

    SDL_Rect text_rect = {10, 10, text_surface->w, text_surface->h};

    SDL_RenderCopy(rend, text_texture, NULL, &text_rect);
    SDL_DestroyTexture(text_texture);
    SDL_FreeSurface(text_surface);
    TTF_CloseFont(font);
}


void render_level_up_bar(SDL_Renderer *rend, unsigned int current_exp, unsigned int lvl) {
    const int BAR_WIDTH = 300;
    const int BAR_HEIGHT = 20;
    const int BAR_X = (WINDOW_WIDTH - BAR_WIDTH) / 2;
    const int BAR_Y = WINDOW_HEIGHT - BAR_HEIGHT - 20;

    
    float progress_ratio = (float)current_exp / calculate_exp_for_next_level(lvl + 1);
    if (progress_ratio > 1.0f) progress_ratio = 1.0f;

    
    SDL_Rect bar_background = {BAR_X, BAR_Y, BAR_WIDTH, BAR_HEIGHT};
    SDL_SetRenderDrawColor(rend, 128, 128, 128, 255); 
    SDL_RenderFillRect(rend, &bar_background);

    // Render the filled part of the bar (progress)
    SDL_Rect bar_fill = {BAR_X, BAR_Y, (int)(BAR_WIDTH * progress_ratio), BAR_HEIGHT};
    SDL_SetRenderDrawColor(rend, 0, 255, 255, 255); 
    SDL_RenderFillRect(rend, &bar_fill);

    // Render the player's level as text
    TTF_Font *font = TTF_OpenFont("/home/dobi/proiect_tp/game_resources/HomeVideoBold-R90Dv.ttf", 24); 
    if (!font) {
        printf("Failed to load font: %s\n", TTF_GetError());
        return;
    }

    SDL_Color text_color = {255, 255, 255, 255}; 
    char level_text[10];
    snprintf(level_text, sizeof(level_text), "Lvl %u", lvl); 

    SDL_Surface *text_surface = TTF_RenderText_Solid(font, level_text, text_color);
    if (!text_surface) {
        printf("Failed to create text surface: %s\n", TTF_GetError());
        TTF_CloseFont(font);
        return;
    }

    SDL_Texture *text_texture = SDL_CreateTextureFromSurface(rend, text_surface);
    if (!text_texture) {
        printf("Failed to create text texture: %s\n", SDL_GetError());
        SDL_FreeSurface(text_surface);
        TTF_CloseFont(font);
        return;
    }

    
    SDL_Rect text_rect = {BAR_X - text_surface->w - 10, BAR_Y + (BAR_HEIGHT - text_surface->h) / 2, text_surface->w, text_surface->h};
    SDL_RenderCopy(rend, text_texture, NULL, &text_rect);

    
    SDL_DestroyTexture(text_texture);
    SDL_FreeSurface(text_surface);
    TTF_CloseFont(font);
}