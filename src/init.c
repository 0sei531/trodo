#include "../Headers/TRODO.h"

void init_args(t_map **map)
{
    *map = NULL;  // Initialize map pointer
    // Add any additional initialization logic
}

void free_map_struct(t_map *map)
{
    if (map) {
        // Free map contents
        free(map);
    }
}

void cleanup_and_exit(SDL_Window *window, SDL_Renderer *renderer, t_map *map)
{
    free_map_struct(map);
    
    if (renderer)
        SDL_DestroyRenderer(renderer);
    
    if (window)
        SDL_DestroyWindow(window);
    
    SDL_Quit();
    exit(0);
}
