#include "../Headers/TRODO.h"
#include <SDL2/SDL.h>

int key_release(SDL_KeyboardEvent *key, void *d)
{
    d = NULL;

    // Check if the game is in the intro mode
    if (data.mode == INTRO)
    {
        if (!data.mouse.clicked)
            data.mouse.clicked = 1;
        data.mouse.on_click = 0;
    }

    // Handle key release actions for different modes
    if (data.mode == SETTING && key->keysym.sym == SDLK_RETURN && data.mouse.on_clk[0])
    {
        data.mouse.on_clk[0] = 0;
        data.mode = GAME;
    }

    if ((data.mode == SETTING || data.mode == SETTING2) && key->keysym.sym == SDLK_RETURN && data.mouse.on_clk[1])
    {
        data.mouse.on_clk[1] = 0;
        data.mode = S_CONTROL;
    }

    if ((data.mode == SETTING || data.mode == SETTING2) && key->keysym.sym == SDLK_RETURN && data.mouse.on_clk[2])
    {
        data.mouse.on_clk[2] = 0;
        SDL_RenderClear(data.renderer);  // Assuming you are using SDL_Renderer for rendering
        exit(0);  // Exit the application
    }

    if (data.mode == SETTING2 && key->keysym.sym == SDLK_RETURN && data.mouse.on_clk[3])
    {
        data.mouse.on_clk[3] = 0;
        data.mode = GAME;
    }

    // Reset the key state in the SDL key state array (if applicable)
    data.keys[key->keysym.sym] = 0;

    return 0;
}
