#include "../Headers/TRODO.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>


void path_name2(char *path, int i, int len)
{
    int j = len;
    path[j++] = '0' + i / 10;
    path[j++] = '0' + i % 10;
    path[j++] = '.';
    path[j++] = 'x';
    path[j++] = 'p';
    path[j++] = 'm';
    path[j++] = 0;
}

void init_gun(int o, int len, char *path)
{
    int i;
    SDL_Surface *surface;

    i = 0;
    while (++i < len)
    {
        path_name2(path, i, 12);
        
        surface = IMG_Load(path);
        if (!surface) {
            SDL_Log("Error loading image %s: %s", path, IMG_GetError());
            return;
        }

        // Make sure gun[o].gun is properly allocated before using
        if (!data.gun[o].gun) {
            SDL_Log("Error: gun array not allocated for index %d", o);
            SDL_FreeSurface(surface);
            return;
        }

        data.gun[o].gun[i - 1].tex = SDL_CreateTextureFromSurface(data.sdl.renderer, surface);
        if (!data.gun[o].gun[i - 1].tex) {
            SDL_Log("Error creating texture: %s", SDL_GetError());
        }
        SDL_FreeSurface(surface);
    }
}

void init_guns(void)
{
    char path[100];
    
    snprintf(path, sizeof(path), "img/guns/g1/");
    init_gun(4, 53, path);
    snprintf(path, sizeof(path), "img/guns/g2/");
    init_gun(9, 15, path);
    snprintf(path, sizeof(path), "img/guns/g3/");
    init_gun(2, 34, path);
    snprintf(path, sizeof(path), "img/guns/g4/");
    init_gun(19, 50, path);
    snprintf(path, sizeof(path), "img/guns/g5/");
    init_gun(13, 27, path);
    snprintf(path, sizeof(path), "img/guns/g6/");
    init_gun(15, 18, path);
    snprintf(path, sizeof(path), "img/guns/g9/");
    init_gun(17, 82, path);
    snprintf(path, sizeof(path), "img/guns/g7/");
    init_gun(20, 25, path);
    snprintf(path, sizeof(path), "img/guns/g8/");
    init_gun(5, 27, path);
}

static void init_single_motion(int o, int len, char *path, int path_len)
{
    int i;
    SDL_Surface *surface;

    i = 0;
    if (!data.motion || !data.motion[o].frm) {
        SDL_Log("Error: motion array not properly allocated");
        return;
    }

    while (++i < len)
    {
        path_name2(path, i, path_len);
        
        surface = IMG_Load(path);
        if (!surface) {
            SDL_Log("Error loading image %s: %s", path, IMG_GetError());
            return;
        }

        data.motion[o].frm[i - 1].tex = SDL_CreateTextureFromSurface(data.sdl.renderer, surface);
        if (!data.motion[o].frm[i - 1].tex) {
            SDL_Log("Error creating texture: %s", SDL_GetError());
        }
        SDL_FreeSurface(surface);
    }
    data.motion[o].frame = len - 1;
}

void init_motion(void)
{
    init_single_motion(0, 17, "img/enemies/run/", 16);
    init_single_motion(1, 29, "img/enemies/walk/", 17);
    init_single_motion(2, 51, "img/enemies/attack_1/", 21);
    init_single_motion(3, 64, "img/enemies/attack_2/", 21);
    init_single_motion(4, 87, "img/enemies/attack_3/", 21);
    init_single_motion(5, 34, "img/enemies/hit/", 16);
    init_single_motion(6, 82, "img/enemies/death/", 18);
}
