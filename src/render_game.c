#include <SDL2/SDL.h>
#include "../Headers/structs.h"
#include "../Headers/TRODO.h"

typedef struct s_img {
    SDL_Surface *surface;
    SDL_Texture *texture;
    int x;
    int y;
    int bpp;
    int line_len;
    int endian;
} t_img;

typedef struct s_sdl {
    SDL_Window *win_ptr;
    SDL_Renderer *renderer;
} t_sdl;

// Global variables (preserved from original)
int cnt;
int c;
int ac;
int a;
int i;
int f;
int mm;

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
    path[j++] = 'g';  // Changed from xpm to png
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

void render_intro(t_sdl *sdl)
{
    char path[100];
    t_img img;
    int x, y;

    // Clear screen
    SDL_SetRenderDrawColor(sdl->renderer, 0, 0, 0, 255);
    SDL_RenderClear(sdl->renderer);

    // Load and render intro image
    path_name(path, "img/intro/", i, 10);
    img.surface = IMG_Load(path);
    if (img.surface) {
        img.texture = SDL_CreateTextureFromSurface(sdl->renderer, img.surface);
        SDL_Rect dst = {
            .x = (RES_X - 498) / 2,
            .y = (RES_Y - 280) / 2,
            .w = 498,
            .h = 280
        };
        SDL_RenderCopy(sdl->renderer, img.texture, NULL, &dst);
        SDL_FreeSurface(img.surface);
        SDL_DestroyTexture(img.texture);
    }

    // Create overlay effect
    SDL_Surface *overlay = SDL_CreateRGBSurface(0, 498, 280, 32,
        0xFF000000, 0x00FF0000, 0x0000FF00, 0x000000FF);
    
    if (overlay) {
        SDL_LockSurface(overlay);
        for (y = 0; y < 280; y++) {
            for (x = 0; x < 498; x++) {
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

    // Handle "Press to continue" text
    if (f) {
        SDL_Surface *press_surface = IMG_Load("img/press_to_continue.png");  // Changed from xpm
        if (press_surface) {
            SDL_LockSurface(press_surface);
            for (y = 0; y < 53; y++) {
                for (x = 0; x < 439; x++) {
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

    // Handle fade effect when clicked
    if (data.mouse.clicked) {
        SDL_Surface *fade = SDL_CreateRGBSurface(0, RES_X, RES_Y, 32,
            0xFF000000, 0x00FF0000, 0x0000FF00, 0x000000FF);
        
        if (fade) {
            SDL_LockSurface(fade);
            for (y = 0; y < RES_Y; y++) {
                for (x = 0; x < RES_X; x++) {
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

    SDL_RenderPresent(sdl->renderer);
}

void render_intro1(t_sdl *sdl)
{
    char path[100];
    t_img img;
    int x, y;

    path_name(path, "img/intro1/", mm++, 11);
    SDL_RenderClear(sdl->renderer);
    
    img.surface = IMG_Load(path);
    if (img.surface) {
        img.texture = SDL_CreateTextureFromSurface(sdl->renderer, img.surface);
        SDL_RenderCopy(sdl->renderer, img.texture, NULL, NULL);
        SDL_FreeSurface(img.surface);
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
    if (i < 64 * 2)
        render_intr(sdl, data.intro.int1.surface);
    else
        render_intr(sdl, data.intro.int2.surface);
    
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

void setting_render(t_sdl *sdl, SDL_Surface *source, int x, int y, int type)
{
    int i, j;
    SDL_Surface *overlay;

    overlay = SDL_CreateRGBSurface(0, source->w, source->h, 32,
        0xFF000000, 0x00FF0000, 0x0000FF00, 0x000000FF);
    
    if (overlay) {
        SDL_LockSurface(overlay);
        for (i = 0; i < source->w; i++) {
            for (j = 0; j < source->h; j++) {
                Uint32 color = get_img_color(source, i, j);
                if ((color & 0xFF000000) != 0xFF000000) {
                    if (data.mouse.on_clk[type])
                        img_pix_put(overlay, i, j, color + 0xFFFFFF);
                    else if (data.mouse.on_hov[type])
                        img_pix_put(overlay, i, j, color + 0xFF0000);
                    else
                        img_pix_put(overlay, i, j, color);
                }
            }
        }
        SDL_UnlockSurface(overlay);

        SDL_Texture *texture = SDL_CreateTextureFromSurface(sdl->renderer, overlay);
        SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
        SDL_Rect dst = {
            .x = x,
            .y = y,
            .w = source->w,
            .h = source->h
        };
        SDL_RenderCopy(sdl->renderer, texture, NULL, &dst);
        
        SDL_DestroyTexture(texture);
        SDL_FreeSurface(overlay);
    }
}
typedef struct s_sdl {
    SDL_Window* window;
    SDL_Renderer* renderer;
} t_sdl;

// Update the rendering function
int rendering(void *d) {
    d = NULL;
    if (data.mouse.clicked == 128)
        i = 0,
        f = 0,
        data.mouse.clicked = 0,
        data.mode = INTRO2;

    SDL_RenderClear(data.sdl.renderer);

    if (data.mode == INTRO)
        render_intro();
    if (data.mode == INTRO1)
        render_intro1();
    if (data.mode == INTRO2)
        render_intro2();
    if (data.mode == SETTING)
        render_setting();
    if (data.mode == SETTING2)
        render_setting2();
    if (data.mode == ANIMATE_SETT2_IN)
        animate_sett_in();
    if (data.mode == ANIMATE_SETT2_OUT)
        animate_sett_out();
    if (data.mode == S_CONTROL)
        render_control();
    if (data.mode == G_MAP)
        render_map();
    if (data.mode == GAME)
        data.intro.map = 0,
        render_game();
    else if (data.mouse.x != 10000 && data.mode != G_MAP && data.mode != GAME)
        SDL_RenderCopy(data.sdl.renderer, data.mouse.texture, NULL, &(SDL_Rect){data.mouse.x, data.mouse.y, data.mouse.width, data.mouse.height});
        SDL_RenderCopy(data.sdl.renderer, data.intro.lt.texture, NULL, &(SDL_Rect){0, 0, RES_X, RES_Y});

    SDL_RenderPresent(data.sdl.renderer);
    return (0);
}

// Update the set_pixel function
void set_pixel(SDL_Texture* texture, int x, int y, Uint32 color) {
    int pitch;
    void* pixels;
    if (SDL_LockTexture(texture, NULL, &pixels, &pitch) == 0) {
        ((Uint32*)pixels)[y * (pitch / sizeof(Uint32)) + x] = color;
        SDL_UnlockTexture(texture);
    }
}

// Update the paint_img2 function
void paint_img2(t_img *img, int x_w, int y_w, int color) {
    SDL_Texture* img2_texture = SDL_CreateTexture(data.sdl.renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, img->x, img->y);
    for (int y = 0; y < img->y; y++) {
        for (int x = 0; x < img->x; x++) {
            if ((unsigned int)get_img_color(img, x, y) != 0xff000000 && color >= 2)
                set_pixel(img2_texture, x, y, 0xffffff * (mm % 200 < 100) + 0xff0000 * (mm % 200 >= 100));
            else if ((unsigned int)get_img_color(img, x, y) != 0xff000000 && color)
                set_pixel(img2_texture, x, y, 0xff0000);
            else
                set_pixel(img2_texture, x, y, get_img_color(img, x, y));
        }
    }
    SDL_RenderCopy(data.sdl.renderer, img2_texture, NULL, &(SDL_Rect){x_w, y_w, img->x, img->y});
    SDL_DestroyTexture(img2_texture);
    mm++;
}

// Update the main loop
int main(int argc, char *argv[]) {
    // Initialize SDL2
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        fprintf(stderr, "SDL initialization failed: %s\n", SDL_GetError());
        return 1;
    }

    // Create the SDL window and renderer
    data.sdl.window = SDL_CreateWindow("My Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, RES_X, RES_Y, SDL_WINDOW_SHOWN);
    data.sdl.renderer = SDL_CreateRenderer(data.sdl.window, -1, SDL_RENDERER_ACCELERATED);

    // Load and prepare your assets
    // ...

    // Main loop
    while (1) {
        // Handle events
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                break;
            }
            // Handle other events
        }

        // Render the frame
        rendering(NULL);

        // Delay
        SDL_Delay(16); // Approximately 60 FPS
    }

    // Clean up
    SDL_DestroyRenderer(data.sdl.renderer);
    SDL_DestroyWindow(data.sdl.window);
    SDL_Quit();

    return 0;
}
