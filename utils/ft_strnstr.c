#include "../Headers/TRODO.h"
#include <SDL2/SDL.h>

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;

	// Check for NULL pointers and log errors using SDL_Log
	if (!haystack || !needle)
	{
		SDL_Log("Error: NULL pointer passed to ft_strnstr");
		return (NULL);  // Return NULL if either haystack or needle is NULL
	}

	i = 0;
	if (!*needle)  // If the needle is empty, return the haystack
		return ((char *)haystack);

	while (haystack[i] && i < len)
	{
		j = 0;
		while (needle[j] && j + i < len && haystack[i + j] == needle[j])
			j++;
		if (!needle[j])  // If all characters of needle are found, return the substring
			return (&((char *)haystack)[i]);
		i++;
	}
	return (NULL);  // Return NULL if needle is not found in the haystack within len
}
