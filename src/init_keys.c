#include "../Headers/TRODO.h"

void init_keys(void) {
    data.key.up = 0;
    data.key.down = 0;
    data.key.left = 0;
    data.key.right = 0;
    data.key.rotate_left = 0;
    data.key.rotate_right = 0;
    data.key.esc = 0;
    data.key.shift = 0;
    data.key.space = 0;
}

void init_args(t_map **map) {
    if (!map || !*map)
        error("Error: Invalid map pointer\n", 1);

    (*map)->next = NULL;
    (*map)->prev = NULL;
    data.h_map = 0;
    data.w_map = NULL;
    data.map = NULL;
    data.door.map = NULL;
}

void set_char_to_win(void) {
    data.win.intro = 0;
    data.win.game = 0;
    data.win.control = 0;
    data.win.setting = 0;
    data.win.map = 0;
}

#include "../Headers/TRODO.h"

void handle_key_press(SDL_Event *event, t_data *data) {
    switch (event->key.keysym.sym) {
        case SDLK_w: data->key.up = 1; break;
        case SDLK_s: data->key.down = 1; break;
        case SDLK_a: data->key.left = 1; break;
        case SDLK_d: data->key.right = 1; break;
        case SDLK_LEFT: data->key.rotate_left = 1; break;
        case SDLK_RIGHT: data->key.rotate_right = 1; break;
        case SDLK_ESCAPE: data->key.esc = 1; break;
        case SDLK_LSHIFT: data->key.shift = 1; break;
        case SDLK_SPACE: data->key.space = 1; break;
    }
}

void handle_key_release(SDL_Event *event, t_data *data) {
    switch (event->key.keysym.sym) {
        case SDLK_w: data->key.up = 0; break;
        case SDLK_s: data->key.down = 0; break;
        case SDLK_a: data->key.left = 0; break;
        case SDLK_d: data->key.right = 0; break;
        case SDLK_LEFT: data->key.rotate_left = 0; break;
        case SDLK_RIGHT: data->key.rotate_right = 0; break;
        case SDLK_ESCAPE: data->key.esc = 0; break;
        case SDLK_LSHIFT: data->key.shift = 0; break;
        case SDLK_SPACE: data->key.space = 0; break;
    }
}

void handle_mouse_press(SDL_Event *event, t_data *data) {
    if (event->button.button == SDL_BUTTON_LEFT) {
        data->mouse.left = 1;
    }
}

void handle_mouse_release(SDL_Event *event, t_data *data) {
    if (event->button.button == SDL_BUTTON_LEFT) {
        data->mouse.left = 0;
    }
}

