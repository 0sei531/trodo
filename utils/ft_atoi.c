#include "../Headers/TRODO.h"
#include <stdlib.h>
#include <unistd.h>

int ft_atoi(const char *str) {
    int i = 0, num = 0, sign = 1;

    while (str[i] && ((str[i] >= 9 && str[i] <= 13) || str[i] == 32))
        i++;
    if (str[i] == '-')
        sign = -1;
    if (str[i] == '-' || str[i] == '+')
        i++;
    while (str[i] != '\0' && ft_isdigit(str[i])) {
        num = (num * 10) + (str[i] - '0');
        i++;
    }
    return num * sign;
}

void *ft_memset(void *b, int c, size_t len) {
    while (len--)
        ((unsigned char *)b)[len] = (unsigned char)c;
    return b;
}

void *ft_calloc(size_t count, size_t size) {
    void *ptr = malloc(count * size);
    if (!ptr) {
        SDL_Quit();
        write(STDERR_FILENO, "Memory allocation failed!\n", 25);
        exit(1);
    }
    ft_memset(ptr, 0, count * size);
    return ptr;
}

static int ft_size_nb(int n) {
    int i = 1 + !(n) + (n < 0);
    while (n && i++)
        n /= 10;
    return i;
}

char *ft_itoa(int n) {
    char *res = ft_calloc(ft_size_nb(n), 1);
    if (!res) {
        SDL_Quit();
        write(STDERR_FILENO, "Failed to convert integer to string: memory allocation failed\n", 65);
        exit(1);
    }
    res[0] = '-';
    res[--i] = '\0';
    unsigned int u = -n * (n < 0) + n * !(n < 0);
    if (!u)
        res[i - 1] = '0';
    while (u) {
        res[--i] = (u % 10) + '0';
        u /= 10;
    }
    return res;
}
