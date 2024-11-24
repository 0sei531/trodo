#include "../Headers/structs.h"
#include "../Headers/defines.h"
#include <SDL2/SDL.h>

// Function prototype declarations
static int is_point_in_rect(int x, int y, SDL_Rect *rect);

void handle_game_mouse_press(SDL_MouseButtonEvent *button, t_data *data) {
    if (button->button == SDL_BUTTON_LEFT) {
        data->gun[data->indx].f_shoot = 1;
        data->mouse.on_click = M_LEFT_CLICK;
    }
    else if (button->button == SDL_BUTTON_RIGHT) {
        data->use_gun = 1;
        data->mouse.on_click = M_RIGHT_CLICK;
    }
}

void handle_map_mouse_press(SDL_MouseButtonEvent *button, t_data *data) {
    float map_x = ((float)button->x * (*data->w_map)) / X;
    float map_y = ((float)button->y * data->h_map) / Y;
    
    if (button->button == SDL_BUTTON_LEFT) {
        data->cord[0] = map_x;
        data->cord[1] = map_y;
        data->mouse.clicked = 1;
    }
}

void handle_exit_mouse_press(SDL_MouseButtonEvent *button, t_data *data) {
    SDL_Rect resume_btn = {RES_X / 4, RES_Y / 2 - 50, RES_X / 2, 40};
    SDL_Rect exit_btn = {RES_X / 4, RES_Y / 2 + 50, RES_X / 2, 40};
    
    if (is_point_in_rect(button->x, button->y, &resume_btn)) {
        data->mode = GAME;
        if (data->sound.click) {
            // Play click sound if implemented
        }
    }
    else if (is_point_in_rect(button->x, button->y, &exit_btn)) {
        data->mode = G_EXIT_MODE;
        if (data->sound.click) {
            // Play click sound if implemented
        }
    }
}

void handle_intro1_mouse_press(SDL_MouseButtonEvent *button, t_data *data) {
    SDL_Rect next_btn = {RES_X - 150, RES_Y - 80, 100, 40};
    
    if (button->button == SDL_BUTTON_LEFT && 
        is_point_in_rect(button->x, button->y, &next_btn)) {
        data->mode = INTRO2;
        if (data->sound.click) {
            // Play click sound if implemented
        }
    }
}

void handle_intro2_mouse_press(SDL_MouseButtonEvent *button, t_data *data) {
    SDL_Rect start_btn = {
        data->intro.start.x,
        data->intro.start.y,
        100,  // Adjust these dimensions as needed
        40
    };
    
    if (button->button == SDL_BUTTON_LEFT && 
        is_point_in_rect(button->x, button->y, &start_btn)) {
        data->mode = GAME;
        if (data->sound.click) {
            // Play click sound if implemented
        }
    }
}

static int is_point_in_rect(int x, int y, SDL_Rect *rect) {
    return (x >= rect->x && x <= rect->x + rect->w &&
            y >= rect->y && y <= rect->y + rect->h);
}

void handle_mouse_release(SDL_MouseButtonEvent *button, t_data *data) {
    if (button->button == SDL_BUTTON_LEFT) {
        data->gun[data->indx].f_shoot = 0;
        data->mouse.on_click = 0;
    }
    else if (button->button == SDL_BUTTON_RIGHT) {
        data->use_gun = 0;
        data->mouse.on_click = 0;
    }
    data->mouse.clicked = 0;
}
