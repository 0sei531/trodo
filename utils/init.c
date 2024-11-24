#include "../Headers/TRODO.h"

void init_args(t_map **map) {
    if (!map)
        return;
    *map = (t_map *)malloc(sizeof(t_map));
    if (!*map)
        return;
    
    // Initialize map structure members according to structs.h
    (*map)->content = NULL;  // Changed from grid to content as per struct definition
    (*map)->next = NULL;     // Added next pointer initialization
}

void free_map_struct(t_map *map) {
    if (!map)
        return;
    
    // Free the content if it exists
    if (map->content)
        free(map->content);
    
    // Free the map structure itself
    free(map);
}

int init_game(SDL_Window *window, SDL_Renderer *renderer, t_map *map) {
    if (!window || !renderer || !map)
        return 0;
    
    // Initialize game state according to t_data structure
    data.sdl.window = window;      // Using sdl substructure
    data.sdl.renderer = renderer;  // Using sdl substructure
    data.game_map = map;          // Using game_map as per struct definition
    
    // Initialize player data
    data.player.x = 2.0f;
    data.player.y = 2.0f;
    data.player.dirX = -1.0f;
    data.player.dirY = 0.0f;
    data.player.planeX = 0.0f;
    data.player.planeY = 0.66f;
    
    // Initialize game mode
    data.mode = INTRO;
    
    // Initialize mouse state
    data.mouse.on = 0;
    data.mouse.clicked = 0;
    data.mouse.x = 0;
    data.mouse.y = 0;
    
    return 1;
}
