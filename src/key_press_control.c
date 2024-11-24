#include "../Headers/TRODO.h"
#include "../Headers/structs.h"
#include <SDL2/SDL.h>

enum e_map_state {
    MAP_OFF = 0,
    MAP_ON = 1
};

static void handle_movement_keys(SDL_KeyboardEvent *key)
{
    if (key->keysym.sym == SDLK_w || key->keysym.sym == SDLK_UP)
        data.keys[key->keysym.sym] = 1;
    if (key->keysym.sym == SDLK_s || key->keysym.sym == SDLK_DOWN)
        data.keys[key->keysym.sym] = 1;
    if (key->keysym.sym == SDLK_a || key->keysym.sym == SDLK_LEFT)
        data.keys[key->keysym.sym] = 1;
    if (key->keysym.sym == SDLK_d || key->keysym.sym == SDLK_RIGHT)
        data.keys[key->keysym.sym] = 1;
}

void key_press_control(SDL_KeyboardEvent *key)
{
    // Consolidated control key handling
    switch (data.mode) {
        case INTRO:
            if (key->keysym.sym == SDLK_ESCAPE)
                break;
            if (!data.mouse.clicked)
                data.mouse.clicked = 1;
            data.mouse.on_click = 1;
            break;
        case INTRO1:
            // Similar to INTRO or add specific handling
            if (key->keysym.sym == SDLK_ESCAPE)
                break;
            break;
        case INTRO2:
            // Similar to INTRO or add specific handling
            if (key->keysym.sym == SDLK_ESCAPE)
                break;
            break;
        case SETTING:
            if (key->keysym.sym == SDLK_ESCAPE) {
                data.mode = INTRO;
                break;
            }
            if (key->keysym.sym == SDLK_RETURN) {
                if (data.mouse.on_clk[0])
                    data.mode = GAME;
                else if (data.mouse.on_clk[1])
                    data.mode = S_CONTROL;
                else if (data.mouse.on_clk[2]) {
                    SDL_RenderClear(data.sdl.renderer);
                    exit(0);
                }
            }
            break;
        case SETTING2:
            if (key->keysym.sym == SDLK_RETURN && data.mouse.on_clk[3]) {
                data.mode = GAME;
            }
            if (key->keysym.sym == SDLK_ESCAPE)
                data.mode = GAME;
            break;
        case S_CONTROL:
            if (key->keysym.sym == SDLK_ESCAPE)
                data.mode = SETTING;
            break;
        case GAME:
            handle_movement_keys(key);
            if (key->keysym.sym == SDLK_ESCAPE) {
                data.mode = SETTING2;
                SDL_ShowCursor(SDL_ENABLE);
            }
            if (key->keysym.sym == SDLK_m) {
                data.intro.map = (data.intro.map == MAP_OFF) ? MAP_ON : MAP_OFF;
                SDL_ShowCursor(data.intro.map == MAP_ON ? SDL_ENABLE : SDL_DISABLE);
            }
            if (key->keysym.sym == SDLK_e)
                data.door.is_op = 1;
            if (key->keysym.sym == SDLK_SPACE) {
                if (data.use_gun && !data.gun[data.indx].f_shoot)
                    data.gun[data.indx].f_shoot = 1;
            }
            break;
        case G_EXIT_MODE:
            // Potential exit handling, currently similar to a no-op
            if (key->keysym.sym == SDLK_ESCAPE)
                exit(0);
            break;
        case MAP_MODE:
            // Similar to GAME mode map handling
            if (key->keysym.sym == SDLK_m) {
                data.intro.map = (data.intro.map == MAP_OFF) ? MAP_ON : MAP_OFF;
                SDL_ShowCursor(data.intro.map == MAP_ON ? SDL_ENABLE : SDL_DISABLE);
            }
            if (key->keysym.sym == SDLK_ESCAPE)
                data.mode = GAME;
            break;
        case ANIMATE_SETT2_IN_MODE:
        case ANIMATE_SETT2_OUT_MODE:
            // Potential animation transition modes
            // Currently no specific handling
            break;
        default:
            // Catch-all for any unhandled modes
            break;
    }
}

int key_press(SDL_KeyboardEvent *key, void *d)
{
    (void)d;
    key_press_control(key);
    return 0;
}
