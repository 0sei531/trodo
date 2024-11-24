#include "../Headers/TRODO.h"
#include <SDL2/SDL.h>
#include <errno.h>

void error(const char *str, int exit_code) {
    if (!str) return;
    
    const char *prefix = "\033[0;33m";
    const char *suffix = "\033[0m";
    
    if (write(STDERR_FILENO, prefix, 7) == -1 ||
        write(STDERR_FILENO, str, ft_strlen(str)) == -1 ||
        write(STDERR_FILENO, suffix, 4) == -1) {
        perror("Write error");
        exit(1);
    }
    
    if (exit_code == 1) {
        SDL_Quit();
        exit(1);
    }
}
