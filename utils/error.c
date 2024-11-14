#include "../Headers/TRODO.h"
#include <SDL2/SDL.h>
#include <unistd.h>

void error(char *str, int exit_code) {
    write(STDERR_FILENO, "\033[0;33m", 7);  // Print yellow for error message
    write(STDERR_FILENO, str, ft_strlen(str));
    write(STDERR_FILENO, "\033[0m", 4);  // Reset color

    if (exit_code == 1) {
        SDL_Quit();
        exit(1);
    }
}

int main(int argc, char **argv) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        error("SDL initialization failed: ", 1);
    }

    // Initialize window, renderer, and other game components

    game_loop();  // Run the main game loop

    // Clean up and exit
    SDL_Quit();
    return 0;
}

void game_loop() {
    SDL_Event event;
    int running = 1;

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = 0;
            }
            // Handle other events
        }

        // Render game state and update logic
    }

    ft_close();
}
