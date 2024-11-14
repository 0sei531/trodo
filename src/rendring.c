#include "../Headers/TRODO.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

void calculateTime() {
    if (data.objects.t1 > 9) {
        data.objects.t1 = 0;
        data.objects.t2++;
    }
    if (data.objects.t2 > 5) {
        data.objects.t2 = 0;
        data.objects.t3++;
    }
    if (data.objects.t3 > 3 && data.objects.t4 == 2) {
        data.objects.t3 = 0;
        data.objects.t4++;
    }
    if (data.objects.t3 > 9 && data.objects.t4 < 2) {
        data.objects.t3 = 0;
        data.objects.t4++;
    }
    if (data.objects.t4 > 2) {
        data.objects.t4 = 0;
    }
}

void handleMouseMotion(SDL_Event *event) {
    int x, y;
    SDL_GetMouseState(&x, &y);
    // Handle mouse motion
}

void handleMouseButton(SDL_Event *event) {
    if (event->button.button == SDL_BUTTON_LEFT) {
        mouse_press(NULL);
    } else if (event->button.button == SDL_BUTTON_RIGHT) {
        mouse_release(NULL);
    }
}

void *timeCount(void *d) {
    d = NULL;
    SDL_Event event;
    while (1) {
        SDL_WaitEvent(&event);
        if (event.type == SDL_MOUSEMOTION) {
            handleMouseMotion(&event);
        }
        if (event.type == SDL_MOUSEBUTTONDOWN) {
            handleMouseButton(&event);
        }
        if (data.mode == GAME) {
            data.objects.t1++;
            calculateTime();
            data.keys[999 - SCROLL_UP] = 1;
        }
        SDL_Delay(300);
    }
    return NULL;
}

void setVolume() {
    int volume = data.intro.volume / 2;
    Mix_Volume(-1, volume);
}

void *checkSound(void *d) {
    d = NULL;
    while (1) {
        SDL_Delay(100);
        if (data.intro.up && !data.intro.map) {
            Mix_PlayMusic(Mix_LoadMUS("sound/mini_map2.mp3"), 1);
        }
        if (data.sound.hit) {
            Mix_PlaySound(Mix_LoadWAV("sound/hit_sound.mp3"), 0);
            data.sound.hit = 0;
        }
        if (data.sound.scroll) {
            Mix_PlaySound(Mix_LoadWAV("sound/gun.mp3"), 0);
            data.sound.scroll = 0;
        }
        if (data.fov.jumping && data.dir.ph > 0.6) {
            Mix_PlaySound(Mix_LoadWAV("sound/jump.mp3"), 0);
            Mix_PlaySound(Mix_LoadWAV("sound/jump_end.mp3"), 0);
        } else if (data.fov.jumping) {
            Mix_PlaySound(Mix_LoadWAV("sound/jump.mp3"), 0);
        }
        if (data.keys[data.intro.g_k[9]]) {
            Mix_PlaySound(Mix_LoadWAV("sound/run12.mp3"), -1);
            SDL_Delay(10);
            int i = 0, br = data.objects.breath;
            while (data.keys[data.intro.g_k[9]] && ++i < 900000 && data.objects.breath > 0) {
                SDL_Delay(10);
                data.objects.breath = br - i * 100.0 / 900000.0;
            }
            Mix_HaltChannel(-1);
            if (!data.objects.breath) {
                data.sound.breath = 1;
                Mix_PlaySound(Mix_LoadWAV("sound/breath.mp3"), 0);
                data.sound.breath = 0;
            }
        }
        if (!data.door.is_op && !data.door.op) {
            Mix_PlaySound(Mix_LoadWAV("sound/door1.mp3"), 0);
        }
        if (data.intro.vol_click) {
            setVolume();
        }
        if (data.intro.lgt_click) {
            paint_color(&data.intro.lt, ((55 + data.intro.light) << 24), RES_X, RES_Y);
        }
        if (data.sound.hover == 1) {
            data.sound.hover++;
            Mix_PlaySound(Mix_LoadWAV("sound/hover.mp3"), 0);
        }
        if (data.sound.click == 1) {
            data.sound.click++;
            Mix_PlaySound(Mix_LoadWAV("sound/click.wav"), 0);
        }
        if (data.mode == INTRO1) {
            Mix_PlayMusic(Mix_LoadMUS("sound/gun_intro1.mp3"), 1);
        }
        if (data.mode == INTRO2) {
            Mix_PlayMusic(Mix_LoadMUS("sound/mixkit-epic-orchestra-transition-2290.wav"), 1);
        }
    }
    return NULL;
}
