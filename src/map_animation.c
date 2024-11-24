#include <SDL2/SDL.h>
#include "../Headers/TRODO.h"
#include "../Headers/structs.h"

int get_minimap_color2(int x, int y)
{
    double  c;
    double  s;
    Uint32 color;
    void *pixels;
    int pitch;

    // Use the added map_rotation member
    c = cos((data.dir.angle + data.map_rotation + 90 + 7.2 * (double)data.intro.map * (data.intro.map < 51)) * M_PI / 180);
    s = sin((data.dir.angle + data.map_rotation + 90 + 7.2 * (double)data.intro.map * (data.intro.map < 51)) * M_PI / 180);

    x -= 1345;
    y -= 935;

    double xnew = x * c - y * s + 1345;
    double ynew = x * s + y * c + 935;

    // Use the added map_zoom member
    if (xnew < MX)
        x = (double)data.dir.x - fabs(MX - xnew) * (2 - data.map_zoom) - 16.5;
    else
        x = (double)data.dir.x + fabs(MX - xnew) * (2 - data.map_zoom) - 16.5;
    if (ynew < MY)
        y = (double)data.dir.y - fabs(MY - ynew) * (2 - data.map_zoom) - 16.5;
    else
        y = (double)data.dir.y + fabs(MY - ynew) * (2 - data.map_zoom) - 16.5;

    if (x <= 0 || y <= 0 || y / 50 >= data.h_map || x / 50 >= data.w_map[y / 50])
        return (0xff000000);

        
    // Lock texture for pixel access
    SDL_LockTexture(data.assets.texture, NULL, &pixels, &pitch);
    
    switch (data.door.map[y / 50][x / 50])
    {
        case '1': {
            int tex_x = (int)(x * 64.0 / 50.0) % 64 + FLOOR2_START__X;
            int tex_y = (int)(y * 64.0 / 50.0) % 64 + FLOOR2_START__Y;
            color = *(Uint32*)((Uint8*)pixels + tex_y * pitch + tex_x * 4);
            break;
        }
        case 'A':
            color = 0x36454F;
            break;
        case 'B':
            color = 0x231A1A;
            break;
        case 'C':
            color = 0x645F5F;
            break;
        case 'D':
            color = 0x393801;
            break;
        case 'E': {
            if (data.map[(int)y / 50][(int)x / 50] == '0' && 
                (data.map[(int)y / 50 - 1][(int)x / 50] != data.map[(int)y / 50 + 1][(int)x / 50] || 
                 data.map[(int)y / 50][(int)x / 50 - 1] != data.map[(int)y / 50][(int)x / 50 + 1])) {
                int tex_x = (int)(x * 64.0 / 50.0 + data.light) % 64 + 1680;
                int tex_y = (int)(y * 64.0 / 50.0 + data.light) % 64 + 576;
                color = *(Uint32*)((Uint8*)pixels + tex_y * pitch + tex_x * 4);
            } else {
                int tex_x = (int)(x * 64.0 / 50.0 + data.light) % 64 + 1680;
                int tex_y = (int)(y * 64.0 / 50.0 + data.light) % 64 + 648;
                color = *(Uint32*)((Uint8*)pixels + tex_y * pitch + tex_x * 4);
            }
            break;
        }
        case 'F':
            color = 0xB2BEB5;
            break;
        case 'G':
            color = 0xE5E4E2;
            break;
        default:
            color = 0xff000000;
    }
    
    SDL_UnlockTexture(data.assets.texture);
    return color;
}

void map_1(SDL_Renderer *renderer, t_img img, int r)
{
    int i, j;
    
    // Create texture for the map
    img.texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, 
                                  SDL_TEXTUREACCESS_TARGET, (121 + r) * 2, (121 + r) * 2);
    SDL_SetRenderTarget(renderer, img.texture);

    i = 1345 - 114 - r;
    while (++i < 1345 + 129 + r)
    {
        j = 935 - 116 - r;
        while (++j < 935 + 127 + r)
        {
            if ((X - i + 45)*(X - i + 45) + (Y - j + 40)*(Y - j + 40) - (115 + r) * (115 + r) <= 0)
                SDL_SetRenderDrawColor(renderer, get_minimap_color2(i, j) >> 16 & 0xFF,
                                     get_minimap_color2(i, j) >> 8 & 0xFF,
                                     get_minimap_color2(i, j) & 0xFF,
                                     get_minimap_color2(i, j) >> 24 & 0xFF);
            else if ((X - i + 45)*(X - i + 45) + (Y - j + 40)*(Y - j + 40) - (120 + r) * (120 + r) <= 0)
                SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
            else
                SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
            
            SDL_RenderDrawPoint(renderer, i - 1345 + 113 + r, j - 935 + 115 + r);
        }
    }

    SDL_RenderCopy(renderer, img.texture, NULL, NULL);
    SDL_SetRenderTarget(renderer, NULL);
    SDL_DestroyTexture(img.texture);
}


