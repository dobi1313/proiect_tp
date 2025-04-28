#include "game_object.h"
#include <SDL2/SDL_image.h>
#include <stdio.h>

// projectile functions
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

// ship functions
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

// enemy functions
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
            enemies[i].score = enemy_hp;
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

// check collision functions
void check_projectile_enemy_collision(projectile *projectiles, enemy *enemies, unsigned int *score,unsigned int *exp) {
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
                    *score += enemies[j].score;
                    *exp += enemies[j].score;
                }
                break; 
            }
        }
    }
}

void check_enemy_ship_collision(ship *main_ship, enemy *enemies) {
    for (int i = 0; i < ENEMY_MAX; i++) {
        if (enemies[i].is_active && SDL_HasIntersection(&main_ship->rect, &enemies[i].rect)) {
            main_ship->ship_hp -= (enemies[i].hp - main_ship->armor);
            main_ship->is_hit = 1;
            if (main_ship->ship_hp <= 0) {
                main_ship->ship_hp = 0; 
            } 
            enemies[i].is_active = 0; 
        }
    }
}

void check_boss_projectile_collision(projectile *projectiles, boss *boss_enemy, unsigned int *score, unsigned int *exp) {
    if (!boss_enemy->is_active) return;

    for (int i = 0; i < PROJECTILE_MAX; i++) {
        if (!projectiles[i].is_active) continue; 

        if (SDL_HasIntersection(&projectiles[i].rect, &boss_enemy->rect)) {
            projectiles[i].is_active = 0; 
            boss_enemy->hp -= projectiles[i].damage; 
            if (boss_enemy->hp <= 0) {
                boss_enemy->is_active = 0;
                *score += 100;
                *exp += 100; 
            }
            break; 
        }
    }
}


// Lvl up functions
unsigned int calculate_exp_for_next_level(unsigned int level) {
    const unsigned int BASE_EXP = 100; 
    const float EXPONENT = 1.3;        
    return (unsigned int)(BASE_EXP * pow(level, EXPONENT));
}

int if_lvl_up(ship *main_ship, unsigned int *exp) {
    if (*exp == calculate_exp_for_next_level(main_ship->level+1) && exp != 0) {
        *exp = 0;
        return 1; 
    }
    return 0; 
}
void main_ship_lvl_up(ship *main_ship) {
    main_ship->level++;
    main_ship->max_hp += 5;
    main_ship->ship_hp = main_ship->max_hp;
    if(main_ship->level % 3 == 0) {
        main_ship->damage += 1;
    }
    if(main_ship->level % 5 == 0) {
        main_ship->atk_speed -= 50; 
    }
    if(main_ship->level % 7 == 0) {
        main_ship->armor += 1;
    }
}

// boss functions


void update_boss(boss *boss_enemy) {
    if (!boss_enemy->is_active) return;

    
    boss_enemy->x_pos += boss_enemy->x_vel;
    if (boss_enemy->x_pos <= 0 || boss_enemy->x_pos + boss_enemy->rect.w >= WINDOW_WIDTH) {
        boss_enemy->x_vel = -boss_enemy->x_vel; 
    }

    boss_enemy->rect.x = (int)boss_enemy->x_pos;
    boss_enemy->rect.y = (int)boss_enemy->y_pos;
}

void render_boss(SDL_Renderer *rend, boss *boss_enemy) {
    if (boss_enemy->is_active) {
        SDL_SetRenderDrawColor(rend, 255, 0, 255, 255); 
        SDL_RenderFillRect(rend, &boss_enemy->rect);
    }
}
void check_boss_ship_collision(ship *main_ship, boss *boss_enemy) {
    if (boss_enemy->is_active && SDL_HasIntersection(&main_ship->rect, &boss_enemy->rect)) {
        main_ship->ship_hp -= (boss_enemy->hp - main_ship->armor);
        main_ship->is_hit = 1;
        if (main_ship->ship_hp <= 0) {
            main_ship->ship_hp = 0; 
        } 
    }
}


