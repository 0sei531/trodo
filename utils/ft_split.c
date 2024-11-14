#include "../Headers/TRODO.h"
#include <stdlib.h>

int	count_words(char const *s, char c)
{
	int		count;
	int		i;

	i = 0;
	count = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i] != c && s[i])
			count++;
		while (s[i] != c && s[i])
			i++;
	}
	return (count);
}

char	*init_str(char const *s, char c)
{
	int		i;
	char	*ptr;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	ptr = (char *)malloc(sizeof(char) * (i + 1));
	if (!ptr)
	{
		// If memory allocation fails, print an error and return NULL
		SDL_Log("Memory allocation error in init_str");
		return (NULL);
	}
	ft_memcpy(ptr, s, i);
	ptr[i] = 0;
	return (ptr);
}

char	**ft_split(char const *s, char c)
{
	int		i;
	int		strs_len;
	char	**ptr;

	if (!s)
		return (NULL);
	strs_len = count_words(s, c);
	ptr = (char **)malloc(sizeof(char *) * (strs_len + 1));
	if (!ptr)
	{
		// If memory allocation fails, print an error and return NULL
		SDL_Log("Memory allocation error in ft_split");
		return (NULL);
	}
	i = -1;
	while (++i < strs_len)
	{
		// Skip leading delimiters
		while (s[0] == c)
			s++;
		ptr[i] = init_str(s, c);
		if (!ptr[i]) // Check for allocation failure for each string
		{
			// If one string fails to be allocated, free the previous ones and return NULL
			SDL_Log("Memory allocation error in ft_split while processing word %d", i);
			while (i-- > 0)
				free(ptr[i]);
			free(ptr);
			return (NULL);
		}
		s = s + ft_strlen(ptr[i]);
	}
	ptr[i] = 0;
	return (ptr);
}
