#include <SDL2/SDL.h>
#include "../Headers/structs.h"
#include "../Headers/TRODO.h"

void mouse_release_intro(SDL_Event *event)
{
    if (event->button.button == SDL_BUTTON_LEFT && !data.mouse.clicked)
        data.mouse.clicked = 1;
    if (event->button.button == SDL_BUTTON_LEFT)
        data.mouse.on_click = 0;
        // data.mode = SETTING;
}

void set_vol_lgt_as_def(t_img *img2, int *v, int val)
{
    *v = val;
    if (*v > 200)
        *v = 200;
    if (*v < 0)
        *v = 0;
    paint_color(img2, 0xB2BEB5, 200, 10);
    paint_color(img2, 0xff0000, *v, 10);
    set_volume();
    paint_color(&data.intro.lt, ((55 + data.intro.light) << 24), RES_X, RES_Y);
}

void mouse_release_setting(SDL_Event *event, int x, int y)
{
    if (event->button.button == SDL_BUTTON_LEFT)
    {
        if (data.mode == SETTING)
        {
            if (data.mouse.on_clk[0] && x >= (RES_X - data.intro.start.x) / 2 && y >= (RES_Y - data.intro.start.y) / 2 - RES_Y / 6 && x < (RES_X + data.intro.start.x) / 2 && y < (RES_Y + data.intro.start.y) / 2 - RES_Y / 6)
                data.sound.click = 1,
                data.mode = GAME;
            if (data.mouse.on_clk[1] && x >= (RES_X - data.intro.sett.x) / 2 && y >= (RES_Y - data.intro.sett.y) / 2 - RES_Y / 12 && x < (RES_X + data.intro.sett.x) / 2 && y < (RES_Y + data.intro.sett.y) / 2 - RES_Y / 12)
                data.sound.click = 1,
                data.mode = S_CONTROL;
            if (data.mouse.on_clk[2] && x >= (RES_X - data.intro.exit.x) / 2 && y >= (RES_Y - data.intro.exit.y) / 2 && x < (RES_X + data.intro.exit.x) / 2 && y < (RES_Y + data.intro.exit.y) / 2)
                data.sound.click = 1,
                exit (0);
        }
        if (data.mode == SETTING2)
        {
            if (data.mouse.on_clk[3] && x >= (RES_X - data.intro.cont.x) / 2 && y >= (RES_Y - data.intro.cont.y) / 2 - RES_Y / 6 && x < (RES_X + data.intro.cont.x) / 2 && y < (RES_Y + data.intro.cont.y) / 2 - RES_Y / 6)
                data.sound.click = 1,
                data.mode = GAME;
            if (data.mouse.on_clk[4] && x >= (RES_X - data.intro.restart.x) / 2 && y >= (RES_Y - data.intro.restart.y) / 2 - RES_Y / 12 && x < (RES_X + data.intro.restart.x) / 2 && y < (RES_Y + data.intro.restart.y) / 2 - RES_Y / 12)
                data.sound.click = 1,
                data.mode = GAME;
            if (data.mouse.on_clk[1] && x >= (RES_X - data.intro.sett.x) / 2 && y >= (RES_Y - data.intro.sett.y) / 2 && x < (RES_X + data.intro.sett.x) / 2 && y < (RES_Y + data.intro.sett.y) / 2)
                data.sound.click = 1,
                data.mode = S_CONTROL;
            if (data.mouse.on_clk[2] && x >= (RES_X - data.intro.exit.x) / 2 && y >= (RES_Y - data.intro.exit.y) / 2 + RES_Y / 12 && x < (RES_X + data.intro.exit.x) / 2 && y < (RES_Y + data.intro.exit.y) / 2 + RES_Y / 12)
                data.sound.click = 1,
                exit (0);
        }
        if (data.mode == S_CONTROL)
        {
            if (data.mouse.on_clk[5] && x >= RES_X / 2 - 225 && y >= RES_Y - 100 && x < RES_X / 2 - 75 && y < RES_Y - 40)
            {
                data.sound.click = 1;
                data.mode = SETTING * !data.mouse.sett2 + SETTING2 * data.mouse.sett2;
            }
            if (data.mouse.on_clk[6] && x >= RES_X / 2 + 75 && y >= RES_Y - 100 && x < RES_X / 2 + 225 && y < RES_Y - 40)
            {
                data.sound.click = 1;
                init_keys();
                set_vol_lgt_as_def(&data.intro.vol[0], &data.intro.volume, 100);
                set_vol_lgt_as_def(&data.intro.lgt[0], &data.intro.light, 200);
            }
        }
        data.mouse.on_clk[0] = 0;
        data.mouse.on_clk[1] = 0;
        data.mouse.on_clk[2] = 0;
        data.mouse.on_clk[3] = 0;
        data.mouse.on_clk[4] = 0;
        data.mouse.on_clk[5] = 0;
        data.mouse.on_clk[6] = 0;
    }
}

void mouse_release_control(SDL_Event *event, int x, int y)
{
    if (event->button.button == SDL_BUTTON_LEFT)
    {
        paint_color(&data.intro.vol[1], 0xffffff, 25, 40);
        paint_color(&data.intro.lgt[1], 0xffffff, 25, 40);
        data.intro.vol_click = 0;
        data.intro.lgt_click = 0;
    }
    mouse_release_setting(event, x, y);
}

void mouse_release_game(SDL_Event *event)
{
    if (data.intro.g_k[7] == M_LEFT_CLICK && event->button.button == SDL_BUTTON_LEFT)
        data.keys[data.intro.g_k[7]] = 0;
    if (data.intro.g_k[8] == M_RIGHT_CLICK && event->button.button == SDL_BUTTON_RIGHT)
        data.keys[data.intro.g_k[8]] = 0;
}

void mouse_release_map(SDL_Event *event)
{
    if (data.intro.g_k[7] == M_LEFT_CLICK && event->button.button == SDL_BUTTON_LEFT)
        data.keys[data.intro.g_k[7]] = 0;
    if (data.intro.g_k[8] == M_RIGHT_CLICK && event->button.button == SDL_BUTTON_RIGHT)
        data.keys[data.intro.g_k[8]] = 0;
}

int mouse_release(SDL_Event *event, void *w)
{
    w = NULL;
    int x, y;
    SDL_GetMouseState(&x, &y);

    if (data.mode == INTRO)
        mouse_release_intro(event);
    else if (data.mode == SETTING || data.mode == SETTING2)
        mouse_release_setting(event, x, y);
    else if (data.mode == S_CONTROL)
        mouse_release_control(event, x, y);
    else if (data.mode == G_MAP)
        mouse_release_map(event);
    else if (data.mode == GAME)
        mouse_release_game(event);

    return (0);
}
