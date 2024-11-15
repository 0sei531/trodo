#ifndef STRUCTS_H
#define STRUCTS_H

/*************************************************************************/
/*========                         SDL                           ========*/
/*************************************************************************/
typedef struct s_sdl
{
    void            *window;    // SDL Window
    void            *renderer;  // SDL Renderer
    void            *texture;   // SDL Texture
}   t_sdl;

/*************************************************************************/
/*========                     Direction                        ========*/
/*************************************************************************/
typedef struct s_dir
{
    double          pos_x;      // Player X position
    double          pos_y;      // Player Y position
    double          dir_x;      // X component of direction vector
    double          dir_y;      // Y component of direction vector
    double          plane_x;    // X component of the camera plane
    double          plane_y;    // Y component of the camera plane
}   t_dir;

/*************************************************************************/
/*========                 Player Objects                       ========*/
/*************************************************************************/
typedef struct s_p_objects
{
    int             weapon;     // Current weapon index
    int             health;     // Player health points
    int             ammo;       // Ammunition count
}   t_p_objects;

/*************************************************************************/
/*========                       Mouse                         ========*/
/*************************************************************************/
typedef struct s_mouse
{
    int             x;          // Mouse X position
    int             y;          // Mouse Y position
    int             left;       // Left button state
    int             right;      // Right button state
}   t_mouse;

/*************************************************************************/
/*========                        FOV                           ========*/
/*************************************************************************/
typedef struct s_fov
{
    double          fov_angle;  // Field of view angle in degrees
    double          distance;   // Distance to the projection plane
}   t_fov;

/*************************************************************************/
/*========                       Intro                          ========*/
/*************************************************************************/
typedef struct s_intro
{
    int             active;     // Is the intro screen active
    t_img           background; // Intro background image
}   t_intro;

/*************************************************************************/
/*========                       Sound                          ========*/
/*************************************************************************/
typedef struct s_sound
{
    void            *music;     // Background music
    void            *effects;   // Sound effects
}   t_sound;

/*************************************************************************/
/*========                        Door                          ========*/
/*************************************************************************/
typedef struct s_door
{
    int             is_open;    // Door open state
    double          pos_x;      // Door X position
    double          pos_y;      // Door Y position
}   t_door;

/*************************************************************************/
/*========                  Enemy Motion                       ========*/
/*************************************************************************/
typedef struct s_enemies_motion
{
    int             count;      // Number of enemies
    double          *positions; // Array of enemy positions
}   t_enemies_motion;

/*************************************************************************/
/*========                        Angles                        ========*/
/*************************************************************************/
typedef struct s_angle
{
    double          r_cos[1501];         // Precomputed cos values
    double          r_sin[1501];         // Precomputed sin values
    double          r_res_cos[1501];    // Precomputed residual cos
    double          cte_tan;            // Constant tangent
    double          pl_cos;             // Player plane cosine
    double          pl_sin;             // Player plane sine
    double          pl_cos_plus_90;     // Plane cosine at +90 degrees
    double          pl_sin_plus_90;     // Plane sine at +90 degrees
}   t_angle;

/*************************************************************************/
/*========                        Objects                        ========*/
/*************************************************************************/
typedef struct s_object
{
    int             active;     // Is the object active in the scene
    int             type;       // Object type
    double          pos_x;      // X position in the game world
    double          pos_y;      // Y position in the game world
    t_img           sprite;     // Object sprite
}   t_object;

/*************************************************************************/
/*========                       Game Data                      ========*/
/*************************************************************************/
typedef struct s_game
{
    t_sdl           sdl;        // SDL context for rendering
    t_dir           dir;        // Player position and direction
    t_p_objects     p_objects;  // Player's objects (weapons, health, etc.)
    t_mouse         mouse;      // Mouse state
    t_fov           fov;        // Camera field of view
    t_intro         intro;      // Intro screen assets
    t_sound         sound;      // Sound assets and states
    t_door          door;       // Door properties
    t_enemies_motion enemies_motion; // Enemy motion animations
    t_angle         angles;     // Pre-calculated angle values for rendering
    t_object        objects[100]; // Array of game objects (enemies, items, etc.)
    int             game_mode;  // Current game mode
    char            **map;      // Game map layout
    int             map_width;  // Width of the map
    int             map_height; // Height of the map
    int             score;      // Player's score
    int             level;      // Current game level
}   t_game;

#endif
