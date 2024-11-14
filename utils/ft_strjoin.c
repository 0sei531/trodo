#include "../Headers/TRODO.h"
#include <SDL2/SDL.h>

void	fill(char *s, char *filler, int start)
{
	int	i;
	int	j;

	i = 0;
	j = start;
	while (filler[i])
		s[j++] = filler[i++];
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*str;

	if (!s2)
	{
		// Log error if s2 is NULL
		SDL_Log("Error: s2 is NULL in ft_strjoin");
		return (NULL);
	}
	if (!s1)
	{
		s1 = malloc(1);
		if (!s1)
		{
			// Log error if memory allocation fails
			SDL_Log("Error: Memory allocation failed for s1 in ft_strjoin");
			return (NULL);
		}
		*s1 = '\0';
	}

	// Allocate memory for the new string
	str = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!str)
	{
		// Log error if memory allocation fails
		SDL_Log("Error: Memory allocation failed for str in ft_strjoin");
		free(s1); // Don't forget to free s1 if allocation fail
		return (NULL);
	}

	// Fill the string with s1 and s2
	fill(str, s1, 0);
	fill(str, s2, ft_strlen(s1));

	// Null-terminate the string
	str[ft_strlen(s1) + ft_strlen(s2)] = '\0';

	// Free the memory of s1 after it has been copied to str
	free(s1);

	return (str);
}
