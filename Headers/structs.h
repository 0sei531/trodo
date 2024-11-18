#ifndef STRUCTS_H
# define STRUCTS_H

# include <SDL2/SDL.h>

/* Struct Definitions */
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

typedef struct s_p_objects
{
    int             health;
    int             breath;
    int             t1, t2, t3, t4;
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
    t_img           int1, int2, start, restart, cont, sett, exit;
    t_img           back, reset, gun, tr, tr2, up_logo, down_logo;
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
    int             mode;
    int             mv;
    int             g_mv;
    t_img           img_c, assets, guns, cross, health_enm, lose;
    int             show_health;
    int             keys[1000];
    int             height, width, c, speed;
    double          rays[1500];
    int             color[2];
    char            **map;
    int             *w_map;
    int             h_map;
    int             death;
    t_sdl           sdl;
    t_rgb           floor, ceil;
    t_dir           dir;
    t_img           img, img2, img3, blood_hit, blood_hit2;
    t_p_objects     objects;
    t_mouse         mouse;
    t_fov           fov;
    t_intro         intro;
    t_angle         angles;
    t_gun           gun[27];
    SDL_Texture     *sl;
    t_img           nums[10];
    int             use_gun, aim, zoom;
    double          map_zoom;
    int             map_rotation, mv_x, mv_y, c_x, c_y;
    t_enm           enemy[100];
    int             enm_nb;
}   t_data;

#endif // STRUCTS_H
