#include "../Headers/TRODO.h"
#include <SDL2/SDL.h>

 char *ft_substr(char const *s, size_t start, size_t len)
{
    size_t  i;
    char    *str;

    // Check for NULL pointer for the input string and log an error
    if (!s)
    {
        SDL_Log("Error: NULL pointer passed to ft_substr");
        return (NULL);  // Return NULL if the input string is NULL
    }

    // If the start index is beyond the length of the string, set len to 0
    if (ft_strlen(s) < start)
        len = 0;

    // If the len requested exceeds the remaining string length, adjust it
    if (len > ft_strlen(s) - start)
        len = ft_strlen(s) - start;

    // Allocate memory for the substring
    str = (char *)malloc(sizeof(char) * (len + 1));
    if (!str)
    {
        SDL_Log("Error: Memory allocation failed in ft_substr");
        return (NULL);  // Return NULL if memory allocation fails
    }

    // Copy the substring into the allocated space
    i = 0;
    while (s[start + i] && i < len)
    {
        str[i] = s[start + i];
        i++;
    }

    // Null-terminate the substring
    str[i] = 0;
    return (str);
}
