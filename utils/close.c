#include <SDL2/SDL.h>
#include "../Headers/TRODO.h"

void game_loop() {
   SDL_Event event;
   int running = 1;
   while (running) {
       while (SDL_PollEvent(&event)) {
           if (event.type == SDL_QUIT)
               running = 0;
       }
       // Add game logic here
   }
   ft_close();
}

int main() {
   if (SDL_Init(SDL_INIT_VIDEO) < 0) {
       printf("SDL init failed: %s\n", SDL_GetError());
       return 1;
   }
   // Initialize window, renderer, etc.
   game_loop();
   return 0;
}
