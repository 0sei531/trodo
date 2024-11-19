#include <SDL2/SDL.h>
#include "../Headers/structs.h"
#include "../Headers/TRODO.h"

// Function to handle mouse press events for the intro mode
void mouse_press_intro(SDL_Event *event)
{
    if (event->button.button == SDL_BUTTON_LEFT)
        data.mouse.on_click = 1;
}

// Function to handle mouse press events for the settings
void mouse_press_setting(SDL_Event *event, int x, int y)
{
    if (event->button.button == SDL_BUTTON_LEFT)
    {
        if (data.mode == SETTING)
        {
            if (x >= (RES_X - data.intro.start.x) / 2 && y >= (RES_Y - data.intro.start.y) / 2 - RES_Y / 6 &&
                x < (RES_X + data.intro.start.x) / 2 && y < (RES_Y + data.intro.start.y) / 2 - RES_Y / 6)
                data.mouse.on_clk[0] = 1;
            if (x >= (RES_X - data.intro.sett.x) / 2 && y >= (RES_Y - data.intro.sett.y) / 2 - RES_Y / 12 &&
                x < (RES_X + data.intro.sett.x) / 2 && y < (RES_Y + data.intro.sett.y) / 2 - RES_Y / 12)
                data.mouse.on_clk[1] = 1;
            if (x >= (RES_X - data.intro.exit.x) / 2 && y >= (RES_Y - data.intro.exit.y) / 2 &&
                x < (RES_X + data.intro.exit.x) / 2 && y < (RES_Y + data.intro.exit.y) / 2)
                data.mouse.on_clk[2] = 1;
        }
        if (data.mode == SETTING2)
        {
            if (x >= (RES_X - data.intro.cont.x) / 2 && y >= (RES_Y - data.intro.cont.y) / 2 - RES_Y / 6 &&
                x < (RES_X + data.intro.cont.x) / 2 && y < (RES_Y + data.intro.cont.y) / 2 - RES_Y / 6)
                data.mouse.on_clk[3] = 1;
            if (x >= (RES_X - data.intro.restart.x) / 2 && y >= (RES_Y - data.intro.restart.y) / 2 - RES_Y / 12 &&
                x < (RES_X + data.intro.restart.x) / 2 && y < (RES_Y + data.intro.restart.y) / 2 - RES_Y / 12)
                data.mouse.on_clk[4] = 1;
            if (x >= (RES_X - data.intro.sett.x) / 2 && y >= (RES_Y - data.intro.sett.y) / 2 &&
                x < (RES_X + data.intro.sett.x) / 2 && y < (RES_Y + data.intro.sett.y) / 2)
                data.mouse.on_clk[1] = 1;
            if (x >= (RES_X - data.intro.exit.x) / 2 && y >= (RES_Y - data.intro.exit.y) / 2 + RES_Y / 12 &&
                x < (RES_X + data.intro.exit.x) / 2 && y < (RES_Y + data.intro.exit.y) / 2 + RES_Y / 12)
                data.mouse.on_clk[2] = 1;
        }
        if (data.mode == S_CONTROL)
        {
            if (x >= RES_X / 2 - 225 && y >= RES_Y - 100 && x < RES_X / 2 - 75 && y < RES_Y - 40)
                data.mouse.on_clk[5] = 1;
            if (x >= RES_X / 2 + 75 && y >= RES_Y - 100 && x < RES_X / 2 + 225 && y < RES_Y - 40)
                data.mouse.on_clk[6] = 1;
        }
    }
}

// Function to handle mouse press events in the control settings
void mouse_press_control(SDL_Event *event, int x, int y)
{
    int i;
    int inc_y;
    int pos = -1;

    if (event->button.button == SDL_BUTTON_LEFT)
    {
        i = -1;
        while (++i < 12)
            if (data.intro.on_clk[i + 4])
                pos = i;

        if (pos == -1)
        {
            i = 5;
            inc_y = 280;
            pos = 3 * (x > 390 && x < 436 && y > 120 && y < 160) + 4 * (x > 564 && x < 610 && y > 120 && y < 160);
            while (i < 16)
            {
                pos += i++ * (x - 100 > 0 && x - 100 < 500 && y - inc_y > -25 && y - inc_y < 65);
                if (i < 16)
                    pos += i++ * (x - 800 > 0 && x - 800 < 500 && y - inc_y > -25 && y - inc_y < 65);
                inc_y += 120;
            }
            if (pos && !data.intro.on_clk[pos])
            {
                if (pos == 3 || pos == 4)
                    data.intro.g_k[0] = !data.intro.g_k[0];
                else    
                    data.intro.on_clk[pos] = 3;
                data.sound.click = 1;
            }
            i = 0;
            while (++i < 15)
                data.intro.on_clk[(pos + i) % 16] = 0;
        }
    }
}

// Function to handle mouse press events for the game
void mouse_press_game(SDL_Event *event, int x, int y)
{
    if (event->button.button == SDL_BUTTON_LEFT)
    {
        if (!data.keys[data.intro.g_k[7]] && event->button.button == SDL_BUTTON_LEFT)
            data.keys[data.intro.g_k[7]] = 1;
        if (data.intro.g_k[7] == M_LEFT_CLICK && event->button.button == SDL_BUTTON_LEFT)
            data.keys[data.intro.g_k[7]] = 1;
        if (data.intro.g_k[8] == M_RIGHT_CLICK && event->button.button == SDL_BUTTON_RIGHT)
            data.keys[data.intro.g_k[8]] = 1;
    }
}

// Main mouse press handler
int mouse_press(SDL_Event *event, int x, int y)
{
    if (data.mode == INTRO)
        mouse_press_intro(event);
    else if (data.mode == SETTING || data.mode == SETTING2)
        mouse_press_setting(event, x, y);
    else if (data.mode == S_CONTROL)
        mouse_press_control(event, x, y);
    else if (data.mode == G_MAP)
        mouse_press_map(event, x, y);
    else if (data.mode == GAME && data.objects.health > 0)
        mouse_press_game(event, x, y);

    return 0;
}
