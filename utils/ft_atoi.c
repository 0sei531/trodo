#include "../Headers/TRODO.h"
#include <unistd.h>

int ft_atoi(const char *str)
{
    int i;
    int sign;
    int result;
    
    i = 0;
    sign = 1;
    result = 0;
    while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
        i++;
    if (str[i] == '-' || str[i] == '+')
    {
        if (str[i] == '-')
            sign = -1;
        i++;
    }
    while (str[i] != '\0' && ftisdigit(str[i]))
    {
        result = result * 10 + (str[i] - '0');
        i++;
    }
    return (sign * result);
}

void *ft_calloc(size_t count, size_t size)
{
    void *ptr;
    ssize_t write_result;
    unsigned char *byte_ptr;
    size_t total_size;

    total_size = count * size;
    ptr = malloc(total_size);
    if (!ptr)
    {
        write_result = write(STDERR_FILENO, "Memory allocation failed!\n", 25);
        (void)write_result;
        return (NULL);
    }
    
    // Zero out the allocated memory
    byte_ptr = (unsigned char *)ptr;
    while (total_size--)
        *byte_ptr++ = 0;
    
    return (ptr);
}

char *ft_itoa(int n)
{
    char    *res;
    int     len;
    int     tmp;
    int     i;
    
    len = 1;
    tmp = n;
    while (tmp /= 10)
        len++;
    i = len + (n < 0);
    res = (char *)malloc(sizeof(char) * (i + 1));
    if (!res)
    {
        ssize_t write_result = write(STDERR_FILENO, 
            "Failed to convert integer to string: memory allocation failed\n", 65);
        (void)write_result;
        return (NULL);
    }
    res[i] = '\0';
    if (n < 0)
        res[0] = '-';
    while (i-- > (n < 0))
    {
        res[i] = '0' + (n < 0 ? -(n % 10) : n % 10);
        n /= 10;
    }
    return (res);
}
