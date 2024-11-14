#include "../Headers/TRODO.h"
#include <SDL2/SDL.h>

char	*ft_strchr(const char *str, int c)
{
	if (!str)
	{
		// Log error if the input string is NULL
		SDL_Log("Error: NULL pointer passed to ft_strchr");
		return (NULL);
	}

	while (*str)
	{
		if (*str == (char)c)
			return ((char *)str);
		str++;
	}
	if (!(char)c)
		return ((char *)str);

	return (NULL); // Return NULL explicitly for case where character is not found
}
