#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include <SDL2/SDL.h>
#include <math.h>


#define PROJECTILE_SPEED 1000
#define PROJECTILE_MAX 200
#define SPEED 600
#define ENEMY_MAX 30
#define ENEMY_SPEED 150
#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 800
#define POWERUP_MAX 10
#define ENEMY_SIZE 40
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) > (b) ? (b) : (a))
#define POWERUP_TYPE_COUNT 7

typedef enum{
    Shield,
    RapidFire,
    SpeedBoost,
    DoubleDamage,
    SlowTime,
    DoublePoints,
    DoubleProjectiles
}powerup_type;

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
    int has_shield;
    int rapid_fire;
    int double_points;
    int slow_time;
    int double_projectiles;
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

typedef struct {
    powerup_type type;
    Uint32 duration;
    Uint32 start_time;
    int is_active;
    int is_up;
    float x_pos;
    float y_pos;
    SDL_Rect rect;
    int y_vel;
} powerup;

void fire_projectile(projectile *projectiles, ship *main_ship, int projectile_type);
void render_projectiles(SDL_Renderer *rend, projectile *projectiles);
void update_projectiles(projectile *projectiles, float dt);


void update_position( int up, int down, int left, int right,  ship *main_ship);


void spawn_enemy(enemy *enemies, int enemy_hp);
void update_enemies(enemy *enemies, ship *main_ship);
void render_enemies(SDL_Renderer *rend, enemy *enemies);
void check_projectile_enemy_collision(projectile *projectiles, enemy *enemies, unsigned int *score, unsigned int *exp, powerup *powerups, ship *main_ship);
void handle_enemy_death(enemy *enemies, powerup *powerups);


void check_enemy_ship_collision(ship *main_ship, enemy *enemies);
unsigned int calculate_exp_for_next_level(unsigned int level);
int if_lvl_up(ship *main_ship, unsigned int *exp);
void main_ship_lvl_up(ship *main_ship);


void update_boss(boss *boss_enemy);
void render_boss(SDL_Renderer *rend, boss *boss_enemy);
void check_boss_ship_collision(ship *main_ship, boss *boss_enemy);
void check_boss_projectile_collision(projectile *projectiles, boss *boss_enemy, unsigned int *score, unsigned int *experience);


void slow_time_power_up(ship *main_ship);
void double_points_power_up(ship *main_ship);
void double_projectiles_power_up(ship *main_ship);
void power_up_effect(ship *main_ship, powerup *powerups);
void power_end_effect(ship *main_ship, powerup *powerups);


#endif