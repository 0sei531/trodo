#include "../Headers/TRODO.h"
#include <stdbool.h>

bool ft_isdigit(int c) {
    return c >= '0' && c <= '9';
}

bool ft_str_isdigit(char *s) {
    if (!s || !*s)
        return false;
    while (*s) {
        if (!ft_isdigit(*s))
            return false;
        s++;
    }
    return true;
}
