#include "../Headers/TRODO.h"
#include <limits.h>

bool ftisdigit(int c)
{
    return (c >= '0' && c <= '9');
}

int ft_atoi(const char *str)
{
    int i;
    int sign;
    long result;

    i = 0;
    sign = 1;
    result = 0;
    while (str[i] == ' ' || str[i] == '\n' || str[i] == '\t' ||
           str[i] == '\v' || str[i] == '\f' || str[i] == '\r')
        i++;
    if (str[i] == '-' || str[i] == '+')
    {
        if (str[i] == '-')
            sign = -1;
        i++;
    }
    while (str[i] && ftisdigit(str[i]))
    {
        result = result * 10 + (str[i] - '0');
        if (result * sign > INT_MAX)
            return (INT_MAX);
        if (result * sign < INT_MIN)
            return (INT_MIN);
        i++;
    }
    return ((int)(result * sign));
}

static size_t count_words(const char *s, char c)
{
    size_t count;
    size_t i;

    count = 0;
    i = 0;
    while (s[i])
    {
        while (s[i] == c)
            i++;
        if (s[i])
        {
            count++;
            while (s[i] && s[i] != c)
                i++;
        }
    }
    return (count);
}

static char *get_next_word(const char *s, char c, size_t *start)
{
    size_t end;
    char *word;

    while (s[*start] == c)
        (*start)++;
    end = *start;
    while (s[end] && s[end] != c)
        end++;
    word = ft_substr(s, *start, end - *start);
    *start = end;
    return (word);
}

char **ft_split(char const *s, char c)
{
    char **result;
    size_t word_count;
    size_t i;
    size_t start;

    if (!s)
        return (NULL);
    word_count = count_words(s, c);
    result = malloc((word_count + 1) * sizeof(char *));
    if (!result)
        return (NULL);
    i = 0;
    start = 0;
    while (i < word_count)
    {
        result[i] = get_next_word(s, c, &start);
        if (!result[i])
        {
            while (i > 0)
                free(result[--i]);
            free(result);
            return (NULL);
        }
        i++;
    }
    result[word_count] = NULL;
    return (result);
}
