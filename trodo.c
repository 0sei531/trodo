#include "Headers/TRODO.h"
#include "Headers/structs.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <math.h>

/* Global variable declaration - definition should be in a separate .c file */
extern t_data data;

/* Local function prototypes */
static int arg_check(int ac, char **av);
static int init_sdl(SDL_Window **window, SDL_Renderer **renderer);
static void print_error(const char *msg);

/* Error handling helper function */
static void print_error(const char *msg) {
    if (msg) {
        ssize_t ret;
        size_t len = ft_strlen(msg);
        
        ret = write(STDERR_FILENO, msg, len);
        if (ret < 0 || (size_t)ret != len) {
            // Handle write error - in this case we can't really print an error 
            // about failing to print an error, so we'll just return
            return;
        }
        
        ret = write(STDERR_FILENO, "\n", 1);
        if (ret < 0 || ret != 1) {
            return;
        }
    }
}

/* Argument validation function */
static int arg_check(int ac, char **av) {
    if (ac != 2) {
        print_error("Error: Invalid number of arguments");
        return 0;
    }

    size_t len = ft_strlen(av[1]);
    if (len < 4 || ft_strncmp(av[1] + len - 4, ".cub", 4) != 0) {
        print_error("Error: Invalid file extension (must be .cub)");
        return 0;
    }

    return 1;
}

/* SDL initialization function */
static int init_sdl(SDL_Window **window, SDL_Renderer **renderer) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        print_error(SDL_GetError());
        return 0;
    }

    *window = SDL_CreateWindow(
        "TRODO",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        800, 600,
        SDL_WINDOW_SHOWN
    );

    if (!*window) {
        print_error(SDL_GetError());
        SDL_Quit();
        return 0;
    }

    *renderer = SDL_CreateRenderer(*window, -1,
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    if (!*renderer) {
        print_error(SDL_GetError());
        SDL_DestroyWindow(*window);
        SDL_Quit();
        return 0;
    }

    // Initialize SDL_image for texture loading
    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
        print_error(IMG_GetError());
        SDL_DestroyRenderer(*renderer);
        SDL_DestroyWindow(*window);
        SDL_Quit();
        return 0;
    }

    return 1;
}

/* Main function */
int main(int ac, char **av) {
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;
    t_map *map = NULL;
    int status = 0;

    // Check command line arguments
    if (!arg_check(ac, av)) {
        return EXIT_FAILURE;
    }

    // Initialize SDL
    if (!init_sdl(&window, &renderer)) {
        return EXIT_FAILURE;
    }

    // Initialize map structure
    init_args(&map);
    if (!map) {
        cleanup_and_exit(window, renderer, NULL);
        return EXIT_FAILURE;
    }

    // Parse map file
    if (!parsing(av[1])) {
        print_error("Error: Failed to parse map file");
        cleanup_and_exit(window, renderer, map);
        return EXIT_FAILURE;
    }

    // Initialize game
    if (!init_game(window, renderer, map)) {
        print_error("Error: Failed to initialize game");
        cleanup_and_exit(window, renderer, map);
        return EXIT_FAILURE;
    }

    // Main game loop
    SDL_Event event;
    int running = 1;

    while (running) {
        // Handle events
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    running = 0;
                    break;
                case SDL_KEYDOWN:
                    handle_key_press(&event, &data);
                    break;
                case SDL_KEYUP:
                    handle_key_release(&event, &data);
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    handle_mouse_press(&event, &data);
                    break;
                case SDL_MOUSEBUTTONUP:
                    handle_mouse_release(&event, &data);
                    break;
                case SDL_MOUSEMOTION:
                    handle_mouse_motion(&event, &data);
                    break;
            }
        }

        // Update game state
        move();

        // Render frame
        render_game(&data);

        // Cap frame rate
        SDL_Delay(1000 / 60);
    }

    // Cleanup and exit
    cleanup_and_exit(window, renderer, map);
    return status;
}
