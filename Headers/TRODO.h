#ifndef TRODO_H
# define TRODO_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <time.h>
# include <pthread.h>
# include <math.h>
# include <semaphore.h>
# include <x86intrin.h>
# include <SDL2/SDL.h>

# include "defines.h"
# include "structs.h"

t_data data;

/* Utility Functions */
int     ft_strncmp(const char *s1, const char *s2, size_t n);
int     ft_strlen(const char *str);
int     ft_strlen2(char **str);
char	*ft_strjoin(char *s1, char *s2);
char	**ft_split(char const *s, char c);
void	*ft_memcpy(void *dst, const void *src, size_t n);
char	*ft_substr(char const *s, int start, int len);
char	*ft_strchr(const char *str, int c);
char    *get_next_line(int fd);
int	    ft_isdigit(int c);
int	    ft_atoi(const char *str);
void    init_args(t_map **map);
void	error(char *str, int m);
int		ft_close(void);

/* Linked List Functions */
t_map	*ft_lst_last(t_map *lst);
void	ft_lst_del_one(t_map *lst, void (*del)(void*));
void	ft_lst_clear(t_map **lst, void (*del)(void*));
void	ft_lst_add_back(t_map **lst, t_map *new);
void	ft_lst_add_front(t_map **lst, t_map *new);
t_map	*ft_lst_new(void *content);

/* Parsing and Map Setup */
void    parsing(t_map *map);
int     ft_str_isdigit(char *s);
int     ft_lst_size(t_map *lst);
char	*ft_str_trim(char const *s1, char const *set);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
void    replace_tab(char *s);
void    check_map();
int     check_all_spaces(char *s);
void    set_minimap();
void    set_char_to_win();

/* Movement and Rotation Functions */
void    up();
void    down();
void    left_angle();
void    right_angle();
void    left();
void    right();

/* Event Handling with SDL */
void    handle_key_press(SDL_Event *event, t_data *data);
void    handle_key_release(SDL_Event *event, t_data *data);
void    handle_mouse_press(SDL_Event *event, t_data *data);
void    handle_mouse_motion(SDL_Event *event, t_data *data);
void    handle_mouse_release(SDL_Event *event, t_data *data);

/* Rendering and Game Mechanics */
void    set_rays();
void    cast_to_3d(int i);
void    render_pixel(SDL_Renderer *renderer, int x, int y, int color);
void    before();
void    render_game(t_data *data);
void    paint_texture(t_img *img, int color, int x_s, int y_s);
void    paint_img(t_img *img, const char *path, int res_x, int res_y);
int     get_img_color(t_img *img, int x, int y);

/* Sound, Timing, and Miscellaneous */
void    *time_count(void *d);
void    *check_sound(void *d);
void    set_volume();
void    init_keys();
void    map_appending();
int     set_design(int side, double x, double y, char design);
void    init_angles();
char	*ft_itoa(int n);
void    init_guns();
void    init_motion();
void	paint_hit_blood();

#endif
