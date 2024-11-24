#include <SDL2/SDL.h>
#include "../Headers/structs.h"
#include "../Headers/TRODO.h"

// Function to handle mouse press events for the game
void mouse_press_game(SDL_MouseButtonEvent *button)
{
    if (button->button == SDL_BUTTON_LEFT)
    {
        if (!data.keys[data.intro.g_k[7]] && button->button == SDL_BUTTON_LEFT)
            data.keys[data.intro.g_k[7]] = 1;
        if (data.intro.g_k[7] == M_LEFT_CLICK && button->button == SDL_BUTTON_LEFT)
            data.keys[data.intro.g_k[7]] = 1;
        if (data.intro.g_k[8] == M_RIGHT_CLICK && button->button == SDL_BUTTON_RIGHT)
            data.keys[data.intro.g_k[8]] = 1;
    }
}

// Function to handle mouse press events for the map
void mouse_press_map(SDL_MouseButtonEvent *button)
{
    if (button == NULL) return;
    // Add specific map mouse press logic if needed
}

// Main mouse press handler
int mouse_press(SDL_Event *event, int x, int y)
{
    if (event->type != SDL_MOUSEBUTTONDOWN)
        return 0;

    SDL_MouseButtonEvent *button = &event->button;

    if (data.mode == INTRO)
        mouse_press_intro(button);
    else if (data.mode == SETTING || data.mode == SETTING2)
        mouse_press_setting(button);
    else if (data.mode == S_CONTROL)
        mouse_press_control(button);
    else if (data.mode == MAP_MODE)
        mouse_press_map(button);
    else if (data.mode == GAME && data.objects.health > 0)
        mouse_press_game(button);

    (void)x;  // Suppress unused parameter warnings
    (void)y;
    return 0;
}
