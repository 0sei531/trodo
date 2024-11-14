#include <SDL2/SDL.h>
#include "../Headers/TRODO.h"

int get_minimap_color2(int x, int y)
{
    double  c;
    double  s;

    c = cos((data.dir.angle + data.map_rotation + 90 + 7.2 * (double)data.intro.map * (data.intro.map < 51)) * M_PI / 180);
    s = sin((data.dir.angle + data.map_rotation + 90 + 7.2 * (double)data.intro.map * (data.intro.map < 51)) * M_PI / 180);

    x -= 1345;
    y -= 935;

    double xnew = x * c - y * s + 1345;
    double ynew = x * s + y * c + 935;
    
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
    switch (data.door.map[y / 50][x / 50])
    {
        case '1':
            return (*(int *)(data.assets.addr + (((int)(y * 64.0 / 50.0) % 64 + FLOOR2_START__Y) * data.assets.line_len + ((int)(x * 64.0 / 50.0) % 64 + FLOOR2_START__X) * (data.assets.bpp / 8))));        
        case 'A':
            return (0x36454F);
        case 'B':
            return (0x231A1A);
        case 'C':
            return (0x645F5F);
        case 'D':
            return (0x393801);
        case 'E':
            if (data.map[(int)y / 50][(int)x / 50] == '0' && (data.map[(int)y / 50 - 1][(int)x / 50] != data.map[(int)y / 50 + 1][(int)x / 50] || data.map[(int)y / 50][(int)x / 50 - 1] != data.map[(int)y / 50][(int)x / 50 + 1]))
                return (*(int *)(data.assets.addr + (((int)(y * 64.0 / 50.0 + data.light) % 64 + 576) * data.assets.line_len + ((int)(x * 64.0 / 50.0 + data.light) % 64 + 1680) * (data.assets.bpp / 8))));            
            else
                return (*(int *)(data.assets.addr + (((int)(y * 64.0 / 50.0 + data.light) % 64 + 648) * data.assets.line_len + ((int)(x * 64.0 / 50.0 + data.light) % 64 + 1680) * (data.assets.bpp / 8))));                
        case 'F':
            return (0xB2BEB5);
        case 'G':
            return (0xE5E4E2);
        default:
            return (0xff000000);
    }
}

void map_1(SDL_Renderer *renderer, t_img img, int r)
{
    int i, j;

    img.mlx_img = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, (121 + r) * 2, (121 + r) * 2);
    SDL_SetRenderTarget(renderer, img.mlx_img);  // Set target for drawing

    i = 1345 - 114 - r;
    while (++i < 1345 + 129 + r)
    {
        j = 935 - 116 - r;
        while (++j < 935 + 127 + r)
            if ((X - i + 45)*(X - i + 45) + (Y - j + 40)*(Y - j + 40) - (115 + r) * (115 + r) <= 0)
                img_pix_put(&img, i - 1345 + 113 + r, j - 935 + 115 + r, get_minimap_color2(i, j));
            else if ((X - i + 45)*(X - i + 45) + (Y - j  + 40)*(Y - j + 40) - (120 + r) * (120 + r) <= 0)
                img_pix_put(&img, i - 1345 + 113 + r, j - 935 + 115 + r, 0xffffff);
            else
                img_pix_put(&img, i - 1345 + 113 + r, j - 935 + 115 + r, 0xff000000);
    }

    SDL_RenderCopy(renderer, img.mlx_img, NULL, NULL);
    SDL_SetRenderTarget(renderer, NULL);  // Reset to default target
    SDL_DestroyTexture(img.mlx_img);  // Clean up texture after rendering
}

int r;

void *tmp(void *d)
{
    int x, y, i, j;
    t_img *img = (t_img *)d;

    x = 280 + r;
    y = 100 + (2 * r) / 3;
    i = 1345 - 114 - r;
    while (++i < 1345)
    {
        j = 935 - 116 - r;
        while (++j < 935 + 127 + r)
            if ((X - i + 45)*(X - i + 45) + (Y - j + 40)*(Y - j + 40) - 215 * 215 <= 0)
                img_pix_put(img, i - 1345 + 113 + r, j - 935 + 115 + r, get_minimap_color2(i - data.mv_x, j - data.mv_y));
            else if (i > X + 45 - x / 2 && j > Y + 40 - y / 2 && i < X + 45 + x / 2 && j < Y + 40 + y / 2)
                img_pix_put(img, i - 1345 + 113 + r, j - 935 + 115 + r, get_minimap_color2(i - data.mv_x, j - data.mv_y));
            else if ((X - i + 45)*(X - i + 45) + (Y - j  + 40)*(Y - j + 40) - 220 * 220 <= 0)
                img_pix_put(img, i - 1345 + 113 + r, j - 935 + 115 + r, 0xffffff);
            else if (i > X + 45 - x / 2 - 5 && j > Y + 40 - y / 2 - 5 && i < X + 45 + x / 2 + 5 && j < Y + 40 + y / 2 + 5)
                img_pix_put(img, i - 1345 + 113 + r, j - 935 + 115 + r, 0xffffff);
            else
                img_pix_put(img, i - 1345 + 113 + r, j - 935 + 115 + r, 0xff000000);
    }
    return (NULL);
}

void map_2(SDL_Renderer *renderer, t_img img, int r, pthread_t p)
{
    int x, y, i, j;

    img.mlx_img = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, (121 + r) * 2, (121 + r) * 2);
    SDL_SetRenderTarget(renderer, img.mlx_img);  // Set target for drawing

    pthread_create(&p, NULL, tmp, (void *)&img); 
    pthread_join(p, NULL); // Make sure thread completes

    i = 1345 - 114 - r;
    while (++i < 1345 + 129 + r)
    {
        j = 935 - 116 - r;
        while (++j < 935 + 127 + r)
            if ((X - i + 45)*(X - i + 45) + (Y - j + 40)*(Y - j + 40) - (115 + r) * (115 + r) <= 0)
                img_pix_put(&img, i - 1345 + 113 + r, j - 935 + 115 + r, get_minimap_color2(i, j));
            else if ((X - i + 45)*(X - i + 45) + (Y - j + 40)*(Y - j + 40) - (120 + r) * (120 + r) <= 0)
                img_pix_put(&img, i - 1345 + 113 + r, j - 935 + 115 + r, 0xffffff);
            else
                img_pix_put(&img, i - 1345 + 113 + r, j - 935 + 115 + r, 0xff000000);
    }

    SDL_RenderCopy(renderer, img.mlx_img, NULL, NULL);
    SDL_SetRenderTarget(renderer, NULL);  // Reset to default target
    SDL_DestroyTexture(img.mlx_img);  // Clean up texture after rendering
}
