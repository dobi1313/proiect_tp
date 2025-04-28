#include "sdl_utils.h"
#include "game_object.h"
#include "game_ui.h"

int main(void) {
    SDL_Window *window;
    SDL_Renderer *rend;

    if (initialize(&window, &rend) != 0) return 1;

    ship main_ship;
    main_ship.ship_hp = 50;
    main_ship.max_hp = main_ship.ship_hp;
    printf("ship_hp: %d\n", main_ship.max_hp);
    main_ship.atk_speed = 500;
    main_ship.damage = 3;
    main_ship.armor = 1;
    main_ship.level = 0;

    projectile proj[PROJECTILE_MAX] = {0};

    enemy enemies[ENEMY_MAX] = {0};
    int enemy_hp = 10;
    main_ship.rect.w = 50; 
    main_ship.rect.h = 50; 
    main_ship.x_pos = (WINDOW_WIDTH - main_ship.rect.w) / 2;
    main_ship.y_pos = (WINDOW_HEIGHT - main_ship.rect.h) / 2;

    boss boss = {0};


    int up = 0, down = 0, left = 0, right = 0, close_requested = 0;

    Uint32 last_projectile_time = 0;
    Uint32 last_enemy_spawn_time = 0;
    Uint32 spawn_time = 2000;
    Uint32 score = 0;
    Uint32 experience = 0;

    while (!close_requested) {
        handle_input(&up, &down, &left, &right, &close_requested);

        main_ship.x_vel = 0;
        main_ship.y_vel = 0;
        update_position(up, down, left, right, &main_ship);
        
        Uint32 current_time = SDL_GetTicks();

        if (current_time > last_projectile_time + main_ship.atk_speed) {
            fire_projectile(proj, &main_ship);
            last_projectile_time = current_time;
        }

        if (current_time > last_enemy_spawn_time + spawn_time) {
            spawn_enemy(enemies, enemy_hp);
            last_enemy_spawn_time = current_time;
        }
        
        if (current_time % 30000 == 0) {
            enemy_hp++;
            spawn_time -= 50;
        }

        if (current_time % 300000 == 0) {
            boss.hp = enemy_hp * 15; 
            boss.dmg = 10; 
            boss.is_active = 1; 
            boss.rect.w = 100; 
            boss.rect.h = 100; 
            boss.x_pos = (WINDOW_WIDTH - boss.rect.w) / 2; 
            boss.y_pos = -boss.rect.h;
            render_boss(rend, &boss); 
        }
        
        if (boss.is_active) {
            update_boss(&boss);
            check_boss_projectile_collision(proj, &boss, &score, &experience);
            check_boss_ship_collision(&main_ship, &boss);
            render_boss(rend, &boss); 
        }
        
        update_projectiles(proj);
        update_enemies(enemies);
        check_projectile_enemy_collision(proj, enemies, &score, &experience);
        check_enemy_ship_collision(&main_ship, enemies);
        
        if (main_ship.ship_hp <= 0) {
            render_game_over(rend);
            SDL_RenderPresent(rend);
            SDL_Delay(2000);
            break; 
        }
        

        if(if_lvl_up(&main_ship, &experience)) {
            main_ship_lvl_up(&main_ship);
        }
        
        SDL_SetRenderDrawColor(rend, 0, 0, 0, 255);  
        SDL_RenderClear(rend);
        
        render_projectiles(rend, proj);
        render_enemies(rend, enemies);
        
        render_ship(rend, &main_ship); 
        
        render_hp_bar(rend, &main_ship);
        
        render_score(rend, score);
        render_level_up_bar(rend, experience, main_ship.level);
        
        SDL_RenderPresent(rend);

        SDL_Delay(1000 / 60);
    }
    cleanup(NULL, rend, window); 

    return 0;
}