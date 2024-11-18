#include "../Headers/TRODO.h"
#include <SDL2/SDL.h>

size_t ft_strlen(const char *str)
{
    size_t len;
    if (!str)
    {
        SDL_Log("Error: NULL pointer passed to ft_strlen");
        return (0);
    }
    len = 0;
    while (str[len])
        len++;
    return (len);
}

size_t ft_strlen2(char **str)
{
    size_t len;
    if (!str)
    {
        SDL_Log("Error: NULL pointer passed to ft_strlen2");
        return (0);
    }
    len = 0;
    while (str[len])
        len++;
    return (len);
}}
	len = 0;
	while (str[len])
		len++;
	return (len);
}
