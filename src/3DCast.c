#include "../Headers/TRODO.h"
#include "../Headers/structs.h"
#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define WIDTH 800
#define HEIGHT 600


t_img load_texture(SDL_Renderer *renderer, const char *path)
{
    t_img img;
    SDL_Surface *surface = SDL_LoadBMP(path);
    if (!surface)
    {
        printf("Error loading BMP: %s\n", SDL_GetError());
        exit(1);
    }
    img.texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (!img.texture)
    {
        printf("Error creating texture: %s\n", SDL_GetError());
        SDL_FreeSurface(surface);
        exit(1);
    }
    img.width = surface->w;
    img.height = surface->h;
    img.x = 0;
    img.y = 0;
    SDL_FreeSurface(surface);
    return img;
}


void cast_to_3d(int ray_index)
{
    double dist = data.rays[ray_index];

    // Prevent division by zero and extreme values
    if (dist < 0.1)
    {
        dist = 0.1;
    }

    // Calculate wall height using distance and field of view correction
    double ray_angle = (ray_index - RES_X/2) * (ANGLE * M_PI / 180.0);
    double corrected_distance = dist * cos(ray_angle);

    // Use RES_Y for consistent vertical resolution
    int line_height = (int)((RES_Y * ANGLES) / corrected_distance);

    // Calculate drawing boundaries
    int draw_start = -line_height / 2 + RES_Y / 2;
    if (draw_start < 0)
    {
        draw_start = 0;
    }

    int draw_end = line_height / 2 + RES_Y / 2;
    if (draw_end >= RES_Y)
    {
        draw_end = RES_Y - 1;
    }

    // Store wall rendering information
    data.walls[ray_index].height = line_height;
    data.walls[ray_index].top = draw_start;
    data.walls[ray_index].bottom = draw_end;

    // Calculate texture coordinates for walls
    if (data.door.hit_wall)
    {
        int tex_x = (int)(data.color[1]) % ANGLES;
        data.walls[ray_index].tex_x = tex_x;

        // Calculate shading based on distance
        double shade = 1.0;
        if (dist > 0)
        {
            shade = 1.0 - fmin(dist / (RES_X * 0.66), 0.9);
        }
        data.walls[ray_index].shade = shade;
    }

    // Calculate floor casting
    if (draw_end < RES_Y)
    {
        for (int y = draw_end; y < RES_Y; y++)
        {
            double current_dist = RES_Y / (2.0 * y - RES_Y);
            double weight = current_dist / dist;

            double floor_x = weight * data.dir.x + (1.0 - weight) * data.dir.x;
            double floor_y = weight * data.dir.y + (1.0 - weight) * data.dir.y;

            if ((y - draw_end) < RES_Y/2)
            {
                data.floors[ray_index][y - draw_end].tex_x = (int)(floor_x * ANGLES) % ANGLES;
                data.floors[ray_index][y - draw_end].tex_y = (int)(floor_y * ANGLES) % ANGLES;
                data.floors[ray_index][y - draw_end].distance = current_dist;
            }
        }
    }

    // Calculate ceiling casting
    if (draw_start > 0)
    {
        for (int y = 0; y < draw_start && y < RES_Y/2; y++)
        {
            double ceiling_dist = RES_Y / (RES_Y - 2.0 * y);

            double ceiling_x = data.dir.x + ceiling_dist * data.angles.r_cos[ray_index];
            double ceiling_y = data.dir.y + ceiling_dist * data.angles.r_sin[ray_index];

            data.ceilings[ray_index][y].tex_x = (int)ceiling_x % ANGLES;
            data.ceilings[ray_index][y].tex_y = (int)ceiling_y % ANGLES;
            data.ceilings[ray_index][y].distance = ceiling_dist;
        }
    }
}
