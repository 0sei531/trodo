#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "../Headers/structs.h"
#include "../Headers/TRODO.h"
#include <string.h>
#include <stdio.h>

// Global variables
int cnt, c, ac, a, i, f, mm;

void path_name(char *path, char *p, int i, int len)
{
    int j;

    memcpy(path, p, len);
    j = len;
    if (i / 100)
        path[j++] = '0' + (i / 100);
    if (i / 10)
        path[j++] = '0' + (i % 100) / 10;
    path[j++] = '0' + (i % 10);
    path[j++] = '.';
    path[j++] = 'p';
    path[j++] = 'n';
    path[j++] = 'g';
    path[j++] = 0;
}

Uint32 get_img_color(SDL_Surface *surface, int x, int y)
{
    Uint32 *pixels = (Uint32*)surface->pixels;
    return pixels[y * (surface->pitch / sizeof(Uint32)) + x];
}

void img_pix_put(SDL_Surface *surface, int x, int y, Uint32 color)
{
    Uint32 *pixels = (Uint32*)surface->pixels;
    pixels[y * (surface->pitch / sizeof(Uint32)) + x] = color;
}

void set_pixel(SDL_Texture* texture, int x, int y, Uint32 color)
{
    int pitch;
    void* pixels;
    if (SDL_LockTexture(texture, NULL, &pixels, &pitch) == 0) {
        ((Uint32*)pixels)[y * (pitch / sizeof(Uint32)) + x] = color;
        SDL_UnlockTexture(texture);
    }
}

void render_intro(t_sdl *sdl)
{
    char path[100];
    SDL_Surface *temp_surface;
    t_img img;

    SDL_SetRenderDrawColor(sdl->renderer, 0, 0, 0, 255);
    SDL_RenderClear(sdl->renderer);

    path_name(path, "img/intro/", i, 10);
    temp_surface = IMG_Load(path);
    if (temp_surface) {
        img.texture = SDL_CreateTextureFromSurface(sdl->renderer, temp_surface);
        img.width = 498;
        img.height = 280;
        SDL_Rect dst = {
            .x = (RES_X - 498) / 2,
            .y = (RES_Y - 280) / 2,
            .w = 498,
            .h = 280
        };
        SDL_RenderCopy(sdl->renderer, img.texture, NULL, &dst);
        SDL_FreeSurface(temp_surface);
        SDL_DestroyTexture(img.texture);
    }

    SDL_Surface *overlay = SDL_CreateRGBSurface(0, 498, 280, 32,
        0xFF000000, 0x00FF0000, 0x0000FF00, 0x000000FF);

    if (overlay) {
        SDL_LockSurface(overlay);
        for (int y = 0; y < 280; y++) {
            for (int x = 0; x < 498; x++) {
                Uint32 alpha;
                if (x < 125)
                    alpha = x * 2;
                else if (x > 498 - 125)
                    alpha = (-x + 498 - 125) * 2;
                else if (y < 10)
                    alpha = y * 20;
                else if (y > 280 - 10)
                    alpha = (-y + 280 - 10) * 20;
                else
                    alpha = 255;

                img_pix_put(overlay, x, y, (alpha << 24));
            }
        }
        SDL_UnlockSurface(overlay);

        SDL_Texture *overlay_texture = SDL_CreateTextureFromSurface(sdl->renderer, overlay);
        SDL_SetTextureBlendMode(overlay_texture, SDL_BLENDMODE_BLEND);
        SDL_Rect overlay_dst = {
            .x = (RES_X - 498) / 2,
            .y = (RES_Y - 280) / 2,
            .w = 498,
            .h = 280
        };
        SDL_RenderCopy(sdl->renderer, overlay_texture, NULL, &overlay_dst);

        SDL_DestroyTexture(overlay_texture);
        SDL_FreeSurface(overlay);
    }

    i++;
    if (i == 182)
        f = 1;
    i = i * (i < 182);

    if (f) {
        SDL_Surface *press_surface = IMG_Load("img/press_to_continue.png");
        if (press_surface) {
            SDL_LockSurface(press_surface);
            for (int y = 0; y < 53; y++) {
                for (int x = 0; x < 439; x++) {
                    Uint32 color = get_img_color(press_surface, x, y);
                    if (data.mouse.on_click && (color & 0xFF000000) != 0xFF000000)
                        img_pix_put(press_surface, x, y, 0xFFFFFFFF);
                    else if (!data.mouse.hover && (color & 0xFF000000) != 0xFF000000)
                        img_pix_put(press_surface, x, y, color + ((i * 2) << 24));
                    else if ((color & 0xFF000000) == 0)
                        img_pix_put(press_surface, x, y, color + 0xac51e38);
                }
            }
            SDL_UnlockSurface(press_surface);

            SDL_Texture *press_texture = SDL_CreateTextureFromSurface(sdl->renderer, press_surface);
            SDL_SetTextureBlendMode(press_texture, SDL_BLENDMODE_BLEND);
            SDL_Rect press_dst = {
                .x = (RES_X - 498) / 2 + 35,
                .y = (RES_Y + 280) / 2 + 70,
                .w = 439,
                .h = 53
            };
            SDL_RenderCopy(sdl->renderer, press_texture, NULL, &press_dst);

            SDL_DestroyTexture(press_texture);
            SDL_FreeSurface(press_surface);
        }
    }

    if (data.mouse.clicked) {
        SDL_Surface *fade = SDL_CreateRGBSurface(0, RES_X, RES_Y, 32,
            0xFF000000, 0x00FF0000, 0x0000FF00, 0x000000FF);

        if (fade) {
            SDL_LockSurface(fade);
            for (int y = 0; y < RES_Y; y++) {
                for (int x = 0; x < RES_X; x++) {
                    img_pix_put(fade, x, y, 0x000000 + ((255 - data.mouse.clicked * 2) << 24));
                }
            }
            SDL_UnlockSurface(fade);

            SDL_Texture *fade_texture = SDL_CreateTextureFromSurface(sdl->renderer, fade);
            SDL_SetTextureBlendMode(fade_texture, SDL_BLENDMODE_BLEND);
            SDL_RenderCopy(sdl->renderer, fade_texture, NULL, NULL);

            SDL_DestroyTexture(fade_texture);
            SDL_FreeSurface(fade);
        }
        data.mouse.clicked++;
    }
}

void render_intro1(t_sdl *sdl)
{
    char path[100];
    SDL_Surface *temp_surface;
    t_img img;

    path_name(path, "img/intro1/", mm++, 11);
    SDL_RenderClear(sdl->renderer);

    temp_surface = IMG_Load(path);
    if (temp_surface) {
        img.texture = SDL_CreateTextureFromSurface(sdl->renderer, temp_surface);
        SDL_RenderCopy(sdl->renderer, img.texture, NULL, NULL);
        SDL_FreeSurface(temp_surface);
        SDL_DestroyTexture(img.texture);
    }

    SDL_RenderPresent(sdl->renderer);

    if (mm >= 175)
        data.mode = INTRO2;
}

void render_intr(t_sdl *sdl, SDL_Surface *source)
{
    SDL_Surface *overlay;
    int x, y;

    SDL_RenderClear(sdl->renderer);

    overlay = SDL_CreateRGBSurface(0, RES_X, RES_Y, 32,
        0xFF000000, 0x00FF0000, 0x0000FF00, 0x000000FF);

    if (overlay) {
        SDL_LockSurface(overlay);
        for (y = 0; y < RES_Y; y++) {
            for (x = 0; x < RES_X; x++) {
                Uint32 color = get_img_color(source, x, y);
                img_pix_put(overlay, x, y,
                    color + (((255 - i * 4) * !f + ((i * 4) % 256) * f) << 24));
            }
        }
        SDL_UnlockSurface(overlay);

        SDL_Texture *texture = SDL_CreateTextureFromSurface(sdl->renderer, overlay);
        SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
        SDL_RenderCopy(sdl->renderer, texture, NULL, NULL);

        SDL_DestroyTexture(texture);
        SDL_FreeSurface(overlay);
    }

    SDL_RenderPresent(sdl->renderer);
}

void render_intro2(t_sdl *sdl)
{
    SDL_Surface *temp_surface1 = SDL_CreateRGBSurface(0, RES_X, RES_Y, 32,
        0xFF000000, 0x00FF0000, 0x0000FF00, 0x000000FF);
    SDL_Surface *temp_surface2 = SDL_CreateRGBSurface(0, RES_X, RES_Y, 32,
        0xFF000000, 0x00FF0000, 0x0000FF00, 0x000000FF);

    if (temp_surface1 && temp_surface2) {
        if (i < 64 * 2)
            render_intr(sdl, temp_surface1);
        else
            render_intr(sdl, temp_surface2);
    }

    SDL_FreeSurface(temp_surface1);
    SDL_FreeSurface(temp_surface2);

    i++;
    if (i == 64)
        f = 1;
    if (i == 64 * 2)
        f = 0;
    if (i == 64 * 3) {
        i = 0;
        f = 0;
        data.mouse.clicked = 0;
        data.mode = SETTING;
    }
}

void paint_img2(t_img *img, int x_w, int y_w, int color)
{
    SDL_Surface *temp_surface = SDL_CreateRGBSurface(0, img->width, img->height, 32,
        0xFF000000, 0x00FF0000, 0x0000FF00, 0x000000FF);
    SDL_Texture* img2_texture = SDL_CreateTexture(data.sdl.renderer, SDL_PIXELFORMAT_ARGB8888,
        SDL_TEXTUREACCESS_STREAMING, img->width, img->height);

    if (temp_surface && img2_texture) {
        for (int y = 0; y < img->height; y++) {
            for (int x = 0; x < img->width; x++) {
                Uint32 pixel_color = get_img_color(temp_surface, x, y);
                if (pixel_color != 0xff000000 && color >= 2)
                    set_pixel(img2_texture, x, y, 0xffffff * (mm % 200 < 100) + 0xff0000 * (mm % 200 >= 100));
                else if (pixel_color != 0xff000000 && color)
                    set_pixel(img2_texture, x, y, 0xff0000);
                else
                    set_pixel(img2_texture, x, y, pixel_color);
            }
        }
        SDL_Rect dest = {x_w, y_w, img->width, img->height};
        SDL_RenderCopy(data.sdl.renderer, img2_texture, NULL, &dest);
    }

    SDL_FreeSurface(temp_surface);
    SDL_DestroyTexture(img2_texture);
    mm++;
}

// Function declarations for the missing functions
void render_setting(t_sdl *sdl);
void render_setting2(t_sdl *sdl);
void animate_sett_in(t_sdl *sdl);
void animate_sett_out(t_sdl *sdl);
void render_control(t_sdl *sdl);
void render_map(t_sdl *sdl);
void render_game(t_data *data);

int rendering(void *d)
{
    (void)d;

    if (data.mouse.clicked == 128) {
        i = 0;
        f = 0;
        data.mouse.clicked = 0;
        data.mode = INTRO2;
    }

    SDL_RenderClear(data.sdl.renderer);

    switch(data.mode) {
        case INTRO:
            render_intro(&data.sdl);
            break;
        case INTRO1:
            render_intro1(&data.sdl);
            break;
        case INTRO2:
            render_intro2(&data.sdl);
            break;
        case SETTING:
            render_setting(&data.sdl);
            break;
        case SETTING2:
            render_setting2(&data.sdl);
            break;
        case ANIMATE_SETT2_IN:
            animate_sett_in(&data.sdl);
            break;
        case ANIMATE_SETT2_OUT:
            animate_sett_out(&data.sdl);
            break;
        case S_CONTROL:
            render_control(&data.sdl);
            break;
        case MAP_MODE:
            render_map(&data.sdl);
            break;
        case GAME:
            data.intro.map = 0;
            render_game(&data);
            break;
        default:
            break;
    }

    if (data.mouse.x != 10000 && data.mode != MAP_MODE && data.mode != GAME) {
        SDL_Rect mouseRect = {
            .x = data.mouse.x,
            .y = data.mouse.y,
            .w = 32,  // Default width for mouse cursor
            .h = 32   // Default height for mouse cursor
        };
        SDL_RenderCopy(data.sdl.renderer, data.mouse.img, NULL, &mouseRect);
    }

    SDL_RenderPresent(data.sdl.renderer);
    return 0;
}

