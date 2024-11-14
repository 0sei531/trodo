#"../Headers/TRODO.h"
#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>

#define WIDTH 800
#define HEIGHT 600

// Struct to hold image data
typedef struct {
    SDL_Texture *texture;
    int width;
    int height;
} t_img;

// Function to put a pixel on an SDL surface
void img_pix_put(SDL_Surface *surface, int x, int y, int color) {
    Uint32 *pixels = (Uint32 *)surface->pixels;
    pixels[(y * surface->w) + x] = color;
}

// Function to load an image and convert it to texture
t_img load_texture(SDL_Renderer *renderer, const char *path) {
    t_img img;
    SDL_Surface *surface = SDL_LoadBMP(path); // Using SDL2 function to load BMP files
    if (!surface) {
        printf("Error loading BMP: %s\n", SDL_GetError());
        exit(1);
    }

    img.texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (!img.texture) {
        printf("Error creating texture: %s\n", SDL_GetError());
        SDL_FreeSurface(surface);
        exit(1);
    }

    img.width = surface->w;
    img.height = surface->h;
    SDL_FreeSurface(surface); // Free the surface as it's no longer needed

    return img;
}

// Function to render an image
void render_texture(SDL_Renderer *renderer, t_img *img, int x, int y) {
    SDL_Rect dest = {x, y, img->width, img->height};
    SDL_RenderCopy(renderer, img->texture, NULL, &dest); // Render the texture
}

int main() {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("SDL_Init Error: %s\n", SDL_GetError());
        return 1;
    }

    // Create the window
    SDL_Window *window = SDL_CreateWindow("Cub3D", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
    if (!window) {
        printf("SDL_CreateWindow Error: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    // Create the renderer
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        printf("SDL_CreateRenderer Error: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    // Load texture (you should replace "image.bmp" with the actual image path)
    t_img img = load_texture(renderer, "image.bmp");

    int running = 1;
    SDL_Event event;

    // Main loop
    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = 0;
            }
        }

        SDL_RenderClear(renderer); // Clear the screen

        // Render the texture at position (100, 100)
        render_texture(renderer, &img, 100, 100);

        SDL_RenderPresent(renderer); // Present the rendered content
    }

    // Cleanup
    SDL_DestroyTexture(img.texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
