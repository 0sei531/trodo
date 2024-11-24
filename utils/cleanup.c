#include "../Headers/TRODO.h"

void cleanup_and_exit(SDL_Window *window, SDL_Renderer *renderer, t_map *map) {
    (void)window;    // Suppress unused parameter warning
    (void)renderer;  // Suppress unused parameter warning

    // Clean up game textures and resources
    if (data.mouse.img) {
        SDL_DestroyTexture(data.mouse.img);
        data.mouse.img = NULL;
    }

    // Clean up SDL resources
    if (data.sdl.renderer) {
        SDL_DestroyRenderer(data.sdl.renderer);
        data.sdl.renderer = NULL;
    }

    if (data.sdl.window) {
        SDL_DestroyWindow(data.sdl.window);
        data.sdl.window = NULL;
    }

    // Clean up map
    if (map) {
        ft_lst_clear(&map, free);
    }

    // Quit SDL subsystems
    IMG_Quit();
    SDL_Quit();
}
