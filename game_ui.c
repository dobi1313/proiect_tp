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

    TTF_Font *font = TTF_OpenFont("game_resources/HomeVideoBold-R90Dv.ttf", 38); 
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

    TTF_Font *font = TTF_OpenFont("game_resources/HomeVideoBold-R90Dv.ttf", 24); 
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
    TTF_Font *font = TTF_OpenFont("game_resources/HomeVideoBold-R90Dv.ttf", 24); 
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


void render_power_up_block(SDL_Renderer *rend, powerup *p) {
    if (!p->is_active) return;

    // Choose color based on power-up type
    switch (p->type) {
        case Shield:
            SDL_SetRenderDrawColor(rend, 0, 200, 255, 255); // Cyan
            break;
        case RapidFire:
            SDL_SetRenderDrawColor(rend, 255, 255, 0, 255); // Yellow
            break;
        case SpeedBoost:
            SDL_SetRenderDrawColor(rend, 0, 255, 0, 255); // Green
            break;
        case DoubleDamage:
            SDL_SetRenderDrawColor(rend, 255, 0, 0, 255); // Red
            break;
        case SlowTime:
            SDL_SetRenderDrawColor(rend, 128, 0, 255, 255); // Purple
            break;
        case DoublePoints:
            SDL_SetRenderDrawColor(rend, 255, 128, 0, 255); // Orange
            break;
        case DoubleProjectiles:
            SDL_SetRenderDrawColor(rend, 255, 0, 255, 255); // Magenta
            break;
        default:
            SDL_SetRenderDrawColor(rend, 200, 200, 200, 255); // Gray for unknown
            break;
    }

    SDL_RenderFillRect(rend, &p->rect);

    // Optional: Draw a white border
    SDL_SetRenderDrawColor(rend, 255, 255, 255, 255);
    SDL_RenderDrawRect(rend, &p->rect);
}
void update_power_up(powerup *powerups) {
    for (int i = 0; i < POWERUP_MAX; i++) {
        if (powerups[i].is_active) {
            powerups[i].y_pos += powerups[i].y_vel / 60.0;

            if (powerups[i].y_pos > WINDOW_HEIGHT) {
                powerups[i].is_active = 0;
            }

            powerups[i].rect.x = (int)powerups[i].x_pos;
            powerups[i].rect.y = (int)powerups[i].y_pos;
        }
    }
}
void check_power_up_collision(ship *main_ship, powerup *powerups) {
    for (int i = 0; i < POWERUP_TYPE_COUNT; i++) {
        if (powerups[i].is_active && SDL_HasIntersection(&main_ship->rect, &powerups[i].rect)) {
            
            if(powerups[i].is_up) {
                powerups[i].is_active = 0;
                powerups[i].duration = 10000; 
                continue;
            }
            else {
                power_up_effect(main_ship, &powerups[i]);
                powerups[i].is_active = 0;
            }
        }
    }
}
void render_shield(SDL_Renderer *rend, ship *main_ship) {
    if (!main_ship->has_shield) return;

    SDL_Rect shield_rect;
    shield_rect.w = main_ship->rect.w + 10;
    shield_rect.h = main_ship->rect.h + 10;
    shield_rect.x = main_ship->rect.x - 5;
    shield_rect.y = main_ship->rect.y - 5;

    SDL_SetRenderDrawColor(rend, 255, 255, 0, 100); // Semi-transparent yellow
    SDL_RenderFillRect(rend, &shield_rect);
}

// Pause menu rendering
int is_point_in_rect(int x, int y, SDL_Rect *rect) {
    return (x >= rect->x && x <= rect->x + rect->w &&
            y >= rect->y && y <= rect->y + rect->h);
}
void render_pause_menu(SDL_Renderer *rend) {
    SDL_SetRenderDrawColor(rend, 0, 0, 0, 200); // Semi-transparent overlay
    SDL_RenderFillRect(rend, NULL);

    // Render "PAUSED" text
    TTF_Font *font = TTF_OpenFont("game_resources/HomeVideoBold-R90Dv.ttf", 48);
    if (font) {
        SDL_Color color = {255, 255, 255, 255};
        SDL_Surface *surface = TTF_RenderText_Solid(font, "PAUSED", color);
        if (surface) {
            SDL_Texture *texture = SDL_CreateTextureFromSurface(rend, surface);
            SDL_Rect dst = {WINDOW_WIDTH/2 - surface->w/2, WINDOW_HEIGHT/2 - 120, surface->w, surface->h};
            SDL_RenderCopy(rend, texture, NULL, &dst);
            SDL_DestroyTexture(texture);
            SDL_FreeSurface(surface);
        }
        TTF_CloseFont(font);
    }

    // Resume button
    SDL_Rect resume_btn = {WINDOW_WIDTH/2 - 100, WINDOW_HEIGHT/2 - 20, 200, 60};
    SDL_SetRenderDrawColor(rend, 255, 255, 0, 255);
    SDL_RenderFillRect(rend, &resume_btn);

    font = TTF_OpenFont("game_resources/HomeVideoBold-R90Dv.ttf", 32);
    if (font) {
        SDL_Color color = {0, 0, 0, 255};
        SDL_Surface *surface = TTF_RenderText_Solid(font, "Resume", color);
        if (surface) {
            SDL_Texture *texture = SDL_CreateTextureFromSurface(rend, surface);
            SDL_Rect dst = {resume_btn.x + (resume_btn.w - surface->w)/2, resume_btn.y + (resume_btn.h - surface->h)/2, surface->w, surface->h};
            SDL_RenderCopy(rend, texture, NULL, &dst);
            SDL_DestroyTexture(texture);
            SDL_FreeSurface(surface);
        }
        TTF_CloseFont(font);
    }

    // Quit button
    SDL_Rect quit_btn = {WINDOW_WIDTH/2 - 100, WINDOW_HEIGHT/2 + 60, 200, 60};
    SDL_SetRenderDrawColor(rend, 200, 0, 0, 255);
    SDL_RenderFillRect(rend, &quit_btn);

    font = TTF_OpenFont("game_resources/HomeVideoBold-R90Dv.ttf", 32);
    if (font) {
        SDL_Color color = {255, 255, 255, 255};
        SDL_Surface *surface = TTF_RenderText_Solid(font, "Quit", color);
        if (surface) {
            SDL_Texture *texture = SDL_CreateTextureFromSurface(rend, surface);
            SDL_Rect dst = {quit_btn.x + (quit_btn.w - surface->w)/2, quit_btn.y + (quit_btn.h - surface->h)/2, surface->w, surface->h};
            SDL_RenderCopy(rend, texture, NULL, &dst);
            SDL_DestroyTexture(texture);
            SDL_FreeSurface(surface);
        }
        TTF_CloseFont(font);
    }

    SDL_RenderPresent(rend);

}


int handle_start_menu_mouse_click(int mouse_x, int mouse_y) {
    SDL_Rect start_btn = {WINDOW_WIDTH/2 - 100, WINDOW_HEIGHT/2 - 20, 200, 60};
    SDL_Rect quit_btn  = {WINDOW_WIDTH/2 - 100, WINDOW_HEIGHT/2 + 60, 200, 60};
    if (is_point_in_rect(mouse_x, mouse_y, &start_btn)) return 1; // Start
    if (is_point_in_rect(mouse_x, mouse_y, &quit_btn))  return 2; // Quit
    return 0;
}




int handle_pause_menu_mouse_click(int mouse_x, int mouse_y) {
    SDL_Rect resume_btn = {WINDOW_WIDTH/2 - 100, WINDOW_HEIGHT/2 - 20, 200, 60};
    SDL_Rect quit_btn   = {WINDOW_WIDTH/2 - 100, WINDOW_HEIGHT/2 + 60, 200, 60};

    if (is_point_in_rect(mouse_x, mouse_y, &resume_btn)) {
        return 1; // Resume
    }
    if (is_point_in_rect(mouse_x, mouse_y, &quit_btn)) {
        return 2; // Quit
    }
    return 0;
}
void render_start_menu(SDL_Renderer *rend) {
    SDL_SetRenderDrawColor(rend, 0, 0, 0, 255);
    SDL_RenderClear(rend);

    // --- Render the colorful title ---
    const char *title = "SPACE_SHOOTER";
    SDL_Color colors[] = {
        {255, 0, 0, 255},    // S - Red
        {255, 127, 0, 255},  // P - Orange
        {255, 255, 0, 255},  // A - Yellow
        {0, 255, 0, 255},    // C - Green
        {0, 0, 255, 255},    // E - Blue
        {75, 0, 130, 255},   // _ - Indigo
        {148, 0, 211, 255},  // S - Violet
        {255, 20, 147, 255}, // H - Pink
        {0, 255, 255, 255},  // O - Cyan
        {255, 215, 0, 255},  // O - Gold
        {0, 128, 128, 255},  // T - Teal
        {255, 69, 0, 255},   // E - OrangeRed
        {128, 0, 128, 255},  // R - Purple
    };
    int title_len = strlen(title);

    TTF_Font *font = TTF_OpenFont("game_resources/HomeVideoBold-R90Dv.ttf", 64);
    if (font) {
        int total_width = 0;
        int letter_widths[32] = {0};
        int letter_heights[32] = {0};
        SDL_Surface *surfaces[32] = {0};

        // Render each letter of the title with its corresponding color
        for (int i = 0; i < title_len; i++) {
            char letter[2] = {title[i], '\0'};
            surfaces[i] = TTF_RenderText_Solid(font, letter, colors[i % (sizeof(colors)/sizeof(colors[0]))]);
            if (surfaces[i]) {
                letter_widths[i] = surfaces[i]->w;
                letter_heights[i] = surfaces[i]->h;
                total_width += surfaces[i]->w;
            }
        }

        int x = WINDOW_WIDTH/2 - total_width/2;
        int y = WINDOW_HEIGHT/2 - 180;
        // Render each letter texture at the correct position
        for (int i = 0; i < title_len; i++) {
            if (surfaces[i]) {
                SDL_Texture *texture = SDL_CreateTextureFromSurface(rend, surfaces[i]);
                SDL_Rect dst = {x, y, letter_widths[i], letter_heights[i]};
                SDL_RenderCopy(rend, texture, NULL, &dst);
                x += letter_widths[i];
                SDL_DestroyTexture(texture);
                SDL_FreeSurface(surfaces[i]);
            }
        }
        TTF_CloseFont(font);
    }

    // --- Render Start and Quit buttons (after the title) ---
    SDL_Rect start_btn = {WINDOW_WIDTH/2 - 100, WINDOW_HEIGHT/2 - 20, 200, 60};
    SDL_SetRenderDrawColor(rend, 0, 200, 0, 255);
    SDL_RenderFillRect(rend, &start_btn);

    font = TTF_OpenFont("game_resources/HomeVideoBold-R90Dv.ttf", 32);
    if (font) {
        SDL_Color color = {255, 255, 255, 255};
        SDL_Surface *surface = TTF_RenderText_Solid(font, "Start", color);
        if (surface) {
            SDL_Texture *texture = SDL_CreateTextureFromSurface(rend, surface);
            SDL_Rect dst = {start_btn.x + (start_btn.w - surface->w)/2, start_btn.y + (start_btn.h - surface->h)/2, surface->w, surface->h};
            SDL_RenderCopy(rend, texture, NULL, &dst);
            SDL_DestroyTexture(texture);
            SDL_FreeSurface(surface);
        }
        TTF_CloseFont(font);
    }

    SDL_Rect quit_btn = {WINDOW_WIDTH/2 - 100, WINDOW_HEIGHT/2 + 60, 200, 60};
    SDL_SetRenderDrawColor(rend, 200, 0, 0, 255);
    SDL_RenderFillRect(rend, &quit_btn);

    font = TTF_OpenFont("game_resources/HomeVideoBold-R90Dv.ttf", 32);
    if (font) {
        SDL_Color color = {255, 255, 255, 255};
        SDL_Surface *surface = TTF_RenderText_Solid(font, "Quit", color);
        if (surface) {
            SDL_Texture *texture = SDL_CreateTextureFromSurface(rend, surface);
            SDL_Rect dst = {quit_btn.x + (quit_btn.w - surface->w)/2, quit_btn.y + (quit_btn.h - surface->h)/2, surface->w, surface->h};
            SDL_RenderCopy(rend, texture, NULL, &dst);
            SDL_DestroyTexture(texture);
            SDL_FreeSurface(surface);
        }
        TTF_CloseFont(font);
    }

    SDL_RenderPresent(rend);
}

