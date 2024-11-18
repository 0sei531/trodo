#include "../Headers/TRODO.h"
#include <SDL2/SDL.h>

int arg_check(int ac, char **av)
{
    char *error;
    ssize_t write_ret;

    error = NULL;
    if (ac != 2)
        error = "Error: too many arguments\n";
    else if (ft_strncmp(av[1] + ft_strlen(av[1]) - 4, ".cub", 4) != 0)
        error = "Error: invalid file extension\n";

    if (error)
    {
        write_ret = write(2, error, ft_strlen(error));
        if (write_ret == -1)
            return (0);  // Handle write error
        return (0);
    }
    return (1);
}

int init_sdl(SDL_Window **window, SDL_Renderer **renderer)
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        ft_putstr_fd("SDL2 initialization failed: ", 2);
        ft_putstr_fd(SDL_GetError(), 2);
        return (0);
    }

    *window = SDL_CreateWindow("Cub3D", SDL_WINDOWPOS_CENTERED, 
        SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);
    if (!*window)
    {
        ft_putstr_fd("Error creating SDL window: ", 2);
        ft_putstr_fd(SDL_GetError(), 2);
        SDL_Quit();
        return (0);
    }

    *renderer = SDL_CreateRenderer(*window, -1, SDL_RENDERER_ACCELERATED);
    if (!*renderer)
    {
        ft_putstr_fd("Error creating SDL renderer: ", 2);
        ft_putstr_fd(SDL_GetError(), 2);
        SDL_DestroyWindow(*window);
        SDL_Quit();
        return (0);
    }

    return (1);
}

void clean_up(SDL_Window *window, SDL_Renderer *renderer, t_map *map)
{
    if (renderer)
        SDL_DestroyRenderer(renderer);
    if (window)
        SDL_DestroyWindow(window);
    SDL_Quit();
    
    // Use the appropriate free function based on your structure
    free_map_struct(map);  // Using the function declared in your header
}

int main(int ac, char **av)
{
    SDL_Window *window;
    SDL_Renderer *renderer;
    t_map *map;
    char *buff;
    int fd;

    // Initialize SDL2
    if (!init_sdl(&window, &renderer))
        return (1);

    init_args(&map);
    buff = NULL;

    if (arg_check(ac, av) != 1)
    {
        clean_up(window, renderer, map);
        return (0);
    }

    // Open the .cub file
    fd = open(av[1], O_RDONLY);
    if (fd < 0)
    {
        ft_putstr_fd("Error: could not open file\n", 2);
        clean_up(window, renderer, map);
        return (1);
    }

    // Read the .cub file line by line and add to the map
    while ((buff = get_next_line(fd)) != NULL)
    {
        if (ft_strlen(buff) > 0 && buff[ft_strlen(buff) - 1] == '\n')
            buff[ft_strlen(buff) - 1] = '\0';  // Remove trailing newline
        ft_lst_add_back(&map, ft_lst_new(buff));  // Add to the map
        free(buff);  // Free memory after use
    }

    close(fd);

    // Parse the map and setup the minimap
    parsing(map);
    set_minimap();

    // Main game loop
    SDL_Event event;
    int running = 1;

    while (running)
    {
        // Event handling
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
                running = 0;
            else if (event.type == SDL_KEYDOWN)
                handle_key_press(&event, &data);
            else if (event.type == SDL_KEYUP)
                handle_key_release(&event, &data);
            else if (event.type == SDL_MOUSEBUTTONDOWN)
                handle_mouse_press(&event, &data);
            else if (event.type == SDL_MOUSEMOTION)
                handle_mouse_motion(&event, &data);
            else if (event.type == SDL_MOUSEBUTTONUP)
                handle_mouse_release(&event, &data);
        }

        // Clear screen
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        // Render game state
        render_game(&data);
        set_rays(renderer);

        // Present the renderer
        SDL_RenderPresent(renderer);
    }

    // Cleanup and exit
    clean_up(window, renderer, map);
    return (0);
}
