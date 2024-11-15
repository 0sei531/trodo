#include "../Headers/TRODO.h"
#include <stdlib.h>

static int	ft_search(char *s, char c)
{
	int	i;

	i = -1;
	while (s[++i])
		if (s[i] == c)
			return (1);
	return (0);
}

char	*ft_str_trim(char const *s1, char const *set)
{
	int		sl;
	char	*s;
	char	*res;

	if (!s1 || !set)
	{
		// Log error if either input string is NULL
		SDL_Log("Error: NULL pointer passed to ft_str_trim");
		return (NULL);
	}
	s = (char *)s1;
	while (*s && ft_search((char *)set, *s))
		s++;
	sl = ft_strlen(s);
	while (sl && ft_search((char *)set, s[sl - 1]))
		sl--;
	res = ft_substr(s, 0, sl);
	if (!res)
	{
		// Log error if ft_substr allocation fails
		SDL_Log("Memory allocation failed in ft_str_trim");
		return (NULL);
	}
	return (res);
}
