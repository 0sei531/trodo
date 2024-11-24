#include "../Headers/TRODO.h"

void *ft_memcpy(void *dst, const void *src, size_t n) {
    if (!dst || !src) return NULL;
    
    unsigned char *d = (unsigned char *)dst;
    const unsigned char *s = (const unsigned char *)src;
    
    while (n--) *d++ = *s++;
    return dst;
}

void *ft_calloc(size_t count, size_t size) {
    size_t total_size = count * size;
    void *ptr = malloc(total_size);
    
    if (!ptr) {
        error("Memory allocation failed", 0);
        return NULL;
    }
    
    memset(ptr, 0, total_size);
    return ptr;
}
