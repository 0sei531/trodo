#include <SDL2/SDL.h>
#include "../Headers/structs.h"
#include "../Headers/TRODO.h"
#include <SDL2/SDL_mixer.h>

// Define data extension structure using existing types from structs.h
typedef struct {
    t_objects objects;
    t_sound sound;
    t_fov fov;
} t_data_ext;

// Global extension of data
t_data_ext data_ext;

// Function declarations
void paint_img(SDL_Texture **texture, SDL_Rect *rect, int width, int height);

void calculateTime(void) {
    if (data_ext.objects.t1 > 9) {
        data_ext.objects.t1 = 0;
        data_ext.objects.t2++;
    }
    if (data_ext.objects.t2 > 5) {
        data_ext.objects.t2 = 0;
        data_ext.objects.t3++;
    }
    if (data_ext.objects.t3 > 3 && data_ext.objects.t4 == 2) {
        data_ext.objects.t3 = 0;
        data_ext.objects.t4++;
    }
    if (data_ext.objects.t3 > 9 && data_ext.objects.t4 < 2) {
        data_ext.objects.t3 = 0;
        data_ext.objects.t4++;
    }
    if (data_ext.objects.t4 > 2) {
        data_ext.objects.t4 = 0;
    }
}

void handle_mouse_motion(SDL_Event *event, t_data *data_ptr) {
    int x, y;
    (void)event;
    SDL_GetMouseState(&x, &y);
    data_ptr->mouse.x = x;
    data_ptr->mouse.y = y;
}

static void handle_mouse_button(SDL_Event *event, t_data *data_ptr) {
    if (event->button.button == SDL_BUTTON_LEFT) {
        handle_mouse_press(event, data_ptr);
    } else if (event->button.button == SDL_BUTTON_RIGHT) {
        handle_mouse_release(event, data_ptr);
    }
}

void *time_count(void *d) {
    (void)d;
    SDL_Event event;
    t_data *data_ptr = &data;

    while (1) {
        SDL_WaitEvent(&event);
        if (event.type == SDL_MOUSEMOTION) {
            handle_mouse_motion(&event, data_ptr);
        }
        if (event.type == SDL_MOUSEBUTTONDOWN) {
            handle_mouse_button(&event, data_ptr);
        }
        if (data.mode == GAME) {
            data_ext.objects.t1++;
            calculateTime();
            data.keys[999 - SCROLL_UP] = 1;
        }
        SDL_Delay(300);
    }
    return NULL;
}

void set_volume(void) {
    int volume = data.intro.volume / 2;
    Mix_Volume(-1, volume);
}

void *check_sound(void *d) {
    (void)d;
    Mix_Chunk *sound_effect;

    while (1) {
        SDL_Delay(100);
        if (data.intro.up && !data.intro.map) {
            Mix_PlayMusic(Mix_LoadMUS("sound/mini_map2.mp3"), 1);
        }
        if (data_ext.sound.hit) {
            sound_effect = Mix_LoadWAV("sound/hit_sound.mp3");
            if (sound_effect) {
                Mix_PlayChannel(-1, sound_effect, 0);
                Mix_FreeChunk(sound_effect);
            }
            data_ext.sound.hit = 0;
        }
        if (data_ext.sound.scroll) {
            sound_effect = Mix_LoadWAV("sound/gun.mp3");
            if (sound_effect) {
                Mix_PlayChannel(-1, sound_effect, 0);
                Mix_FreeChunk(sound_effect);
            }
            data_ext.sound.scroll = 0;
        }
        if (data_ext.fov.jumping && data.dir.px > 0.6) {
            sound_effect = Mix_LoadWAV("sound/jump.mp3");
            if (sound_effect) {
                Mix_PlayChannel(-1, sound_effect, 0);
                Mix_FreeChunk(sound_effect);
            }
            sound_effect = Mix_LoadWAV("sound/jump_end.mp3");
            if (sound_effect) {
                Mix_PlayChannel(-1, sound_effect, 0);
                Mix_FreeChunk(sound_effect);
            }
        } else if (data_ext.fov.jumping) {
            sound_effect = Mix_LoadWAV("sound/jump.mp3");
            if (sound_effect) {
                Mix_PlayChannel(-1, sound_effect, 0);
                Mix_FreeChunk(sound_effect);
            }
        }
        if (data.keys[data.intro.g_k[9]]) {
            sound_effect = Mix_LoadWAV("sound/run12.mp3");
            if (sound_effect) {
                Mix_PlayChannel(-1, sound_effect, -1);
                SDL_Delay(10);
                int i = 0, br = data_ext.objects.breath;
                while (data.keys[data.intro.g_k[9]] && ++i < 900000 && data_ext.objects.breath > 0) {
                    SDL_Delay(10);
                    data_ext.objects.breath = br - i * 100.0 / 900000.0;
                }
                Mix_HaltChannel(-1);
                Mix_FreeChunk(sound_effect);
            }
            if (!data_ext.objects.breath) {
                data_ext.sound.breath = 1;
                sound_effect = Mix_LoadWAV("sound/breath.mp3");
                if (sound_effect) {
                    Mix_PlayChannel(-1, sound_effect, 0);
                    Mix_FreeChunk(sound_effect);
                }
                data_ext.sound.breath = 0;
            }
        }
        if (!data.door.is_op && !data.door.op) {
            sound_effect = Mix_LoadWAV("sound/door1.mp3");
            if (sound_effect) {
                Mix_PlayChannel(-1, sound_effect, 0);
                Mix_FreeChunk(sound_effect);
            }
        }
        if (data.intro.vol_click) {
            set_volume();
        }
        if (data.intro.lgt_click) {
            paint_img(&data.intro.lt, NULL, RES_X, RES_Y);
        }
        if (data_ext.sound.hover == 1) {
            data_ext.sound.hover++;
            sound_effect = Mix_LoadWAV("sound/hover.mp3");
            if (sound_effect) {
                Mix_PlayChannel(-1, sound_effect, 0);
                Mix_FreeChunk(sound_effect);
            }
        }
        if (data_ext.sound.click == 1) {
            data_ext.sound.click++;
            sound_effect = Mix_LoadWAV("sound/click.wav");
            if (sound_effect) {
                Mix_PlayChannel(-1, sound_effect, 0);
                Mix_FreeChunk(sound_effect);
            }
        }
        if (data.mode == INTRO) {
            Mix_PlayMusic(Mix_LoadMUS("sound/gun_intro1.mp3"), 1);
        }
        if (data.mode == SETTING) {
            Mix_PlayMusic(Mix_LoadMUS("sound/mixkit-epic-orchestra-transition-2290.wav"), 1);
        }
    }
    return NULL;
}
