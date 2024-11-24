#include "../Headers/TRODO.h"

void game_loop(SDL_Window *window, SDL_Renderer *renderer, t_map *map) {
    SDL_Event event;
    bool running = true;

    // Initialize data structure with the window, renderer and map
    data.sdl.window = window;      // Access through sdl struct
    data.sdl.renderer = renderer;  // Access through sdl struct
    data.game_map = map;          // Assign to game_map instead of map

    while (running) {
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    running = false;
                    break;
                case SDL_KEYDOWN:
                    handle_key_press(&event, &data);
                    break;
                case SDL_KEYUP:
                    handle_key_release(&event, &data);
                    break;
                case SDL_MOUSEMOTION:
                    handle_mouse_motion(&event, &data);
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    handle_mouse_press(&event, &data);
                    break;
                case SDL_MOUSEBUTTONUP:
                    handle_mouse_release(&event, &data);  // Pass the whole event struct
                    break;
            }
        }

        // Update game state
        move();
        render_game(&data);
        SDL_Delay(1000 / 60);  // Cap at ~60 FPS
    }

    cleanup_and_exit(window, renderer, map);
}
