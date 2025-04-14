#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include <SDL2/SDL.h>

#define PROJECTILE_SPEED 500
#define PROJECTILE_MAX 200
#define SPEED 400
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 640
#define ENEMY_MAX 20
#define ENEMY_SPEED 150

typedef struct {
    SDL_Rect rect;
    float x_pos;
    float y_pos;
    int x_vel;
    int y_vel;
    int damage;
    int ship_hp;
    int is_hit;
} ship;

typedef struct {
    SDL_Rect rect;
    float x_pos;
    float y_pos;
    int x_vel;
    int y_vel;
    int is_active;
    int damage;
} projectile;

typedef struct {
    SDL_Rect rect;
    float x_pos;
    float y_pos;
    int y_vel;
    int is_active;
    int hp;
    int is_hit;
} enemy;

void fire_projectile(projectile *projectiles, ship *main_ship);
void render_projectiles(SDL_Renderer *rend, projectile *projectiles);
void update_projectiles(projectile *projectiles);
void update_position( int up, int down, int left, int right,  ship *main_ship);
void spawn_enemy(enemy *enemies, int enemy_hp);
void update_enemies(enemy *enemies);
void render_enemies(SDL_Renderer *rend, enemy *enemies);
void check_projectile_enemy_collision(projectile *projectiles, enemy *enemies) ;
void check_enemy_ship_collision(ship *main_ship, enemy *enemies);


#endif