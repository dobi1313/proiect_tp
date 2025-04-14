#include "game_object.h"
#include <SDL2/SDL_image.h>
#include <stdio.h>

void fire_projectile(projectile *projectiles, ship *main_ship) {
    for (int i = 0; i < PROJECTILE_MAX; i++) {
        if (!projectiles[i].is_active) {
            projectiles[i].rect.w = 10;
            projectiles[i].rect.h = 10;
            projectiles[i].x_pos = main_ship->x_pos + main_ship->rect.w / 2 - projectiles[i].rect.w / 2;
            projectiles[i].y_pos = main_ship->y_pos;
            projectiles[i].x_vel = 0;
            projectiles[i].y_vel = -PROJECTILE_SPEED; 
            projectiles[i].is_active = 1;
            projectiles[i].damage = main_ship->damage;
            break;
        }
    }
}

void update_projectiles(projectile *projectiles) {
    for (int i = 0; i < PROJECTILE_MAX; i++) {
        if (projectiles[i].is_active) {
            projectiles[i].y_pos += projectiles[i].y_vel / 60.0;

            
            if (projectiles[i].y_pos < 0) {
                projectiles[i].is_active = 0;
            }

            projectiles[i].rect.x = (int)projectiles[i].x_pos;
            projectiles[i].rect.y = (int)projectiles[i].y_pos;
        }
    }
}

void render_projectiles(SDL_Renderer *rend, projectile *projectiles) {
    for (int i = 0; i < PROJECTILE_MAX; i++) {
        if (projectiles[i].is_active) {
            SDL_SetRenderDrawColor(rend, 255, 255, 255, 255);
            SDL_RenderFillRect(rend, &projectiles[i].rect);
        }
    }
}

void update_position( int up, int down, int left, int right, ship *main_ship) {
    if(up && !down) main_ship->y_vel = -SPEED / 60.0;
    if(down && !up) main_ship->y_vel = SPEED / 60.0;

    if(left && !right) main_ship->x_vel = -SPEED / 60.0;
    if(right && !left) main_ship->x_vel = SPEED / 60.0;

    main_ship->x_pos += main_ship->x_vel;
    main_ship->y_pos += main_ship->y_vel;

    if (main_ship->x_pos < 0) main_ship->x_pos = 0;
    if (main_ship->x_pos > WINDOW_WIDTH - main_ship->rect.w) main_ship->x_pos = WINDOW_WIDTH - main_ship->rect.w;
    if (main_ship->y_pos < 0) main_ship->y_pos = 0;
    if (main_ship->y_pos > WINDOW_HEIGHT - main_ship->rect.h) main_ship->y_pos = WINDOW_HEIGHT - main_ship->rect.h;

    main_ship->rect.x = (int)main_ship->x_pos;
    main_ship->rect.y = (int)main_ship->y_pos;
}

void spawn_enemy(enemy *enemies, int enemy_hp) {
    for (int i = 0; i < ENEMY_MAX; i++) {
        if (!enemies[i].is_active) {  
            enemies[i].x_pos = rand() % (WINDOW_WIDTH - 40); 
            enemies[i].y_pos = 0; 
            enemies[i].rect.w = 40; 
            enemies[i].rect.h = 40;
            enemies[i].y_vel = 100; 
            enemies[i].is_active = 1;
            enemies[i].hp = enemy_hp;
            break;
        }
    }
}

void update_enemies(enemy *enemies) {
    for (int i = 0; i < ENEMY_MAX; i++) {
        if (enemies[i].is_active) {
            enemies[i].y_pos += enemies[i].y_vel / 60.0;

            if (enemies[i].y_pos > WINDOW_HEIGHT) {
                enemies[i].is_active = 0;
            }

            enemies[i].rect.x = (int)enemies[i].x_pos;
            enemies[i].rect.y = (int)enemies[i].y_pos;
        }
    }
}
void render_enemies(SDL_Renderer *rend, enemy *enemies) {
    Uint8 r, g, b, a;
    SDL_GetRenderDrawColor(rend, &r, &g, &b, &a); 
    for (int i = 0; i < ENEMY_MAX; i++) {
        if (enemies[i].is_active) {
            if (enemies[i].is_hit) {
                SDL_SetRenderDrawColor(rend, 255, 255, 0, 255); 
                SDL_RenderFillRect(rend, &enemies[i].rect);
                enemies[i].is_hit = 0; 
            } else {
                SDL_SetRenderDrawColor(rend, 255, 0, 0, 255); 
                SDL_RenderFillRect(rend, &enemies[i].rect);
            }
        }
    }

    SDL_SetRenderDrawColor(rend, r, g, b, a); 
}

void check_projectile_enemy_collision(projectile *projectiles, enemy *enemies) {
    for (int i = 0; i < PROJECTILE_MAX; i++) {
        if (!projectiles[i].is_active) continue; 

        for (int j = 0; j < ENEMY_MAX; j++) {
            if (!enemies[j].is_active) continue; 

            if (SDL_HasIntersection(&projectiles[i].rect, &enemies[j].rect)) {
                projectiles[i].is_active = 0; 
                enemies[j].is_hit = 1;
                if (enemies[j].hp > 0) {
                    enemies[j].hp -= projectiles[i].damage; 
                }
                if (enemies[j].hp <= 0) {
                    enemies[j].is_active = 0; 
                }
                break; 
            }
        }
    }
}

void check_enemy_ship_collision(ship *main_ship, enemy *enemies) {
    for (int i = 0; i < ENEMY_MAX; i++) {
        if (enemies[i].is_active && SDL_HasIntersection(&main_ship->rect, &enemies[i].rect)) {
            main_ship->ship_hp -= enemies[i].hp;
            main_ship->is_hit = 1;
            if (main_ship->ship_hp <= 0) {
                main_ship->ship_hp = 0; 
            } 
            enemies[i].is_active = 0; 
        }
    }
}