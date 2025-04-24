#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include <SDL2/SDL.h>
#include <math.h>


#define PROJECTILE_SPEED 1000
#define PROJECTILE_MAX 200
#define SPEED 600
#define ENEMY_MAX 20
#define ENEMY_SPEED 150
#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 800

typedef struct {
    SDL_Rect rect;
    float x_pos;
    float y_pos;
    int x_vel;
    int y_vel;
    int damage;
    int ship_hp;
    int max_hp;
    int is_hit;
    int atk_speed;
    int armor;
    int level;
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
    int score;
} enemy;

typedef struct {
    SDL_Rect rect;
    float x_pos;
    float y_pos;
    int x_vel;
    int is_active;
    int hp;
    int dmg;
} boss;

void fire_projectile(projectile *projectiles, ship *main_ship);
void render_projectiles(SDL_Renderer *rend, projectile *projectiles);
void update_projectiles(projectile *projectiles);


void update_position( int up, int down, int left, int right,  ship *main_ship);


void spawn_enemy(enemy *enemies, int enemy_hp);
void update_enemies(enemy *enemies);
void render_enemies(SDL_Renderer *rend, enemy *enemies);
void check_projectile_enemy_collision(projectile *projectiles, enemy *enemies, unsigned int *score, unsigned int *experience); 


void check_enemy_ship_collision(ship *main_ship, enemy *enemies);
unsigned int calculate_exp_for_next_level(unsigned int level);
int if_lvl_up(ship *main_ship, unsigned int *exp);
void main_ship_lvl_up(ship *main_ship);


void update_boss(boss *boss_enemy);
void render_boss(SDL_Renderer *rend, boss *boss_enemy);
void check_boss_ship_collision(ship *main_ship, boss *boss_enemy);
void check_boss_projectile_collision(projectile *projectiles, boss *boss_enemy, unsigned int *score, unsigned int *experience);


#endif