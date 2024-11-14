#include "../Headers/TRODO.h"
#include <SDL2/SDL.h>

void replace_tab(char *s)
{
    // Ensure the string is not NULL and process each character
    if (!s)
    {
        SDL_Log("Error: NULL pointer passed to replace_tab");
        return;
    }

    while (*s)
    {
        if (*s == '\t')  // If it's a tab character, replace it with a space
            *s = ' ';
        s++;
    }
}

int check_all_spaces(char *s)
{
    // Ensure the string is not NULL
    if (!s)
    {
        SDL_Log("Error: NULL pointer passed to check_all_spaces");
        return 0;  // Return false (0) for NULL input
    }

    // Skip all leading spaces
    while (*s && *s == ' ')
        s++;

    // If the string is empty after skipping spaces, return true (0)
    return (*s == '\0');
}
