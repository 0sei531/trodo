#include "../Headers/TRODO.h"

void handle_mouse_press(SDL_Event *event, t_data *data) {
    if (!event || !data) return;
    SDL_MouseButtonEvent *button = &event->button;
    // Update mouse state
    data->mouse.x = button->x;
    data->mouse.y = button->y;
    data->mouse.clicked = 1;
    // Handle mouse press based on game mode
    switch (data->mode) {
        case INTRO:
            mouse_press_intro(button);
            break;
        case SETTING:
            mouse_press_setting(button);
            break;
        case SETTING2:
            mouse_press_setting2(button);
            break;
        case S_CONTROL:
            mouse_press_control(button);
            break;
        case GAME:
            // Handle game mode mouse input
            // Add your game-specific mouse handling here
            break;
        default:
            break;
    }
}

void mouse_press_intro(SDL_MouseButtonEvent *button) {
    if (!button) return;
    
    t_intro *intro = &data.intro;
    
    // Check for clicks on intro buttons
    if (button->button == SDL_BUTTON_LEFT) {
        // Start button
        if (button->x >= intro->start.x && button->x <= intro->start.x + 200 &&
            button->y >= intro->start.y && button->y <= intro->start.y + 50) {
            intro->on_clk[0] = 1;
            data.mode = GAME;
        }
        // Settings button
        else if (button->x >= intro->sett.x && button->x <= intro->sett.x + 200 &&
                 button->y >= intro->sett.y && button->y <= intro->sett.y + 50) {
            intro->on_clk[1] = 1;
            data.mode = SETTING;
        }
        // Exit button
        else if (button->x >= intro->exit.x && button->x <= intro->exit.x + 200 &&
                 button->y >= intro->exit.y && button->y <= intro->exit.y + 50) {
            intro->on_clk[2] = 1;
            // Handle exit
        }
    }
}

void mouse_press_setting(SDL_MouseButtonEvent *button) {
    if (!button) return;
    
    // Handle settings screen button clicks
    if (button->button == SDL_BUTTON_LEFT) {
        // Example: Check for clicks in various settings regions
        if (button->x >= 50 && button->x <= 250) {
            if (button->y >= 100 && button->y <= 150) {
                // First setting option
                data.mode = SETTING2;
            }
            else if (button->y >= 200 && button->y <= 250) {
                // Second setting option
                data.mode = S_CONTROL;
            }
            // Add more settings options as needed
        }
        
        // Back button (example coordinates)
        if (button->x >= 700 && button->x <= 780 &&
            button->y >= 20 && button->y <= 60) {
            data.mode = INTRO;
        }
    }
}

void mouse_press_setting2(SDL_MouseButtonEvent *button) {
    if (!button) return;
    
    // Handle secondary settings screen
    if (button->button == SDL_BUTTON_LEFT) {
        // Volume controls
        if (button->x >= 50 && button->x <= 250) {
            if (button->y >= 100 && button->y <= 150) {
                data.intro.volume = !data.intro.volume;
                set_volume();  // Assuming this function exists to handle volume changes
            }
        }
        
        // Light controls
        if (button->x >= 50 && button->x <= 250) {
            if (button->y >= 200 && button->y <= 250) {
                data.intro.light = !data.intro.light;
                data.light = data.intro.light;
            }
        }
        
        // Back button (example coordinates)
        if (button->x >= 700 && button->x <= 780 &&
            button->y >= 20 && button->y <= 60) {
            data.mode = SETTING;
        }
    }
}

void mouse_press_control(SDL_MouseButtonEvent *button) {
    if (!button) return;
    
    // Handle controls settings screen
    if (button->button == SDL_BUTTON_LEFT) {
        // Key binding areas (example coordinates)
        if (button->x >= 50 && button->x <= 250) {
            if (button->y >= 100 && button->y <= 150) {
                // Waiting for new key binding for movement
                data.intro.up = 1;
            }
            else if (button->y >= 200 && button->y <= 250) {
                // Other control settings
                data.intro.up = 0;
            }
        }
        
        // Back button
        if (button->x >= 700 && button->x <= 780 &&
            button->y >= 20 && button->y <= 60) {
            data.mode = SETTING;
        }
    }
}
