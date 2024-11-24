#include "../Headers/TRODO.h"

void handle_key_press(SDL_Event *event, t_data *data) {
    if (!event || !data) return;
    switch (event->key.keysym.sym) {
        case SDLK_w:
        case SDLK_UP:
            press_key(data, UP);
            break;
        case SDLK_s:
        case SDLK_DOWN:
            press_key(data, DOWN);
            break;
        case SDLK_a:
        case SDLK_LEFT:
            press_key(data, LEFT);
            break;
        case SDLK_d:
        case SDLK_RIGHT:
            press_key(data, RIGHT);
            break;
        case SDLK_ESCAPE:
            data->mode = G_EXIT_MODE;
            break;
        case SDLK_m:
            data->mode = MAP_MODE;
            break;
    }
}

void handle_key_release(SDL_Event *event, t_data *data) {
    if (!event || !data) return;
    switch (event->key.keysym.sym) {
        case SDLK_w:
        case SDLK_UP:
            release_key(data, UP);
            break;
        case SDLK_s:
        case SDLK_DOWN:
            release_key(data, DOWN);
            break;
        case SDLK_a:
        case SDLK_LEFT:
            release_key(data, LEFT);
            break;
        case SDLK_d:
        case SDLK_RIGHT:
            release_key(data, RIGHT);
            break;
    }
}

void move(void) {
    float moveSpeed = 0.05f;
    float rotSpeed = 0.03f;

    if (is_key_pressed(&data, UP)) {
        float newX = data.dir.x + data.dir.px * moveSpeed;
        float newY = data.dir.y + data.dir.py * moveSpeed;
        if (data.map[(int)data.dir.y][(int)newX] != '1')
            data.dir.x = newX;
        if (data.map[(int)newY][(int)data.dir.x] != '1')
            data.dir.y = newY;
    }

    if (is_key_pressed(&data, DOWN)) {
        float newX = data.dir.x - data.dir.px * moveSpeed;
        float newY = data.dir.y - data.dir.py * moveSpeed;
        if (data.map[(int)data.dir.y][(int)newX] != '1')
            data.dir.x = newX;
        if (data.map[(int)newY][(int)data.dir.x] != '1')
            data.dir.y = newY;
    }

    if (is_key_pressed(&data, LEFT)) {
        float oldDirX = data.dir.px;
        data.dir.px = data.dir.px * cos(-rotSpeed) - data.dir.py * sin(-rotSpeed);
        data.dir.py = oldDirX * sin(-rotSpeed) + data.dir.py * cos(-rotSpeed);
        float oldPlaneX = data.dir.x;
        data.dir.x = data.dir.x * cos(-rotSpeed) - data.dir.y * sin(-rotSpeed);
        data.dir.y = oldPlaneX * sin(-rotSpeed) + data.dir.y * cos(-rotSpeed);
    }

    if (is_key_pressed(&data, RIGHT)) {
        float oldDirX = data.dir.px;
        data.dir.px = data.dir.px * cos(rotSpeed) - data.dir.py * sin(rotSpeed);
        data.dir.py = oldDirX * sin(rotSpeed) + data.dir.py * cos(rotSpeed);
        float oldPlaneX = data.dir.x;
        data.dir.x = data.dir.x * cos(rotSpeed) - data.dir.y * sin(rotSpeed);
        data.dir.y = oldPlaneX * sin(rotSpeed) + data.dir.y * cos(rotSpeed);
    }
}
