#include <SDL2/SDL.h>
#include "../Headers/structs.h"
#include "../Headers/TRODO.h"
#include <math.h>
#define RES_X 1920
#define RES_Y 1080


void variant_calculate_d(double *cord, double decrease, int angl) {
    while (data.map[(int)(cord[1] + decrease * data.angles.r_sin[angl]) / 50][(int)cord[0] / 50] == '0'
        && data.map[(int)cord[1] / 50][(int)(cord[0] + decrease * data.angles.r_cos[angl]) / 50] == '0'
        && data.map[(int)(cord[1] + decrease * data.angles.r_sin[angl]) / 50][(int)(cord[0] + decrease * data.angles.r_cos[angl]) / 50] == '0') {
        cord[0] += decrease * data.angles.r_cos[angl]; 
        cord[1] += decrease * data.angles.r_sin[angl];
    }
}

void variant_calculate(double *cord, double decrease, int angl) {
    while (data.map[(int)(cord[1] + decrease * data.angles.r_sin[angl]) / 50][(int)cord[0] / 50] != '1'
        && data.map[(int)cord[1] / 50][(int)(cord[0] + decrease * data.angles.r_cos[angl]) / 50] != '1'
        && data.map[(int)(cord[1] + decrease * data.angles.r_sin[angl]) / 50][(int)(cord[0] + decrease * data.angles.r_cos[angl]) / 50] != '1') {
        cord[0] += decrease * data.angles.r_cos[angl];
        cord[1] += decrease * data.angles.r_sin[angl];
    }
}

void init_angles() {
    double r = -30;
    for (int i = 0; i < RES_X; i++) {
        double angl = data.dir.angle + r;
        data.angles.r_cos[i] = cos(angl * M_PI / 180);
        data.angles.r_sin[i] = sin(angl * M_PI / 180);
        data.angles.r_res_cos[i] = cos(r * M_PI / 180);
        r += 0.04;
    }
    data.angles.pl_cos = cos(data.dir.angle * M_PI / 180);
    data.angles.pl_sin = sin(data.dir.angle * M_PI / 180);
    data.angles.pl_cos_plus_90 = cos((data.dir.angle + 90) * M_PI / 180);
    data.angles.pl_sin_plus_90 = sin((data.dir.angle + 90) * M_PI / 180);
    data.angles.cte_tan = tan(30 * M_PI / 180);
}

void set_rays(SDL_Renderer *renderer) {
    double cord[2];
    for (int i = 0; i < RES_X; i++) {
        data.color[0] = 0;
        cord[0] = data.dir.x + 17;
        cord[1] = data.dir.y + 17;
        data.indx = i;

        variant_calculate_d(cord, 45, i);
        variant_calculate_d(cord, 20, i);
        variant_calculate_d(cord, 10, i);
        variant_calculate_d(cord, 1, i);
        variant_calculate_d(cord, 0.1, i);

        data.door.hit_wall = 0;

        if (data.map[(int)(cord[1] + data.angles.r_sin[i]) / 50][(int)cord[0] / 50] == 'H' || 
            data.map[(int)cord[1] / 50][(int)(cord[0] + data.angles.r_cos[i]) / 50] == 'H') {
            data.door.cord[0] = (int)cord[0];
            data.door.cord[1] = (int)cord[1];
            data.color[0] = 1;
            data.door.is_op = !(fabs(cord[0] - data.dir.x - 17) < 90 && fabs(cord[1] - data.dir.y - 17) < 90);

            // Door collision handling
            if (data.map[(int)cord[1] / 50][(int)(cord[0] + data.angles.r_cos[i]) / 50] == 'H' && cord[0] + data.angles.r_cos[i] > cord[0])
                data.door.color[1] = (int)cord[1];
            else if (data.map[(int)cord[1] / 50][(int)(cord[0] + data.angles.r_cos[i]) / 50] == 'H' && cord[0] + data.angles.r_cos[i] < cord[0])
                data.door.color[1] = (int)cord[1];
            else if (data.map[(int)(cord[1] + data.angles.r_sin[i]) / 50][(int)cord[0] / 50] == 'H' && cord[1] + data.angles.r_sin[i] > cord[1])
                data.door.color[1] = (int)cord[0];
            else if (data.map[(int)(cord[1] + data.angles.r_sin[i]) / 50][(int)cord[0] / 50] == 'H' && cord[1] + data.angles.r_sin[i] < cord[1])
                data.door.color[1] = (int)cord[0];

            data.door.rays[i] = sqrt((cord[0] - (double)data.dir.x - 17)*(cord[0] - (double)data.dir.x - 17) + 
                                      (cord[1] - (double)data.dir.y - 17)*(cord[1] - (double)data.dir.y - 17)) * data.angles.r_res_cos[i];

            variant_calculate(cord, 45, i);
            variant_calculate(cord, 20, i);
            variant_calculate(cord, 10, i);
            variant_calculate(cord, 1, i);
            variant_calculate(cord, 0.1, i);

            data.door.hit_wall = data.map[(int)(cord[1]) / 50][(int)(cord[0]) / 50] == 'H';
        }

        SDL_RenderDrawLine(renderer, cord[0], cord[1], cord[0] + 100, cord[1] + 100);

        if (data.map[(int)cord[1] / 50][(int)(cord[0] + data.angles.r_cos[i]) / 50] == '1' && cord[0] + data.angles.r_cos[i] > cord[0])
            data.color[1] = (int)cord[1];
        else if (data.map[(int)cord[1] / 50][(int)(cord[0] + data.angles.r_cos[i]) / 50] == '1' && cord[0] + data.angles.r_cos[i] < cord[0])
            data.color[1] = (int)cord[1];
        else if (data.map[(int)(cord[1] + data.angles.r_sin[i]) / 50][(int)cord[0] / 50] == '1' && cord[1] + data.angles.r_sin[i] > cord[1])
            data.color[1] = (int)cord[0];
        else if (data.map[(int)(cord[1] + data.angles.r_sin[i]) / 50][(int)cord[0] / 50] == '1' && cord[1] + data.angles.r_sin[i] < cord[1])
            data.color[1] = (int)cord[0];

        data.rays[i] = sqrt((cord[0] - (double)data.dir.x - 17)*(cord[0] - (double)data.dir.x - 17) + 
                             (cord[1] - (double)data.dir.y - 17)*(cord[1] - (double)data.dir.y - 17)) * data.angles.r_res_cos[i];

        data.cord = cord;
        data.design = data.door.map[(int)(cord[1] - data.angles.r_sin[i]) / 50][(int)(cord[0] - data.angles.r_cos[i]) / 50];

        if (i <= RES_X)
            cast_to_3d(i - 1);
    }
    data.light++;
    if (data.light >= 600)
        data.light = 0;
}


typedef struct {
    double x;
    double y;
    int motion;
    int frm;
    int width;
} Enemy;

typedef struct {
    SDL_Texture *frm[32];
    double x;
    double y;
} Motion;

typedef struct {
    Enemy enemy[32];
    Motion motion[8];
    double dir;
    double angles;
    double cte_tan;
    double ph;
    int c;
    char color_maping[RES_Y][RES_X];
    SDL_Texture img;
} GameData;

GameData data;

void img_pix_put(SDL_Renderer *renderer, SDL_Texture *texture, int x, int y, uint32_t color) {
    void *texture_pixels;
    int texture_pitch;

    SDL_LockTexture(texture, NULL, &texture_pixels, &texture_pitch);
    uint32_t *pixels = (uint32_t *)texture_pixels;

    if (x >= 0 && y >= 0 && x < RES_X && y < RES_Y) {
        pixels[y * RES_X + x] = color;
    }
    
    SDL_UnlockTexture(texture);
}

uint32_t get_img_color(SDL_Texture *texture, int x, int y) {
    uint32_t color = 0;
    void *texture_pixels;
    int texture_pitch;

    SDL_LockTexture(texture, NULL, &texture_pixels, &texture_pitch);
    uint32_t *pixels = (uint32_t *)texture_pixels;

    if (x >= 0 && y >= 0 && x < RES_X && y < RES_Y) {
        color = pixels[y * RES_X + x];
    }

    SDL_UnlockTexture(texture);
    return color;
}

void paint_img3(SDL_Renderer *renderer, SDL_Texture *img, SDL_Texture *img2) {
    int x, y;
    
    // Render img2 to img
    for (y = -1; ++y < RES_Y - (data.aim + data.zoom) * 12;) {
        for (x = -1; ++x < RES_X - (data.aim + data.zoom) * 16;) {
            img_pix_put(renderer, img, x, y, get_img_color(img2, x + (data.aim + data.zoom) * 16, y + (data.aim + data.zoom) * 12));
        }
    }

    // Render img to img2
    for (y = -1; ++y < RES_Y; ) {
        for (x = -1; ++x < RES_X;) {
            img_pix_put(renderer, img2, x, y, get_img_color(img, ((RES_X - (data.aim + data.zoom) * 32) * x) / RES_X, ((RES_Y - (data.aim + data.zoom) * 24) * y) / RES_Y));
        }
    }
}

uint32_t get_enemy_color(double x, double y, int i) {
    SDL_Texture *img = &(data.motion[data.enemy[i].motion].frm[data.enemy[i].frm].texture);
    int pixel_x, pixel_y;

    // Handle different enemy animations
    switch (data.enemy[i].motion) {
        case 0: case 4:
            pixel_x = round(x);
            pixel_y = round(y * (551.0 / 64.0)) - 25;
            if (pixel_y < 0 || pixel_y >= img->h) return 0xff000000;
            return get_img_color(img, pixel_x, pixel_y);
        case 5:
            return get_img_color(img, round(x * (300.0 / img->w)) + 80, round(y * (380.0 / 64.0)) + 50);
        case 6:
            return get_img_color(img, round(x * (390.0 / img->w)), round(y * (450.0 / 64.0)) + 70);
        case 1:
            pixel_y = round(y * (591.0 / 64.0)) - 60;
            if (pixel_y < 0) return 0xff000000;
            return get_img_color(img, round(x), pixel_y);
        default:
            return get_img_color(img, round(x), round(y * (380.0 / 64.0)) + 50);
    }
}

void cast_to_3d_for_enemies(SDL_Renderer *renderer, int start_x, int i, double dist) {
    int j, forward, forward2;
    unsigned int color;
    double img_x, img_y;

    img_x = data.motion[data.enemy[i].motion].frm[data.enemy[i].frm].x;
    img_y = data.motion[data.enemy[i].motion].frm[data.enemy[i].frm].y;

    if (!dist) dist = 1;
    dist = round((50 * (RES_X / 2) / data.angles.cte_tan) / dist);
    forward = (RES_Y / 2 - dist * (data.dir.ph - 0.1)) - data.c;
    forward2 = forward;

    if (forward < 0) forward = 0;
    if (forward > RES_Y) forward = RES_Y;

    int start = start_x - data.enemy[i].width / 2;
    data.enemy[i].width = dist - 170 * ((img_y / img_x) / dist) + 800 * (data.enemy[i].motion == 2) + 580 * (data.enemy[i].motion == 3) + 200 * (data.enemy[i].motion == 4);

    while (++start < start_x + data.enemy[i].width / 2 && start < 1500) {
        if (start >= 0 && dist > data.rays[start]) {
            for (j = forward; (int)(64 / dist * (j - forward2)) < 64 && j < RES_Y; j++) {
                color = get_enemy_color((start - start_x + data.enemy[i].width / 2.0) * (img_x / data.enemy[i].width), (64 / dist * ((j - forward2))), i);
                if (color < 0xff000000 && data.color_maping[j][start] != 'G' && data.color_maping[j][start] != '*') {
                    data.color_maping[j][start] = '*';
                    img_pix_put(renderer, &data.img, start, j, color);
                }
            }
        }
    }
}

void health_left_for_enemy(SDL_Renderer *renderer, SDL_Texture *img, int health) {
    void *texture_pixels;
    int texture_pitch;
    uint32_t *pixels;

    // Lock the texture for pixel manipulation
    SDL_LockTexture(img, NULL, &texture_pixels, &texture_pitch);
    pixels = (uint32_t *)texture_pixels;

    int i, j;

    // Draw the circular background and health status
    for (i = -1; ++i < 20;) {
        for (j = -1; ++j < 40;) {
            if ((i - 20) * (i - 20) + (j - 20) * (j - 20) - 21 * 21 > 0)
                pixels[j * 40 + i] = 0xff000000;  // Black background
            else if ((i - 20) * (i - 20) + (j - 20) * (j - 20) - 10 * 10 > -2)
                pixels[j * 40 + i] = 0;  // Transparent
            else
                // Draw health status (red to dark red)
                pixels[j * 40 + i] = 0xaa0000 * ((i - 10) <= health) + 0x700000 * ((i - 10) > health);
        }
    }

    // Draw the health bar extension
    i--;
    for (; ++i < 1000;) {
        for (j = 9; ++j < 30;) {
            pixels[j * 40 + i] = 0xaa0000 * ((i - 10) <= health) + 0x700000 * ((i - 10) > health);
        }
    }

    // Draw the right side of the health bar circle
    i--;
    for (; ++i < 1020;) {
        for (j = -1; ++j < 40;) {
            if ((i - 1000) * (i - 1000) + (j - 20) * (j - 20) - 21 * 21 > 0)
                pixels[j * 40 + i] = 0xff000000;  // Black background
            else if ((i - 1000) * (i - 1000) + (j - 20) * (j - 20) - 10 * 10 > -2)
                pixels[j * 40 + i] = 0;  // Transparent
            else
                // Draw health status (red to dark red)
                pixels[j * 40 + i] = 0xaa0000 * ((i - 10) <= health) + 0x700000 * ((i - 10) > health);
        }
    }

    // Unlock the texture after modifications
    SDL_UnlockTexture(img);
}


void set_char_to_win(SDL_Renderer *renderer, SDL_Texture *player_texture, SDL_Texture *health_texture, SDL_Texture *enemy_texture, SDL_Texture *crosshair_texture, SDL_Texture *lose_texture) {
   // Clear screen, update enemies, sort by distance
   SDL_RenderClear(renderer);
   set_rays();
   sort_enemies();

   // Draw health bar if enabled
   if (data.show_health)
       health_left_for_enemy(&data.health_enm, data.enemy[0].health);

   // Draw crosshair if present
   if (data.aim)
       paint_img3(&data.img2, &data.img);

   // Render game objects
   SDL_RenderCopy(renderer, data.img.mlx_img, NULL, NULL);
   SDL_RenderCopy(renderer, data.img3.mlx_img, NULL, &(SDL_Rect){RES_X / 3 * 2, 0, data.img3.x, data.img3.y});
   SDL_RenderCopy(renderer, player_texture, NULL, &(SDL_Rect){MX, MY, data.mlx.player_w, data.mlx.player_h});

   // Draw time-related images
   int x = RES_X - 142;
   for (int i = 0; i < 4; i++) {
       SDL_RenderCopy(renderer, data.objects.time[data.objects.t4 - i].mlx_img, NULL, &(SDL_Rect){x, 30, 30, 30});
       x += 30;
   }

   // Draw bullet count
   int bx = RES_X - 242;
   SDL_RenderCopy(renderer, data.nums[data.gun[data.objects.w].case_bullet / 10].mlx_img, NULL, &(SDL_Rect){bx + 17 * 2, 175, 17, 17});
   SDL_RenderCopy(renderer, data.nums[data.gun[data.objects.w].case_bullet % 10].mlx_img, NULL, &(SDL_Rect){bx + 17, 175, 17, 17});
   SDL_RenderCopy(renderer, data.sl, NULL, &(SDL_Rect){bx, 175, 17, 17});
   SDL_RenderCopy(renderer, data.nums[data.gun[data.objects.w].bullet / 10].mlx_img, NULL, &(SDL_Rect){bx - 17, 175, 17, 17});
   SDL_RenderCopy(renderer, data.nums[data.gun[data.objects.w].bullet % 10].mlx_img, NULL, &(SDL_Rect){bx - 17 * 2, 175, 17, 17});

   // Draw crosshair
   SDL_RenderCopy(renderer, crosshair_texture, NULL, &(SDL_Rect){RES_X / 2 - 20, RES_Y / 2 - 20, 40, 40});

   // Draw enemy health bar if enabled
   if (data.show_health)
       SDL_RenderCopy(renderer, health_texture, NULL, &(SDL_Rect){150, RES_Y - 100, data.health_enm.x, data.health_enm.y});

   // Draw blood hit effect if conditions met
   if (data.enemy[0].frm > 10 && data.enemy[0].frm < 30 + 20 * (data.enemy[0].motion == 4) && data.enemy[0].motion > 1 && data.enemy[0].motion < 5)
       SDL_RenderCopy(renderer, data.blood_hit2.mlx_img, NULL, NULL);

   // Draw 'lose' screen if health is zero
   if (data.objects.health <= 0)
       SDL_RenderCopy(renderer, lose_texture, NULL, &(SDL_Rect){(RES_X - data.lose.x) / 2, (RES_Y - data.lose.y) / 2, data.lose.x, data.lose.y});

   // Handle death animation
   if (data.objects.health <= 0 && data.death < 200) {
       data.c += 25 * (data.c + 25 < RES_Y - 200);
       data.death++;
       if (data.dir.ph < 0.9) data.dir.ph += 0.05;
       if (data.death < 20) { data.speed = -6; up(); }
   }

   SDL_RenderPresent(renderer);
}


void load_key_images() {
    char path[50];
    SDL_Surface *tmp_surface;
    SDL_Texture *tmp_texture;

    strcpy(path, "img/keys/?.xpm");
    for (int i = 0; i < 26; i++) {
        path[9] = 'A' + i;
        tmp_surface = IMG_Load(path);
        if (tmp_surface != NULL) {
            data.intro.keys[KEY_A + i] = SDL_CreateTextureFromSurface(data.sdl_renderer, tmp_surface);
            SDL_FreeSurface(tmp_surface);
        }
    }

    data.intro.keys[UP] = IMG_Load("img/keys/up.xpm");
    data.intro.keys[DOWN] = IMG_Load("img/keys/down.xpm");
    data.intro.keys[LEFT] = IMG_Load("img/keys/left.xpm");
    data.intro.keys[RIGHT] = IMG_Load("img/keys/right.xpm");
    data.intro.keys[TAB] = IMG_Load("img/keys/tab.xpm");
    data.intro.keys[SHIFT] = IMG_Load("img/keys/shift.xpm");
    data.intro.keys[CAPS] = IMG_Load("img/keys/caps.xpm");
    data.intro.keys[SPACE] = IMG_Load("img/keys/space.xpm");
    data.intro.keys[ENTER] = IMG_Load("img/keys/enter.xpm");
    data.intro.keys[CONTROL] = IMG_Load("img/keys/ctrl.xpm");
    data.intro.keys[M_LEFT_CLICK] = IMG_Load("img/keys/l_click.xpm");
    data.intro.keys[M_RIGHT_CLICK] = IMG_Load("img/keys/r_click.xpm");
}

void load_guide_images() {
    static const char *guide_paths[] = {
        "img/str/fov.xpm", "img/str/arrows.xpm", "img/str/mouse.xpm",
        "img/str/l_ch1.xpm", "img/str/r_ch1.xpm", "img/str/up.xpm",
        "img/str/down.xpm", "img/str/left.xpm", "img/str/right.xpm",
        "img/str/jump.xpm", "img/str/crouch.xpm", "img/str/attack.xpm",
        "img/str/aim.xpm", "img/str/run.xpm", "img/str/setting.xpm",
        "img/str/map.xpm"
    };

    for (int i = 0; i < 16; i++) {
        data.intro.guide[i].mlx_img = IMG_Load(guide_paths[i]);
        if (data.intro.guide[i].mlx_img != NULL) {
            data.intro.guide[i].mlx_texture = SDL_CreateTextureFromSurface(data.sdl_renderer, data.intro.guide[i].mlx_img);
            SDL_FreeSurface(data.intro.guide[i].mlx_img);
        }
    }
}

void init_img_control() {
    load_key_images();
    load_guide_images();
}

void put_color(int i, int j, char p) {
    if (data.door.map[i][j] != '0') return;
    data.door.map[i][j] = p;
    put_color(i + 1, j, p);
    put_color(i - 1, j, p);
    put_color(i, j + 1, p);
    put_color(i, j - 1, p);
}


void put_color(int i, int j, char p) {
    if (data.door.map[i][j] != '0')
        return;
    data.door.map[i][j] = p;
    put_color(i + 1, j, p);
    put_color(i - 1, j, p);
    put_color(i, j + 1, p);
    put_color(i, j - 1, p);
}

void init_virtual_map() {
    int i, j;
    char p = 'A';

    for (i = 0; data.door.map[i]; i++) {
        for (j = 0; data.door.map[i][j]; j++) {
            if (data.door.map[i][j] == '0')
                put_color(i, j, p++);
        }
        if (p > 'H')
            p = 'A';
    }
}

int create_window(const char *title, int width, int height) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return 0;
    }

    SDL_Window *window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
    if (!window) {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        SDL_Quit();
        return 0;
    }

    return 1;
}

SDL_Renderer *create_renderer(SDL_Window *window) {
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return NULL;
    }
    return renderer;
}

void load_textures(SDL_Renderer *renderer) {
    SDL_Texture *texture = IMG_LoadTexture(renderer, "img/ceill.xpm");
    // Load other textures here
}

void set_minimap() {
    if (!create_window("Map", RES_X, RES_Y))
        return;

    SDL_Renderer *renderer = create_renderer(window);
    if (!renderer)
        return;

    load_textures(renderer);

    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
