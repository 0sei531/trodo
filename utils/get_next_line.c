#include "../Headers/TRODO.h"
#include <SDL2/SDL.h>
#include <unistd.h>
#include <stdlib.h>

char *get_next_line(int fd)
{
    char    *line = NULL;
    char    *buffer;
    size_t  buffer_size = 1024; // Start with a 1KB buffer
    size_t  line_len = 0;
    ssize_t bytes_read;

    buffer = (char *)malloc(buffer_size);
    if (!buffer)
    {
        SDL_Log("Error: Memory allocation failed in get_next_line");
        return (NULL);  // Return NULL if memory allocation fails
    }

    while ((bytes_read = read(fd, buffer + line_len, buffer_size - line_len - 1)) > 0)
    {
        line_len += bytes_read;
        
        // Check if a newline is encountered in the buffer
        for (size_t i = line_len - bytes_read; i < line_len; i++)
        {
            if (buffer[i] == '\n')
            {
                buffer[i] = '\0';
                char *result = strdup(buffer);  // Create a string up to the newline
                if (!result)
                {
                    SDL_Log("Error: Memory allocation failed for result in get_next_line");
                    free(buffer);
                    return (NULL);  // Return NULL if memory allocation fails
                }
                // Shift remaining data in the buffer to prepare for the next line
                size_t remaining_data = line_len - i - 1;
                memmove(buffer, buffer + i + 1, remaining_data);
                line_len = remaining_data;
                return (result);
            }
        }

        // If the buffer is full, resize it to read more data
        if (line_len + bytes_read == buffer_size - 1)
        {
            buffer_size *= 2;  // Double the buffer size
            char *new_buffer = realloc(buffer, buffer_size);
            if (!new_buffer)
            {
                SDL_Log("Error: Memory reallocation failed in get_next_line");
                free(buffer);
                return (NULL);  // Return NULL if memory reallocation fails
            }
            buffer = new_buffer;
        }
    }

    if (bytes_read < 0)
    {
        SDL_Log("Error: Read operation failed in get_next_line");
        free(buffer);
        return (NULL);  // Return NULL if read operation fails
    }

    // If no data is read (empty line or EOF reached)
    if (line_len == 0)
    {
        free(buffer);
        return (NULL);  // Return NULL if there's no data left
    }

    buffer[line_len] = '\0';  // Null-terminate the last line
    char *result = strdup(buffer);
    free(buffer);

    return (result);
}
