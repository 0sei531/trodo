#include <SDL2/SDL.h>
#include "../Headers/structs.h"
#include "../Headers/TRODO.h"
#include <math.h>

void variant_calculate_d(double *cord, double decrease, int angl) {
    while (data.map[(int)(cord[1] + decrease * data.angles.r_sin[angl]) / 50][(int)cord[0] / 50] == '0'
        && data.map[(int)cord[1] / 50][(int)(cord[0] + decrease * data.angles.r_cos[angl]) / 50] == '0'
        && data.map[(int)(cord[1] + decrease * data.angles.r_sin[angl]) / 50][(int)(cord[0] + decrease * data.angles.r_cos[angl]) / 50] == '0') {
        cord[0] += decrease * data.angles.r_cos[angl];
        cord[1] += decrease * data.angles.r_sin[angl];
    }
}

void variant_calculate(double *cord, double decrease, int angl) {
    while (data.map[(int)(cord[1] + decrease * data.angles.r_sin[angl]) / 50][(int)cord[0] / 50] != '1'
        && data.map[(int)cord[1] / 50][(int)(cord[0] + decrease * data.angles.r_cos[angl]) / 50] != '1'
        && data.map[(int)(cord[1] + decrease * data.angles.r_sin[angl]) / 50][(int)(cord[0] + decrease * data.angles.r_cos[angl]) / 50] != '1') {
        cord[0] += decrease * data.angles.r_cos[angl];
        cord[1] += decrease * data.angles.r_sin[angl];
    }
}

void init_angles() {
    double r = -30;
    int max_index = sizeof(data.angles.r_cos) / sizeof(data.angles.r_cos[0]);
    max_index = (max_index < RES_X) ? max_index : RES_X;

    for (int i = 0; i < max_index; i++) {
        double angl = data.dir.angle + r;
        data.angles.r_cos[i] = cos(angl * M_PI / 180);
        data.angles.r_sin[i] = sin(angl * M_PI / 180);
        data.angles.r_res_cos[i] = cos(r * M_PI / 180);
        r += 0.04;
    }

    data.angles.pl_cos = cos(data.dir.angle * M_PI / 180);
    data.angles.pl_sin = sin(data.dir.angle * M_PI / 180);
    data.angles.pl_cos_plus_90 = cos((data.dir.angle + 90) * M_PI / 180);
    data.angles.pl_sin_plus_90 = sin((data.dir.angle + 90) * M_PI / 180);
    data.angles.cte_tan = tan(30 * M_PI / 180);
}

void set_rays(SDL_Renderer *renderer, t_map *map) {
    (void)map;  // Explicitly mark parameter as unused
    double cord[2];
    int max_rays = sizeof(data.rays) / sizeof(data.rays[0]);
    max_rays = (max_rays < RES_X) ? max_rays : RES_X;

    for (int i = 0; i < max_rays; i++) {
        data.color[0] = 0;
        cord[0] = data.dir.x + 17;
        cord[1] = data.dir.y + 17;
        data.indx = i;

        // Variant calculations to detect walls
        variant_calculate_d(cord, 45, i);
        variant_calculate_d(cord, 20, i);
        variant_calculate_d(cord, 10, i);
        variant_calculate_d(cord, 1, i);
        variant_calculate_d(cord, 0.1, i);

        // Added initialization for hit_wall
        data.door.hit_wall = 0;  // Fixed: initialized explicit hit_wall

        // Draw ray line for minimap visualization
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);  // Red ray color
        SDL_RenderDrawLine(renderer,
            (int)data.dir.x + 17, (int)data.dir.y + 17,
            (int)cord[0], (int)cord[1]);

        // Wall collision handling
        if (data.map[(int)cord[1] / 50][(int)(cord[0] + data.angles.r_cos[i]) / 50] == '1') {
            data.color[1] = (cord[0] + data.angles.r_cos[i] > cord[0]) ?
                (int)cord[1] : (int)cord[1];
            data.door.hit_wall = 1;  // Mark wall hit
        }
        else if (data.map[(int)(cord[1] + data.angles.r_sin[i]) / 50][(int)cord[0] / 50] == '1') {
            data.color[1] = (cord[1] + data.angles.r_sin[i] > cord[1]) ?
                (int)cord[0] : (int)cord[0];
            data.door.hit_wall = 1;  // Mark wall hit
        }

        // Calculate ray distance
        data.rays[i] = sqrt(pow(cord[0] - (data.dir.x + 17), 2) +
                           pow(cord[1] - (data.dir.y + 17), 2)) *
                           data.angles.r_res_cos[i];

        // Map design detection
        int map_y = (int)(cord[1] - data.angles.r_sin[i]) / 50;
        int map_x = (int)(cord[0] - data.angles.r_cos[i]) / 50;
        if (map_y >= 0 && map_x >= 0 && map_y < data.h_map && map_x < data.w_map[map_y]) {
            data.design = &data.door.map[map_y][map_x];
        }

        // Cast rays to 3D
        if (i < RES_X) {
            cast_to_3d(i);
        }
    }

    data.light = (data.light + 1) % 600;
}

void set_minimap(void) {
    SDL_Window *window = SDL_CreateWindow("Minimap",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        RES_X/2, RES_Y/2,  // Reduced size
        SDL_WINDOW_SHOWN);

    if (!window) {
        fprintf(stderr, "Window creation failed: %s\n", SDL_GetError());
        return;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1,
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    if (!renderer) {
        fprintf(stderr, "Renderer creation failed: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        return;
    }

    // Clear renderer with black background
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    // Render map tiles
    for (int y = 0; y < data.h_map; y++) {
        for (int x = 0; x < data.w_map[y]; x++) {
            SDL_Rect tile;
            tile.x = x * 25;  // Scale factor for visibility
            tile.y = y * 25;
            tile.w = 25;
            tile.h = 25;

            if (data.map[y][x] == '1') {
                SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255);  // Wall color
                SDL_RenderFillRect(renderer, &tile);
            } else if (data.map[y][x] == '0') {
                SDL_SetRenderDrawColor(renderer, 50, 50, 50, 255);  // Floor color
                SDL_RenderDrawRect(renderer, &tile);
            }
        }
    }

    // Draw player position
    SDL_Rect player;
    player.x = (int)data.dir.x;
    player.y = (int)data.dir.y;
    player.w = 10;
    player.h = 10;
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);  // Green player
    SDL_RenderFillRect(renderer, &player);

    // Call set_rays to draw ray casting lines
    set_rays(renderer, NULL);

    SDL_RenderPresent(renderer);

    // Optional: Add a delay or event handling if needed
    SDL_Delay(100);

    // Cleanup
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
}
