#include "../Headers/TRODO.h"

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 1024
#endif

char *get_next_line(int fd)
{
    static char buffer[BUFFER_SIZE + 1];
    static int index = 0;
    static int bytes_read = 0;
    char *line = NULL;

    while (1)
    {
        if (index >= bytes_read)
        {
            index = 0;
            bytes_read = read(fd, buffer, BUFFER_SIZE);
            if (bytes_read <= 0)
                return line;
            buffer[bytes_read] = '\0';
        }
        char *newline = ft_strchr(buffer + index, '\n');
        if (newline)
        {
            size_t length = newline - (buffer + index);
            char *segment = ft_substr(buffer + index, 0, length);
            line = line ? ft_strjoin(line, segment) : segment;
            index += length + 1;
            return line;
        }
        char *segment = ft_substr(buffer + index, 0, bytes_read - index);
        line = line ? ft_strjoin(line, segment) : segment;
        index = bytes_read;
    }
}
