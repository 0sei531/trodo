#include "../Headers/TRODO.h"

size_t ft_strlen(const char *str) {
    if (!str) return 0;
    size_t len = 0;
    while (str[len]) len++;
    return len;
}

char *ft_strdup(const char *s) {
    if (!s) return NULL;
    
    size_t len = ft_strlen(s);
    char *dup = malloc(len + 1);
    
    if (!dup) return NULL;
    
    ft_memcpy(dup, s, len);
    dup[len] = '\0';
    return dup;
}

char *ft_strjoin(char *s1, char *s2) {
    if (!s2) return NULL;
    if (!s1) {
        s1 = malloc(1);
        if (!s1) return NULL;
        *s1 = '\0';
    }
    
    size_t len1 = ft_strlen(s1);
    size_t len2 = ft_strlen(s2);
    char *str = malloc(len1 + len2 + 1);
    
    if (!str) {
        free(s1);
        return NULL;
    }
    
    ft_memcpy(str, s1, len1);
    ft_memcpy(str + len1, s2, len2);
    str[len1 + len2] = '\0';
    
    free(s1);
    return str;
}

char *ft_substr(const char *s, size_t start, size_t len) {
    if (!s) return NULL;
    
    size_t s_len = ft_strlen(s);
    if (start >= s_len) return ft_strdup("");
    if (len > s_len - start) len = s_len - start;
    
    char *substr = malloc(len + 1);
    if (!substr) return NULL;
    
    ft_memcpy(substr, s + start, len);
    substr[len] = '\0';
    return substr;
}

int ft_strncmp(const char *s1, const char *s2, size_t n) {
    if (!s1 || !s2) return -1;
    
    while (n-- && (*s1 || *s2)) {
        if (*s1 != *s2)
            return (unsigned char)*s1 - (unsigned char)*s2;
        s1++;
        s2++;
    }
    return 0;
}

char *ft_strchr(const char *s, int c) {
    if (!s) return NULL;
    
    while (*s) {
        if (*s == (char)c) return (char *)s;
        s++;
    }
    return (c == 0) ? (char *)s : NULL;
}

char *ft_strnstr(const char *big, const char *little, size_t len) {
    if (!little[0]) return (char *)big;
    
    size_t little_len = ft_strlen(little);
    if (little_len > len) return NULL;
    
    for (size_t i = 0; i <= len - little_len; i++) {
        if (!ft_strncmp(big + i, little, little_len))
            return (char *)(big + i);
    }
    return NULL;
}

