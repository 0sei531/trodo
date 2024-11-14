#include "../Headers/TRODO.h"
#include <SDL2/SDL.h>

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	// Check for NULL pointers and log an error if either is NULL
	if (!s1 || !s2)
	{
		SDL_Log("Error: NULL pointer passed to ft_strncmp");
		return (1); // Return non-zero value if either string is NULL
	}

	i = 0;
	while (i < n && (s1[i] || s2[i]))  // Continue as long as there is a character in either string
	{
		if (s1[i] != s2[i])
			return (((unsigned char *)s1)[i] - ((unsigned char *)s2)[i]);  // Return difference if characters differ
		i++;
	}
	return (0);  // Return 0 if the strings are equal within the first n characters
}
