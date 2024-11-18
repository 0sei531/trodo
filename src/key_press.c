#include "../Headers/TRODO.h"
#include "../Headers/structs.h"
#include <SDL2/SDL.h>

// Handle key press in the intro mode
void key_press_intro(SDL_KeyboardEvent *key)
{
    data.mouse.on_click = 1;
}

// Handle key press in the settings mode
void key_press_setting(SDL_KeyboardEvent *key)
{
    int o = data.mouse.on_hov[0] + 2 * data.mouse.on_hov[1] + 3 * data.mouse.on_hov[2];
    
    if (key->keysym.sym == SDLK_UP && !o)
        data.mouse.on_hov[2] = 1;
    else if (key->keysym.sym == SDLK_UP)
    {
        data.mouse.on_hov[o - 1] = 0;
        data.mouse.on_hov[o % 3] = 0;
        data.mouse.on_hov[(o + 1) % 3] = 1;
    }

    if (key->keysym.sym == SDLK_DOWN && !o)
        data.mouse.on_hov[0] = 1;
    else if (key->keysym.sym == SDLK_DOWN)
    {
        data.mouse.on_hov[o - 1] = 0;
        data.mouse.on_hov[o % 3] = 1;
        data.mouse.on_hov[(o + 1) % 3] = 0;
    }

    if (key->keysym.sym == SDLK_RETURN && o)
        data.mouse.on_clk[o - 1] = 1;
}

// Handle key press in the second setting mode
void key_press_setting2(SDL_KeyboardEvent *key)
{
    int o = 2 * data.mouse.on_hov[1] + 3 * data.mouse.on_hov[2] + 4 * data.mouse.on_hov[3] + 5 * data.mouse.on_hov[4];
    
    if (key->keysym.sym == SDLK_UP && !o)
        data.mouse.on_hov[2] = 1;
    else if (key->keysym.sym == SDLK_UP)
    {
        data.mouse.on_hov[o - 1] = 0;
        data.mouse.on_hov[o % 5 + (o > 4)] = 0;
        data.mouse.on_hov[(o + 1) % 5 + ((o + 1) > 4)] = 0;
        data.mouse.on_hov[(o + 2) % 5 + ((o + 2) > 4)] = 1;
    }

    if (key->keysym.sym == SDLK_DOWN && !o)
        data.mouse.on_hov[3] = 1;
    else if (key->keysym.sym == SDLK_DOWN)
    {
        data.mouse.on_hov[o - 1] = 0;
        data.mouse.on_hov[o % 5 + (o > 4)] = 1;
        data.mouse.on_hov[(o + 1) % 5 + ((o + 1) > 4)] = 0;
        data.mouse.on_hov[(o + 2) % 5 + ((o + 2) > 4)] = 0;
    }

    if (key->keysym.sym == SDLK_RETURN && o)
        data.mouse.on_clk[o - 1] = 1;
    
    if (key->keysym.sym == SDLK_ESCAPE)
        data.mode = ANIMATE_SETT2_OUT;
}

// Function to check if a key is in use
int key_not_in_use(SDL_KeyboardEvent *key)
{
    int i;
    for (i = 0; i < 12; i++)
    {
        if (key->keysym.sym == data.intro.g_k[i] && !data.intro.on_clk[i + 4])
            return 0;
    }
    return 1;
}

// Handle key press for control settings
void key_press_control(SDL_KeyboardEvent *key)
{
    int i;
    int pos = -1;

    if (key->keysym.sym == SDLK_ESCAPE)
        data.mode = SETTING * !data.mouse.sett2 + SETTING2 * data.mouse.sett2;

    if (key_not_in_use(key))
    {
        for (i = 0; i < 12; i++)
        {
            if (data.intro.on_clk[i + 4])
                pos = i;
        }

        if (data.intro.keys[key->keysym.sym] && pos != -1)
            data.intro.g_k[pos] = key->keysym.sym;
    }

    for (i = 0; i < 16; i++)
        data.intro.on_clk[i] = 0;
}

// Handle key press for map mode
void key_press_map(SDL_KeyboardEvent *key)
{
    if (key->keysym.sym == data.intro.g_k[10])
    {
        data.intro.up = !data.intro.up;
        data.mv_x = 0;
        data.mv_y = 0;
        data.keys[data.intro.g_k[7]] = 0;
    }
}

// Handle key press during the game
void key_press_game(SDL_KeyboardEvent *key)
{
    if (data.objects.health > 0)
    {
        if (key->keysym.sym == SDLK_F1 && data.mouse.show)
        {
            SDL_HideCursor();
            data.mouse.show = 0;
        }
        else if (key->keysym.sym == SDLK_F1)
        {
            SDL_ShowCursor(SDL_ENABLE);
            data.mouse.show = 1;
        }

        if (key->keysym.sym == data.intro.g_k[10])
        {
            data.mode = G_MAP;
            data.intro.up = !data.intro.up;
        }

        if (key->keysym.sym == data.intro.g_k[6])
        {
            data.fov.crouching = !data.fov.crouching;
            data.fov.jumping = 0;
        }

        if (key->keysym.sym == data.intro.g_k[5] && ((!data.fov.jumping && data.dir.ph == 0.5) || data.fov.crouching))
        {
            data.fov.jumping = !data.fov.jumping;
            data.fov.crouching = 0;
        }

        data.keys[key->keysym.sym] = 1;

        if (key->keysym.sym == data.intro.g_k[7] && data.use_gun > 100)
            data.use_gun = 0;

        if (key->keysym.sym == SDLK_SPACE)
            data.fov.crouching = 0;
    }

    if (key->keysym.sym == SDLK_ESCAPE)
    {
        data.mode = ANIMATE_SETT2_IN;
        set_char_to_win();
        data.intro.animate_sett = 700;
    }
}

// Handle key press for animation settings (in/out)
void key_press_animate_sett_in(SDL_KeyboardEvent *key)
{
    if (key->keysym.sym == SDLK_ESCAPE)
        data.mode = ANIMATE_SETT2_OUT;
}

void key_press_animate_sett_out(SDL_KeyboardEvent *key)
{
    if (key->keysym.sym == SDLK_ESCAPE)
        data.mode = ANIMATE_SETT2_IN;
}

// Main key press handler
int key_press(SDL_KeyboardEvent *key, void *d)
{
    d = NULL;

    if (data.mode == INTRO)
        key_press_intro(key);
    else if (data.mode == SETTING)
        key_press_setting(key);
    else if (data.mode == SETTING2)
        key_press_setting2(key);
    else if (data.mode == ANIMATE_SETT2_IN)
        key_press_animate_sett_in(key);
    else if (data.mode == ANIMATE_SETT2_OUT)
        key_press_animate_sett_out(key);
    else if (data.mode == S_CONTROL)
        key_press_control(key);
    else if (data.mode == G_MAP)
        key_press_map(key);
    else if (data.mode == GAME)
        key_press_game(key);

    return 0;
}
