#include "../Headers/TRODO.h"
#include <SDL2/SDL.h>
#include "../Headers/structs.h"

int room_a(int side, double x, double y, SDL_Renderer *renderer)
{
    int v = (((int)x / 50) % FLOOR2_SIZE_Y * ((int)y / 50) % FLOOR2_SIZE_Y) % FLOOR2_SIZE_Y;
    int w = (((int)x / 50) % FLOOR2_SIZE_X * ((int)y / 50) % FLOOR2_SIZE_X) % FLOOR2_SIZE_X;
    int v2 = (((int)x / 50) % SUPPORT_SIZE_Y * ((int)y / 50) % SUPPORT_SIZE_Y) % SUPPORT_SIZE_Y;
    int w2 = (((int)x / 50) % SUPPORT_SIZE_X + ((int)y / 50) % SUPPORT_SIZE_X) % SUPPORT_SIZE_X;
    int v3 = (((int)data.cord[0] / 50) % CART1_SIZE_Y + ((int)data.cord[1] / 50) % CART1_SIZE_Y) % CART1_SIZE_Y;
    int w3 = (((int)data.cord[0] / 50) % CART1_SIZE_X + ((int)data.cord[1] / 50) % CART1_SIZE_X) % CART1_SIZE_X;

    if (w2)
    {
        w2 = (w2 + data.light / 10) % SUPPORT_SIZE_X;
        w2 += !w2;
    }

    SDL_Texture *texture;
    SDL_Rect srcRect, destRect;
    switch (side)
    {
        case 1:
            texture = data.assets.texture;
            srcRect.x = ((int)round(y * 10.0 * (64.0 / 500.0)) % 64 + FLOOR2_START__Y + v * 72);
            srcRect.y = ((int)round(x * 10.0 * (64.0 / 500.0)) % 64 + FLOOR2_START__X + w * 72);
            break;
        case -1:
            texture = data.assets.texture;
            srcRect.x = ((int)round(y * 10.0 * (64.0 / 500.0)) % 64 + SUPPORT_START__Y + v2 * 72);
            srcRect.y = ((int)round(x * 10.0 * (64.0 / 500.0)) % 64 + SUPPORT_START__X + w2 * 72);
            break;
        default:
            texture = data.assets.texture;
            srcRect.x = ((int)y + CART1_START__Y + v3 * 72);
            srcRect.y = ((int)round(data.color[1] * 10.0 * (64.0 / 500.0)) % 64 + CART1_START__X + w3 * 72);
            break;
    }

    srcRect.w = 72;
    srcRect.h = 72;

    destRect.x = (int)x;
    destRect.y = (int)y;
    destRect.w = 72;  // Define your width and height as needed
    destRect.h = 72;

    SDL_RenderCopy(renderer, texture, &srcRect, &destRect);
    return 0;
}

int room_b(int side, double x, double y, SDL_Renderer *renderer)
{
    int v = (((int)x / 50) % CONCRETE_SIZE_Y * ((int)y / 50) % CONCRETE_SIZE_Y) % CONCRETE_SIZE_Y;
    int w = (((int)x / 50) % CONCRETE_SIZE_X * ((int)y / 50) % CONCRETE_SIZE_X) % CONCRETE_SIZE_X;
    int v2 = (((int)x / 50) % LIGHT_SIZE_Y * ((int)y / 50) % LIGHT_SIZE_Y) % LIGHT_SIZE_Y;
    int w2 = (((int)x / 50) % LIGHT_SIZE_X + ((int)y / 50) % LIGHT_SIZE_X) % LIGHT_SIZE_X;
    int v3 = (((int)data.cord[0] / 50) % CART2_SIZE_Y + ((int)data.cord[1] / 50) % CART2_SIZE_Y) % CART2_SIZE_Y;
    int w3 = (((int)data.cord[0] / 50) % CART2_SIZE_X + ((int)data.cord[1] / 50) % CART2_SIZE_X) % CART2_SIZE_X;

    if (w2)
        v2 = (v2 + data.light / 10) % LIGHT_SIZE_Y;
    if (side == -1 && !w2 && v2)
        return 0;

    SDL_Texture *texture;
    SDL_Rect srcRect, destRect;
    switch (side)
    {
        case 1:
            texture = data.assets.texture;
            srcRect.x = ((int)round(y * 10.0 * (64.0 / 500.0)) % 64 + CONCRETE_START__Y + v * 72);
            srcRect.y = ((int)round(x * 10.0 * (64.0 / 500.0)) % 64 + CONCRETE_START__X + w * 72);
            break;
        case -1:
            texture = data.assets.texture;
            srcRect.x = ((int)round(y * 10.0 * (64.0 / 500.0)) % 64 + LIGHT_START__Y + v2 * 72);
            srcRect.y = ((int)round(x * 10.0 * (64.0 / 500.0)) % 64 + LIGHT_START__X + w2 * 72);
            break;
        default:
            texture = data.assets.texture;
            srcRect.x = ((int)y + CART2_START__Y + v3 * 72);
            srcRect.y = ((int)round(data.color[1] * 10.0 * (64.0 / 500.0)) % 64 + CART2_START__X + w3 * 72);
            break;
    }

    srcRect.w = 72;
    srcRect.h = 72;

    destRect.x = (int)x;
    destRect.y = (int)y;
    destRect.w = 72;
    destRect.h = 72;

    SDL_RenderCopy(renderer, texture, &srcRect, &destRect);
    return 0;
}
