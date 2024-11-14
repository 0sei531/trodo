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

    i = 0;
    while (++i < len)
    {
        path_name2(path, i, 12);
        
        // Load image using IMG_Load for various formats (like PNG, JPG)
        SDL_Surface *surface = IMG_Load(path);
        if (!surface) {
            fprintf(stderr, "Error loading image %s: %s\n", path, IMG_GetError());
            return;
        }

        // Create texture from surface
        data.gun[o].gun[i - 1].tex = SDL_CreateTextureFromSurface(data.sdl.renderer, surface);
        if (!data.gun[o].gun[i - 1].tex) {
            fprintf(stderr, "Error creating texture from surface: %s\n", SDL_GetError());
        }

        SDL_FreeSurface(surface);  // Free the surface after texture creation

        // If you need to manipulate the texture pixel data:
        // SDL_LockTexture(data.gun[o].gun[i - 1].tex, NULL, &data.gun[o].gun[i - 1].pixels, &data.gun[o].gun[i - 1].pitch);
        // Modify pixel data here (if needed)
        // SDL_UnlockTexture(data.gun[o].gun[i - 1].tex);
    }
}

void init_guns()
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

void init_motion_imgs(int o, int len, char *s, int path_len)
{
    int i;
    char path[100];
    SDL_Surface *surface;

    snprintf(path, sizeof(path), "%s", s);
    i = 0;
    while (++i < len)
    {
        path_name2(path, i, path_len);
        
        // Load image using IMG_Load
        surface = IMG_Load(path);
        if (!surface) {
            fprintf(stderr, "Error loading image %s: %s\n", path, IMG_GetError());
            return;
        }

        // Create texture from surface
        data.motion[o].frm[i - 1].tex = SDL_CreateTextureFromSurface(data.sdl.renderer, surface);
        if (!data.motion[o].frm[i - 1].tex) {
            fprintf(stderr, "Error creating texture from surface: %s\n", SDL_GetError());
        }

        SDL_FreeSurface(surface);  // Free surface after texture creation
    }

    data.motion[o].frame = len - 1;
}

void init_motion()
{
    init_motion_imgs(0, 17, "img/enemies/run/", 16);

    init_motion_imgs(1, 29, "img/enemies/walk/", 17);

    init_motion_imgs(2, 51, "img/enemies/attack_1/", 21);

    init_motion_imgs(3, 64, "img/enemies/attack_2/", 21);

    init_motion_imgs(4, 87, "img/enemies/attack_3/", 21);

    init_motion_imgs(5, 34, "img/enemies/hit/", 16);

    init_motion_imgs(6, 82, "img/enemies/death/", 18);
}
