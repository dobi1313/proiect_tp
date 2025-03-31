#include "sdl_utils.h"
#include "game_object.h"



int main(void) {
    SDL_Window *window;
    SDL_Renderer *rend;

    if (initialize(&window, &rend) != 0) return 1;

    SDL_Texture *tex = load_texture(rend, "/home/dobi/proiect_tp/Game_img/first_img.png");
    if (!tex) {
        cleanup(tex, rend, window);
        return 1;
    }

    ship main_ship;
    projectile proj[PROJECTILE_MAX] = {0};
    enemy enemies[ENEMY_MAX] = {0};


    SDL_QueryTexture(tex, NULL, NULL, &main_ship.rect.w, &main_ship.rect.h);
    main_ship.rect.w /= 6; main_ship.rect.h /= 6;
    main_ship.x_pos = (WINDOW_WIDTH - main_ship.rect.w) / 2, main_ship.y_pos = (WINDOW_HEIGHT - main_ship.rect.h) / 2;

    int up = 0, down = 0, left = 0, right = 0, close_requested = 0;

    Uint32 last_projectile_time = 0;
    Uint32 last_enemy_spawn_time = 0;

    while (!close_requested) {
        handle_input(&up, &down, &left, &right, &close_requested);

        main_ship.x_vel = 0, main_ship.y_vel = 0;
        update_position( up, down, left, right,  &main_ship);

        Uint32 current_time = SDL_GetTicks();

        if (current_time > last_projectile_time + 1000) {
            fire_projectile(proj, &main_ship);
            last_projectile_time = current_time; 
        }
        if (current_time > last_enemy_spawn_time + 2000) { 
            spawn_enemy(enemies);
            last_enemy_spawn_time = current_time;
        }
        
        
        

        update_projectiles(proj);
        update_enemies(enemies);
        check_projectile_enemy_collision( proj, enemies);

        SDL_SetRenderDrawColor(rend, 0, 0, 0, 255);  
        SDL_RenderClear(rend);

        
        render_enemies(rend, enemies);
        render(rend,&main_ship, 0);
        render_projectiles(rend, proj);

        SDL_RenderPresent(rend);

        SDL_Delay(1000 / 60);
    }

    cleanup(tex, rend, window);
    return 0;
}