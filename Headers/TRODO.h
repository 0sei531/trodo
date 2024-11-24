#ifndef TRODO_H
#define TRODO_H
/* System Headers */
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <time.h>
#include <pthread.h>
#include <math.h>
#include <semaphore.h>
#include <x86intrin.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdbool.h>
#include <stddef.h>
/* Local Headers */
#include "defines.h"
#include "structs.h"
/* Global Variables */
extern t_data data;
/* Utility Functions */
bool ftisdigit(int c);
size_t ft_strlen(const char *str);
char *ft_strjoin(char *s1, char *s2);
char **ft_split(char const *s, char c);
void *ft_memcpy(void *dst, const void *src, size_t n);
int ft_atoi(const char *str);
int ft_strncmp(const char *s1, const char *s2, size_t n);
ssize_t ft_putstr_fd(const char *str, int fd);
char *ft_substr(char const *s, size_t start, size_t len);
char *ft_str_trim(char const *s1, char const *set);
char *ft_strchr(const char *s, int c);
void error(const char *message, int exit_code);
char *ft_strnstr(const char *haystack, const char *needle, size_t len);
int spaces(char *str);
void set_char_to_win(void);
char *get_next_line(int fd);
/* Linked List Functions */
t_map *ft_lst_new(void *content);
void ft_lst_add_front(t_map **lst, t_map *new);
void ft_lst_add_back(t_map **lst, t_map *new);
void ft_lst_clear(t_map **lst, void (*del)(void *));
t_map *ft_lst_last(t_map *lst);
void ft_lst_del_one(t_map *lst, void (*del)(void *));
/* Game Initialization and Management */
int init_game(SDL_Window *window, SDL_Renderer *renderer, t_map *map);
void init_args(t_map **map);
void free_map_struct(t_map *map);
void cleanup_and_exit(SDL_Window *window, SDL_Renderer *renderer, t_map *map);
void game_loop(SDL_Window *window, SDL_Renderer *renderer, t_map *map);
int ft_close(void);
void cast_to_3d(int ray_index);
/* Movement and Game Logic */
void up(void);
void down(void);
void left(void);
void right(void);
void move(void);
/* Rendering Functions */
void render_game(t_data *data);
void set_rays(SDL_Renderer *renderer, t_map *map);
void cast_ray(SDL_Renderer *renderer, float angle, t_map *map);
void set_minimap(void);
/* Key and Mouse Event Handling */
int key_press(SDL_KeyboardEvent *key, void *d);
void handle_key_press(SDL_Event *event, t_data *data);
void handle_key_release(SDL_Event *event, t_data *data);
void mouse_press_intro(SDL_MouseButtonEvent *button);
void mouse_press_setting(SDL_MouseButtonEvent *button);
void mouse_press_setting2(SDL_MouseButtonEvent *button);
void mouse_press_control(SDL_MouseButtonEvent *button);
void set_volume(void);
void init_keys(void);
/* SDL Event Handling */
void handle_mouse_press(SDL_Event *event, t_data *data);
void handle_mouse_motion(SDL_Event *event, t_data *data);
void handle_mouse_release(SDL_Event *event, t_data *data);
/* Angle and Math Calculations */
void init_angles(void);
void calculate_fov(void);
void update_player_position(void);
/* Game State Management */
void init_intro(t_intro *intro);
void cleanup_intro(t_intro *intro);
void init_game_state(void);
void update_game_state(void);
void left_angle(void);
void right_angle(void);
void paint_color(SDL_Texture **texture, int color, int width, int height);
/* Parsing and Map Functions */
int parsing(char *file_name);
void validate_map(void);
void load_textures(void);
/* Resource Management */
void cleanup_resources(void);
void free_game_resources(void);
#endif /* TRODO_H */
