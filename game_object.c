#include "game_object.h"
#include <SDL2/SDL_image.h>
#include <stdio.h>




// projectile functions
void fire_projectile(projectile *projectiles, ship *main_ship, int projectile_type) {
    for (int i = 0; i < PROJECTILE_MAX; i++) {
        if (!projectiles[i].is_active) {
            switch (projectile_type) {
                case 1: // Single straight projectile
                      
                    projectiles[i].rect.w = 10;
                    projectiles[i].rect.h = 10;
                    projectiles[i].x_pos = main_ship->x_pos + main_ship->rect.w / 2 - projectiles[i].rect.w / 2;
                    projectiles[i].y_pos = main_ship->y_pos;
                    projectiles[i].x_vel = 0;
                    projectiles[i].y_vel = -PROJECTILE_SPEED;
                    projectiles[i].is_active = 1;
                    projectiles[i].damage = main_ship->damage;
                    break;

                case 2: // Two projectiles (spread)
                    projectiles[i].rect.w = 10;
                    projectiles[i].rect.h = 10;
                    projectiles[i].x_pos = main_ship->x_pos + main_ship->rect.w / 4 - projectiles[i].rect.w / 2;
                    projectiles[i].y_pos = main_ship->y_pos;
                    projectiles[i].x_vel = -50; // Slightly angled left
                    projectiles[i].y_vel = -PROJECTILE_SPEED;
                    projectiles[i].is_active = 1;
                    projectiles[i].damage = main_ship->damage;

                    // Spawn the second projectile
                    if (i + 1 < PROJECTILE_MAX) {
                        projectiles[i + 1].rect.w = 10;
                        projectiles[i + 1].rect.h = 10;
                        projectiles[i + 1].x_pos = main_ship->x_pos + 3 * main_ship->rect.w / 4 - projectiles[i + 1].rect.w / 2;
                        projectiles[i + 1].y_pos = main_ship->y_pos;
                        projectiles[i + 1].x_vel = 50; // Slightly angled right
                        projectiles[i + 1].y_vel = -PROJECTILE_SPEED;
                        projectiles[i + 1].is_active = 1;
                        projectiles[i + 1].damage = main_ship->damage;
                    }
                    break;

                case 3: // Three projectiles (fan spread)
                    projectiles[i].rect.w = 10;
                    projectiles[i].rect.h = 10;
                    projectiles[i].x_pos = main_ship->x_pos + main_ship->rect.w / 2 - projectiles[i].rect.w / 2;
                    projectiles[i].y_pos = main_ship->y_pos;
                    projectiles[i].x_vel = 0;
                    projectiles[i].y_vel = -PROJECTILE_SPEED;
                    projectiles[i].is_active = 1;
                    projectiles[i].damage = main_ship->damage;

                    // Spawn the left projectile
                    if (i + 1 < PROJECTILE_MAX) {
                        projectiles[i + 1].rect.w = 10;
                        projectiles[i + 1].rect.h = 10;
                        projectiles[i + 1].x_pos = main_ship->x_pos + main_ship->rect.w / 4 - projectiles[i + 1].rect.w / 2;
                        projectiles[i + 1].y_pos = main_ship->y_pos;
                        projectiles[i + 1].x_vel = -50; // Angled left
                        projectiles[i + 1].y_vel = -PROJECTILE_SPEED;
                        projectiles[i + 1].is_active = 1;
                        projectiles[i + 1].damage = main_ship->damage;
                    }

                    // Spawn the right projectile
                    if (i + 2 < PROJECTILE_MAX) {
                        projectiles[i + 2].rect.w = 10;
                        projectiles[i + 2].rect.h = 10;
                        projectiles[i + 2].x_pos = main_ship->x_pos + 3 * main_ship->rect.w / 4 - projectiles[i + 2].rect.w / 2;
                        projectiles[i + 2].y_pos = main_ship->y_pos;
                        projectiles[i + 2].x_vel = 50; // Angled right
                        projectiles[i + 2].y_vel = -PROJECTILE_SPEED;
                        projectiles[i + 2].is_active = 1;
                        projectiles[i + 2].damage = main_ship->damage;
                    }
                    break;

                case 4: // Four projectiles (vertical line)
                    projectiles[i].rect.w = 10;
                    projectiles[i].rect.h = 10;
                    projectiles[i].x_pos = main_ship->x_pos + main_ship->rect.w / 2 - projectiles[i].rect.w / 2;
                    projectiles[i].y_pos = main_ship->y_pos;
                    projectiles[i].x_vel = 0;
                    projectiles[i].y_vel = -PROJECTILE_SPEED;
                    projectiles[i].is_active = 1;
                    projectiles[i].damage = main_ship->damage;

                    // Spawn additional projectiles in a vertical line
                    for (int j = 0; j < 4 && i + j < PROJECTILE_MAX; j++) {
                        projectiles[i + j].rect.w = 10;
                        projectiles[i + j].rect.h = 10;
                        projectiles[i + j].x_pos = main_ship->x_pos + j * 15 - 2; // Offset horizontally
                        projectiles[i + j].y_pos = main_ship->y_pos;
                        projectiles[i + j].x_vel = 0;
                        projectiles[i + j].y_vel = -PROJECTILE_SPEED;
                        projectiles[i + j].is_active = 1;
                        projectiles[i + j].damage = main_ship->damage;
                    }
                    break;

                default:
                    printf("Invalid projectile type: %d\n", projectile_type);
                    break;
            }
            break; // Exit the loop after firing the projectile(s)
        }
    }
    if(main_ship->double_projectiles) {
        
        for (int i = 0; i < PROJECTILE_MAX; i++) {
        if (!projectiles[i].is_active) {
            switch (projectile_type) {
                case 1: // Single straight projectile
                    
                    projectiles[i].rect.w = 10;
                    projectiles[i].rect.h = 10;
                    projectiles[i].x_pos = main_ship->x_pos + main_ship->rect.w / 2 - projectiles[i].rect.w / 2;
                    projectiles[i].y_pos = main_ship->y_pos + 15;
                    projectiles[i].x_vel = 0;
                    projectiles[i].y_vel = -PROJECTILE_SPEED;
                    projectiles[i].is_active = 1;
                    projectiles[i].damage = main_ship->damage;
                    break;

                case 2: // Two projectiles (spread)
                    projectiles[i].rect.w = 10;
                    projectiles[i].rect.h = 10;
                    projectiles[i].x_pos = main_ship->x_pos + main_ship->rect.w / 4 - projectiles[i].rect.w / 2;
                    projectiles[i].y_pos = main_ship->y_pos + 15;
                    projectiles[i].x_vel = -50; // Slightly angled left
                    projectiles[i].y_vel = -PROJECTILE_SPEED;
                    projectiles[i].is_active = 1;
                    projectiles[i].damage = main_ship->damage;

                    // Spawn the second projectile
                    if (i + 1 < PROJECTILE_MAX) {
                        projectiles[i + 1].rect.w = 10;
                        projectiles[i + 1].rect.h = 10;
                        projectiles[i + 1].x_pos = main_ship->x_pos + 3 * main_ship->rect.w / 4 - projectiles[i + 1].rect.w / 2;
                        projectiles[i + 1].y_pos = main_ship->y_pos + 15;
                        projectiles[i + 1].x_vel = 50; // Slightly angled right
                        projectiles[i + 1].y_vel = -PROJECTILE_SPEED;
                        projectiles[i + 1].is_active = 1;
                        projectiles[i + 1].damage = main_ship->damage;
                    }
                    break;

                case 3: // Three projectiles (fan spread)
                    projectiles[i].rect.w = 10;
                    projectiles[i].rect.h = 10;
                    projectiles[i].x_pos = main_ship->x_pos + main_ship->rect.w / 2 - projectiles[i].rect.w / 2;
                    projectiles[i].y_pos = main_ship->y_pos + 15;
                    projectiles[i].x_vel = 0;
                    projectiles[i].y_vel = -PROJECTILE_SPEED;
                    projectiles[i].is_active = 1;
                    projectiles[i].damage = main_ship->damage;

                    // Spawn the left projectile
                    if (i + 1 < PROJECTILE_MAX) {
                        projectiles[i + 1].rect.w = 10;
                        projectiles[i + 1].rect.h = 10;
                        projectiles[i + 1].x_pos = main_ship->x_pos + main_ship->rect.w / 4 - projectiles[i + 1].rect.w / 2;
                        projectiles[i + 1].y_pos = main_ship->y_pos + 15;
                        projectiles[i + 1].x_vel = -50; // Angled left
                        projectiles[i + 1].y_vel = -PROJECTILE_SPEED;
                        projectiles[i + 1].is_active = 1;
                        projectiles[i + 1].damage = main_ship->damage;
                    }

                    // Spawn the right projectile
                    if (i + 2 < PROJECTILE_MAX) {
                        projectiles[i + 2].rect.w = 10;
                        projectiles[i + 2].rect.h = 10;
                        projectiles[i + 2].x_pos = main_ship->x_pos + 3 * main_ship->rect.w / 4 - projectiles[i + 2].rect.w / 2;
                        projectiles[i + 2].y_pos = main_ship->y_pos + 15;
                        projectiles[i + 2].x_vel = 50; // Angled right
                        projectiles[i + 2].y_vel = -PROJECTILE_SPEED;
                        projectiles[i + 2].is_active = 1;
                        projectiles[i + 2].damage = main_ship->damage;
                    }
                    break;

                case 4: // Four projectiles (vertical line)
                    projectiles[i].rect.w = 10;
                    projectiles[i].rect.h = 10;
                    projectiles[i].x_pos = main_ship->x_pos + main_ship->rect.w / 2 - projectiles[i].rect.w / 2;
                    projectiles[i].y_pos = main_ship->y_pos + 15;
                    projectiles[i].x_vel = 0;
                    projectiles[i].y_vel = -PROJECTILE_SPEED;
                    projectiles[i].is_active = 1;
                    projectiles[i].damage = main_ship->damage;

                    // Spawn additional projectiles in a vertical line
                    for (int j = 0; j < 4 && i + j < PROJECTILE_MAX; j++) {
                        projectiles[i + j].rect.w = 10;
                        projectiles[i + j].rect.h = 10;
                        projectiles[i + j].x_pos = main_ship->x_pos + j * 15 - 2; // Offset horizontally
                        projectiles[i + j].y_pos = main_ship->y_pos + 15;
                        projectiles[i + j].x_vel = 0;
                        projectiles[i + j].y_vel = -PROJECTILE_SPEED;
                        projectiles[i + j].is_active = 1;
                        projectiles[i + j].damage = main_ship->damage;
                    }
                    break;

                default:
                    printf("Invalid projectile type: %d\n", projectile_type);
                    break;
            }
            break; // Exit the loop after firing the projectile(s)
        }
    }
    }
}

void update_projectiles(projectile *projectiles, float dt) {
    for (int i = 0; i < PROJECTILE_MAX; i++) {
        if (projectiles[i].is_active) {
            projectiles[i].y_pos += projectiles[i].y_vel * dt;
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

void update_enemies(enemy *enemies,ship *main_ship) {
    for (int i = 0; i < ENEMY_MAX; i++) {
        if (enemies[i].is_active) {
            enemies[i].y_pos += enemies[i].y_vel / main_ship->slow_time / 60.0;

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

void handle_enemy_death(enemy *enemies, powerup *powerups) {
    enemies->is_active = 0;
    if (rand() % 100 < 50) {
        int powerup_type = rand() % POWERUP_TYPE_COUNT;
        powerups[powerup_type].is_active = 1;
        powerups[powerup_type].is_up = 0;
        powerups[powerup_type].type = powerup_type;
        powerups[powerup_type].x_pos = enemies->x_pos;
        powerups[powerup_type].y_pos = enemies->y_pos;
        powerups[powerup_type].y_vel = 50;
        powerups[powerup_type].rect.w = 20;
        powerups[powerup_type].rect.h = 20;
        powerups[powerup_type].rect.x = (int)powerups[powerup_type].x_pos;
        powerups[powerup_type].rect.y = (int)powerups[powerup_type].y_pos;
        
    }
}

// check collision functions
void check_projectile_enemy_collision(projectile *projectiles, enemy *enemies, unsigned int *score,unsigned int *exp, powerup *powerups, ship *main_ship) {
    for (int i = 0; i < PROJECTILE_MAX; i++) {
        if (projectiles[i].is_active){

        for (int j = 0; j < ENEMY_MAX; j++) {
            if (enemies[j].is_active){

            if (SDL_HasIntersection(&projectiles[i].rect, &enemies[j].rect)) {
                
                    
                    projectiles[i].is_active = 0;
                    enemies[j].is_hit = 1;
                    if (enemies[j].hp > 0) {
                        enemies[j].hp -= projectiles[i].damage;
                    } else {
                        enemies[j].is_active = 0;
                        *score += enemies[j].score * main_ship->double_points; 
                        *exp += enemies[j].score; 
                        handle_enemy_death(&enemies[j], powerups);
                    }
                    break;
                }
            }
            
        }
        }
    }
}

void check_enemy_ship_collision(ship *main_ship, enemy *enemies) {
    for (int i = 0; i < ENEMY_MAX; i++) {
        if (enemies[i].is_active && SDL_HasIntersection(&main_ship->rect, &enemies[i].rect)) {
            if (main_ship->has_shield) {
                main_ship->has_shield = 0; // Shield used up
            } else {
                int damage = enemies[i].hp - main_ship->armor;
                if (damage < 0) damage = 0;
                main_ship->ship_hp -= damage;
                if (main_ship->ship_hp <= 0) main_ship->ship_hp = 0;
            }
            main_ship->is_hit = 1;
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

void check_boss_ship_collision(ship *main_ship, boss *boss_enemy) {
    if (boss_enemy->is_active && SDL_HasIntersection(&main_ship->rect, &boss_enemy->rect)) {
        if (main_ship->has_shield) {
            main_ship->has_shield = 0; // Shield used up
        } else {
            int damage = boss_enemy->hp - main_ship->armor;
            if (damage < 0) damage = 0;
            main_ship->ship_hp -= damage;
            if (main_ship->ship_hp <= 0) main_ship->ship_hp = 0;
        }
        main_ship->is_hit = 1;
    }
}

// Lvl up functions
unsigned int calculate_exp_for_next_level(unsigned int level) {
    const unsigned int BASE_EXP = 100; 
    const float EXPONENT = 1.3;        
    return (unsigned int)(BASE_EXP * pow(level, EXPONENT));
}

int if_lvl_up(ship *main_ship, unsigned int *exp) {
    if (*exp >= calculate_exp_for_next_level(main_ship->level+1) && exp != 0) {
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
        main_ship->atk_speed = MAX(main_ship->atk_speed - 50, 50); // Ensure atk_speed doesn't go below 50
    }
    if(main_ship->level % 7 == 0) {
        main_ship->armor += 1;
    }
}

// boss functions(not well implemented yet)


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


// powerup functions
void power_up_effect(ship *main_ship, powerup *p) {
    switch (p->type) {
        case Shield:
            main_ship->has_shield = 1;
            p->is_active = 0; 
            p->is_up = 1;
            p->start_time = SDL_GetTicks();
            p->duration = 10000;
            break;
        case RapidFire:
            main_ship->rapid_fire = 2.0;
            p->is_active = 0; 
            p->is_up = 1;
            p->start_time = SDL_GetTicks();
            p->duration = 10000; 
            break;
        case SpeedBoost:
            main_ship->x_vel += 50; 
            p->is_active = 0; 
            p->is_up = 1;
            p->start_time = SDL_GetTicks();
            p->duration = 10000;
            break;
        case DoubleDamage:
            main_ship->damage *= 2; 
            p->is_active = 0; 
            p->is_up = 1;
            p->start_time = SDL_GetTicks();
            p->duration = 10000;
            break;
        case SlowTime:
            main_ship->slow_time = 2;
            p->is_active = 0; 
            p->is_up = 1;
            p->start_time = SDL_GetTicks();
            p->duration = 10000;
            break;
        case DoublePoints:
            main_ship->double_points = 2;
            p->is_active = 0; 
            p->is_up = 1;
            p->start_time = SDL_GetTicks();
            p->duration = 10000;
            break;
        case DoubleProjectiles:
            main_ship->double_projectiles = 1;
            p->is_active = 0; 
            p->is_up = 1;
            p->start_time = SDL_GetTicks();
            p->duration = 10000;
            break;
        default:
            break;
    }
}

void power_end_effect(ship *main_ship, powerup *p) {
    if(!p->is_up) return;
    switch (p->type) {
        case Shield:
            main_ship->has_shield = 0; 
            p->is_up = 0;
            break;
        case RapidFire:
            main_ship->rapid_fire = 1.0; 
            p->is_up = 0;
            break;
        case SpeedBoost:
            main_ship->x_vel -= 50; 
            p->is_up = 0;
            break;
        case DoubleDamage:
            main_ship->damage /= 2; 
            p->is_up = 0;
            break;
        case SlowTime:
            main_ship->slow_time = 1;
            p->is_up = 0;
            break;
        case DoublePoints:
            main_ship->double_points = 1;
            p->is_up = 0;
            break;
        case DoubleProjectiles:
            main_ship->double_projectiles = 0;
            p->is_up = 0;
            break;
        default:
            break;
    }
}


