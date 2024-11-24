#ifndef STRUCTS_H
#define STRUCTS_H

#include "defines.h"
#include <SDL2/SDL.h>
#include <stdbool.h>

// Constants
#define MAX_ENEMIES 50
#define MAX_BULLETS 100
#define MAX_ITEMS 20
#define MAX_MAP_WIDTH 100
#define MAX_MAP_HEIGHT 100
#define FOV_RAYS 360
#define MAX_KEYS 512
#define MAX_FRAMES 10
#define MAX_MOTION_TYPES 7

// New structures for 3D rendering
typedef struct s_wall_segment {
    int height;
    int top;
    int bottom;
    int tex_x;
    double shade;
} t_wall_segment;

typedef struct s_floor_segment {
    int tex_x;
    int tex_y;
    double distance;
} t_floor_segment;

typedef struct s_ceiling_segment {
    int tex_x;
    int tex_y;
    double distance;
} t_ceiling_segment;

// Button position structure
typedef struct s_button {
    int x;
    int y;
} t_button;

// Sound management structure
typedef struct s_sound {
    int click;
    int hit;
    int scroll;
    int hover;
    int breath;
} t_sound;

// Object properties structure
typedef struct s_objects {
    int health;
    int t1;
    int t2;
    int t3;
    int t4;
    float breath;
} t_objects;

// Field of view structure
typedef struct s_fov {
    int jumping;
} t_fov;

// Game mode enumeration
typedef enum {
    INTRO = 0,
    INTRO1 = 1,
    INTRO2 = 2,
    GAME = 3,
    SETTING = 4,
    SETTING2 = 5,
    S_CONTROL = 6,
    G_EXIT_MODE = 7,
    MAP_MODE = 8,
    ANIMATE_SETT2_IN_MODE = 10,
    ANIMATE_SETT2_OUT_MODE = 11
} t_game_mode;

// Direction and position structure
typedef struct s_dir {
    float x;
    float y;
    float px;
    float py;
    float angle;
    float s;
} t_dir;

// SDL context structure
typedef struct s_sdl {
    SDL_Window *window;
    SDL_Renderer *renderer;
} t_sdl;

// Image/texture structure
typedef struct s_img {
    SDL_Texture *texture;
    int width;
    int height;
    int x;
    int y;
} t_img;

// Motion structure
typedef struct s_motion {
    t_img *frm;  // Array of image frames
    int frame;   // Current frame count
} t_motion;

// Gun structure
typedef struct s_gun {
    int f_shoot;
    t_img *gun;   // Array of gun textures
    int frame;    // Number of frames
    int bullet;   // Bullet count
    int case_bullet;  // Case bullet count
    int f_reload;  // Reload flag
} t_gun;

// Mouse input structure
typedef struct s_mouse {
    int on;
    int x;
    int y;
    int clicked;
    int on_click;
    int on_clk[4];
    int hover;
    int on_hov[7];
    SDL_Texture *img;
    int sett2;
} t_mouse;

typedef struct s_keys {
    int up;
    int down;
    int left;
    int right;
} t_keys;

typedef struct s_player {
    float x;
    float y;
    float dirX;
    float dirY;
    float planeX;
    float planeY;
} t_player;

// Door management structure
typedef struct s_door {
    int is_op;
    int op;
    char **map;
    int hit_wall;
} t_door;

// Menu/Intro screen structure
typedef struct s_intro {
    int map;
    int volume;
    int up;
    int *g_k;
    int vol_click;
    int lgt_click;
    SDL_Texture *lt;
    t_button start;
    t_button sett;
    t_button exit;
    t_button cont;
    t_button restart;
    int on_clk[16];
    int on_hov[16];
    int light;
    SDL_Texture *vol[2];
    SDL_Texture *lgt[2];
} t_intro;

// Asset structure
typedef struct s_assets {
    SDL_Texture *texture;
} t_assets;

// Enemy position structure
typedef struct {
    int x;
    int y;
} t_enemy_pos;

// Map linked list structure
typedef struct s_map {
    char *content;
    struct s_map *next;
} t_map;

// Main game data structure
typedef struct s_data {
    char **map;
    t_player player;
    char **door_map;
    int *w_map;
    int h_map;
    int enm_nb;
    t_dir dir;
    t_enemy_pos enemy[MAX_ENEMIES];
    t_map *game_map;
    t_game_mode mode;
    t_sdl sdl;
    t_mouse mouse;
    t_door door;
    t_intro intro;
    t_sound sound;
    t_objects objects;
    int keys[MAX_KEYS];
    float speed;
    int use_gun;
    int indx;
    t_gun gun[MAX_BULLETS];
    t_motion *motion;
    float cord[2];
    int enemy_count;
    int bullet_count;
    int item_count;
    int c;
    struct {
        double r_cos[FOV_RAYS];
        double r_sin[FOV_RAYS];
        double r_res_cos[FOV_RAYS];
        double pl_cos;
        double pl_sin;
        double pl_cos_plus_90;
        double pl_sin_plus_90;
        double cte_tan;
    } angles;
    double rays[FOV_RAYS];
    int color[2];
    char *design;
    int light;
    double map_rotation;
    double map_zoom;
    t_assets assets;
    // New members for 3D rendering
    t_wall_segment walls[FOV_RAYS];
    t_floor_segment floors[FOV_RAYS][RES_Y/2];
    t_ceiling_segment ceilings[FOV_RAYS][RES_Y/2];
} t_data;

static inline bool is_key_pressed(const t_data *data, int key) {
    return data->keys[key] == 1;
}

static inline void press_key(t_data *data, int key) {
    data->keys[key] = 1;
}

static inline void release_key(t_data *data, int key) {
    data->keys[key] = 0;
}

// Enemy entity structure
typedef struct {
    int type;
    int x;
    int y;
    int health;
    int damage;
} t_enemy;

// Bullet/projectile structure
typedef struct {
    int x;
    int y;
    int speed;
    int damage;
    int direction;
} t_bullet;

// Item/pickup structure
typedef struct {
    int type;
    int x;
    int y;
    bool is_active;
    int value;
} t_item;

// Generic linked list structure
typedef struct s_list {
    void *content;
    struct s_list *next;
} t_list;

// Global data instance
extern t_data data;

#endif // STRUCTS_H
