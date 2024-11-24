#include "../Headers/TRODO.h"

static void render_intro_screens(SDL_Renderer *renderer) {
    // Implementation for intro screens rendering
    if (!renderer) return;
    
    // Add your intro screens rendering logic here
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    
    // Render intro elements based on current mode
    if (data.mode == INTRO) {
        // Render INTRO screen elements
        if (data.intro.vol[0]) {  // Assuming these textures exist
            SDL_RenderCopy(renderer, data.intro.vol[0], NULL, NULL);
        }
        if (data.intro.lgt[0]) {
            SDL_RenderCopy(renderer, data.intro.lgt[0], NULL, NULL);
        }
    } else if (data.mode == INTRO1) {
        // Render INTRO1 screen elements
    } else if (data.mode == INTRO2) {
        // Render INTRO2 screen elements
    }
}

static void render_settings_screens(SDL_Renderer *renderer) {
    // Implementation for settings screens rendering
    if (!renderer) return;
    
    // Add your settings screens rendering logic here
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    
    // Render settings elements based on current mode
    if (data.mode == SETTING) {
        // Render main settings screen
        // Example: Render setting buttons, sliders, etc.
        
    } else if (data.mode == SETTING2) {
        // Render secondary settings screen
        // Example: Render volume controls, brightness settings, etc.
        if (data.intro.vol[data.intro.volume]) {
            SDL_RenderCopy(renderer, data.intro.vol[data.intro.volume], NULL, NULL);
        }
        if (data.intro.lgt[data.intro.light]) {
            SDL_RenderCopy(renderer, data.intro.lgt[data.intro.light], NULL, NULL);
        }
        
    } else if (data.mode == S_CONTROL) {
        // Render controls settings screen
        // Example: Render key binding options, control scheme selection, etc.
    }
}

void render_game(t_data *data) {
    if (!data || !data->sdl.renderer) 
        return;

    // Clear screen
    SDL_SetRenderDrawColor(data->sdl.renderer, 0, 0, 0, 255);
    SDL_RenderClear(data->sdl.renderer);

    // Render based on game mode
    switch (data->mode) {
        case GAME:
            // Render 3D view
            for (int i = 0; i < FOV_RAYS; i++) {
                cast_to_3d(i);
            }
            // Render minimap if needed
            set_minimap();
            break;

        case INTRO:
        case INTRO1:
        case INTRO2:
            render_intro_screens(data->sdl.renderer);
            break;

        case SETTING:
        case SETTING2:
        case S_CONTROL:
            render_settings_screens(data->sdl.renderer);
            break;

        default:
            // Handle any other modes
            break;
    }

    // Present the rendered frame
    SDL_RenderPresent(data->sdl.renderer);
}
