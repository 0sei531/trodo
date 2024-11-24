#include "../Headers/TRODO.h"
#include "../Headers/structs.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_FRAMES 10
#define MAX_PATH_LEN 256

static void path_name2(char *path, int i, int len)
{
    if (len + 7 >= MAX_PATH_LEN) // 7 chars for "xx.xpm\0"
        return;
    
    int j = len;
    path[j++] = '0' + (i / 10);
    path[j++] = '0' + (i % 10);
    path[j++] = '.';
    path[j++] = 'p';
    path[j++] = 'n';
    path[j++] = 'g';
    path[j] = '\0';
}

// Cleanup functions
static void cleanup_gun_frames(t_gun *gun)
{
    if (gun && gun->gun)
    {
        for (int i = 0; i < MAX_FRAMES; i++)
        {
            if (gun->gun[i].texture)
            {
                SDL_DestroyTexture(gun->gun[i].texture);
                gun->gun[i].texture = NULL;
            }
        }
        free(gun->gun);
        gun->gun = NULL;
    }
}

void cleanup_motion(void)
{
    if (data.motion)
    {
        for (int i = 0; i < 7; i++)
        {
            if (data.motion[i].frm)
            {
                for (int j = 0; j < MAX_FRAMES; j++)
                {
                    if (data.motion[i].frm[j].texture)
                    {
                        SDL_DestroyTexture(data.motion[i].frm[j].texture);
                    }
                }
                free(data.motion[i].frm);
            }
        }
        free(data.motion);
        data.motion = NULL;
    }
}

// Gun initialization functions
static void allocate_gun_frames(int o, int num_frames)
{
    if (o < 0 || o >= 27)
    {
        SDL_Log("Invalid gun index: %d", o);
        return;
    }

    // Free existing frames if any
    cleanup_gun_frames(&data.gun[o]);

    // Allocate new frames
    data.gun[o].gun = calloc(num_frames, sizeof(t_img));
    if (!data.gun[o].gun)
    {
        SDL_Log("Failed to allocate memory for gun frames");
        return;
    }
    data.gun[o].frame = num_frames;
    data.gun[o].bullet = 0;
    data.gun[o].case_bullet = 0;
    data.gun[o].f_reload = 0;
    data.gun[o].f_shoot = 0;
}

static void init_gun(int o, int len, char *path)
{
    if (!path || len <= 0)
    {
        SDL_Log("Invalid parameters for init_gun");
        return;
    }

    allocate_gun_frames(o, len);
    if (!data.gun[o].gun)
        return;

    char full_path[MAX_PATH_LEN];
    SDL_Surface *surface;

    for (int i = 1; i < len; i++)
    {
        strncpy(full_path, path, MAX_PATH_LEN - 1);
        path_name2(full_path, i, strlen(path));

        surface = IMG_Load(full_path);
        if (!surface)
        {
            SDL_Log("Error loading image %s: %s", full_path, IMG_GetError());
            continue;
        }

        data.gun[o].gun[i - 1].texture = SDL_CreateTextureFromSurface(data.sdl.renderer, surface);
        if (!data.gun[o].gun[i - 1].texture)
        {
            SDL_Log("Error creating texture: %s", SDL_GetError());
            SDL_FreeSurface(surface);
            continue;
        }

        // Get texture dimensions
        SDL_QueryTexture(data.gun[o].gun[i - 1].texture, NULL, NULL, 
                        &data.gun[o].gun[i - 1].width, 
                        &data.gun[o].gun[i - 1].height);

        SDL_FreeSurface(surface);
    }
}

void init_guns(void)
{
    const char *gun_paths[] = {
        "img/guns/g1/", "img/guns/g2/", "img/guns/g3/",
        "img/guns/g4/", "img/guns/g5/", "img/guns/g6/",
        "img/guns/g9/", "img/guns/g7/", "img/guns/g8/"
    };
    
    const int gun_indices[] = {4, 9, 2, 19, 13, 15, 17, 20, 5};
    const int gun_frames[] = {53, 15, 34, 50, 27, 18, 82, 25, 27};
    
    const int num_guns = sizeof(gun_indices) / sizeof(gun_indices[0]);
    char path[MAX_PATH_LEN];
    
    for (int i = 0; i < num_guns; i++)
    {
        strncpy(path, gun_paths[i], MAX_PATH_LEN - 1);
        init_gun(gun_indices[i], gun_frames[i], path);
    }
}

// Motion initialization functions
static void init_single_motion(int o, int len, const char *base_path, int path_len)
{
    if (o < 0 || o >= 7 || !data.motion || !data.motion[o].frm)
    {
        SDL_Log("Invalid motion parameters or uninitialized motion array");
        return;
    }

    char full_path[MAX_PATH_LEN];
    SDL_Surface *surface;

    for (int i = 1; i < len; i++)
    {
        strncpy(full_path, base_path, MAX_PATH_LEN - 1);
        path_name2(full_path, i, path_len);

        surface = IMG_Load(full_path);
        if (!surface)
        {
            SDL_Log("Error loading image %s: %s", full_path, IMG_GetError());
            continue;
        }

        data.motion[o].frm[i - 1].texture = SDL_CreateTextureFromSurface(data.sdl.renderer, surface);
        if (!data.motion[o].frm[i - 1].texture)
        {
            SDL_Log("Error creating texture: %s", SDL_GetError());
            SDL_FreeSurface(surface);
            continue;
        }

        // Get texture dimensions
        SDL_QueryTexture(data.motion[o].frm[i - 1].texture, NULL, NULL,
                        &data.motion[o].frm[i - 1].width,
                        &data.motion[o].frm[i - 1].height);

        SDL_FreeSurface(surface);
    }
    data.motion[o].frame = len - 1;
}

static void allocate_motion_arrays(void)
{
    // Free existing motion arrays if any
    cleanup_motion();

    // Allocate main motion array
    data.motion = calloc(7, sizeof(t_motion));
    if (!data.motion)
    {
        SDL_Log("Failed to allocate motion array");
        return;
    }

    // Allocate frame arrays for each motion
    for (int i = 0; i < 7; i++)
    {
        data.motion[i].frm = calloc(MAX_FRAMES, sizeof(t_img));
        if (!data.motion[i].frm)
        {
            SDL_Log("Failed to allocate motion frames for index %d", i);
            cleanup_motion();
            return;
        }
        data.motion[i].frame = 0;
    }
}

void init_motion(void)
{
    const struct {
        const char *path;
        int frames;
        int path_len;
    } motion_data[] = {
        {"img/enemies/run/", 17, 16},
        {"img/enemies/walk/", 29, 17},
        {"img/enemies/attack_1/", 51, 21},
        {"img/enemies/attack_2/", 64, 21},
        {"img/enemies/attack_3/", 87, 21},
        {"img/enemies/hit/", 34, 16},
        {"img/enemies/death/", 82, 18}
    };

    allocate_motion_arrays();
    if (!data.motion)
        return;

    for (int i = 0; i < 7; i++)
    {
        init_single_motion(i, motion_data[i].frames, 
                         motion_data[i].path, 
                         motion_data[i].path_len);
    }
}
