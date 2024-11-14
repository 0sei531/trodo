#include "../Headers/TRODO.h"
#include <SDL2/SDL.h>

int	ft_strlen(const char *str)
{
	int	len;

	if (!str)
	{
		// Log error if str is NULL
		SDL_Log("Error: NULL pointer passed to ft_strlen");
		return (0);
	}
	len = 0;
	while (str[len])
		len++;
	return (len);
}

int	ft_strlen2(char **str)
{
	int	len;

	if (!str)
	{
		// Log error if str is NULL
		SDL_Log("Error: NULL pointer passed to ft_strlen2");
		return (0);
	}
	len = 0;
	while (str[len])
		len++;
	return (len);
}
