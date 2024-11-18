#ifndef STRUCTS_H
# define STRUCTS_H

# include <SDL2/SDL.h>
# include <SDL2/SDL_mixer.h>

/* Base Structures */
typedef struct s_map
{
    char            *content;
    struct s_map    *next;
}   t_map;

typedef struct s_rgb
{
    int             r;
    int             g;
    int             b;
}   t_rgb;

typedef struct s_img
{
    SDL_Texture     *texture;
    int             x;
    int             y;
    int             width;
    int             height;
}   t_img;

typedef struct s_dir
{
    double          ph;
    int             px;
    int             py;
    int             s;
    int             x;
    int             y;
    double          angle;
}   t_dir;

typedef struct s_sdl
{
    SDL_Window      *window;
    SDL_Renderer    *renderer;
    t_img           floor;
    t_img           space;
    t_img           wall;
    t_img           player;
    t_img           cadre1;
    t_img           cadre2;
}   t_sdl;

typedef struct s_sound
{
    Mix_Chunk       *hit_sound;
    Mix_Chunk       *scroll_sound;
    Mix_Chunk       *breath_sound;
    int             hit;
    int             scroll;
    int             breath;
    int             hover;
    int             click;
}   t_sound;

typedef struct s_door
{
    char            **map;
    int             hit_wall;
    int             cord[2];
    int             color[2];
    double          rays[1500];
    int             is_op;
    int             op;
}   t_door;

typedef struct s_p_objects
{
    int             health;
    int             breath;
    int             t1;
    int             t2;
    int             t3;
    int             t4;
    int             w;
    t_img           time[10];
}   t_p_objects;

typedef struct s_mouse
{
    int             hover;
    int             on_click;
    int             clicked;
    int             show;
    int             x;
    int             y;
    double          on;
    SDL_Texture     *img;
    int             on_clk[7];
    int             on_hov[7];
    int             sett2;
}   t_mouse;

typedef struct s_fov
{
    int             jumping;
    int             crouching;
}   t_fov;

typedef struct s_intro
{
    int             fov;
    int             map;
    int             up;
    t_img           int1;
    t_img           int2;
    t_img           start;
    t_img           restart;
    t_img           cont;
    t_img           sett;
    t_img           exit;
    t_img           back;
    t_img           reset;
    t_img           gun;
    t_img           tr;
    t_img           tr2;
    t_img           up_logo;
    t_img           down_logo;
    t_img           guide[16];
    SDL_Texture     *keys[1000];
    int             g_k[12];
    int             on_hov[17];
    int             on_clk[17];
    int             volume;
    t_img           vol_icon[3];
    t_img           vol[2];
    int             vol_click;
    int             light;
    t_img           light_icon[2];
    t_img           lgt[2];
    t_img           lt;
    int             lgt_click;
    int             animate_sett;
}   t_intro;

typedef struct s_angle
{
    double          r_cos[1501];
    double          r_sin[1501];
    double          r_res_cos[1501];
    double          cte_tan;
    double          pl_cos;
    double          pl_sin;
    double          pl_cos_plus_90;
    double          pl_sin_plus_90;
}   t_angle;

typedef struct s_gun
{
    int             f_shoot;
    int             f_reload;
    int             frame;
    int             case_bullet;
    int             bullet;
    t_img           gun[90];
}   t_gun;

typedef struct s_enm
{
    int             hit;
    int             health;
    double          width;
    double          dist;
    int             motion;
    int             old_motion;
    int             frm;
    int             id;
    int             x;
    int             y;
}   t_enm;

typedef struct s_data
{
    /* Game State */
    int             mode;
    int             mv;
    int             g_mv;
    int             death;
    int             indx;
    int             light;
    
    /* Display Properties */
    int             height;
    int             width;
    int             c;
    int             speed;
    
    /* Assets and Images */
    t_img           img_c;
    t_img           assets;
    t_img           guns;
    t_img           cross;
    t_img           health_enm;
    t_img           lose;
    t_img           img;
    t_img           img2;
    t_img           img3;
    t_img           blood_hit;
    t_img           blood_hit2;
    t_img           nums[10];
    SDL_Texture     *sl;
    
    /* Map and Navigation */
    double          rays[1500];
    int             color[2];
    char            **map;
    int             *w_map;
    int             h_map;
    double          *cord;
    char            *design;
    double          map_zoom;
    int             map_rotation;
    int             mv_x;
    int             mv_y;
    int             c_x;
    int             c_y;
    
    /* Game Features */
    int             show_health;
    int             keys[1000];
    int             use_gun;
    int             aim;
    int             zoom;
    
    /* Component Structures */
    t_sdl           sdl;
    t_rgb           floor;
    t_rgb           ceil;
    t_dir           dir;
    t_door          door;
    t_sound         sound;
    t_p_objects     objects;
    t_mouse         mouse;
    t_fov           fov;
    t_intro         intro;
    t_angle         angles;
    t_gun           gun[27];
    t_enm           enemy[100];
    int             enm_nb;
}   t_data;

/* Global Variable */
extern t_data data;

#endif // STRUCTS_H
