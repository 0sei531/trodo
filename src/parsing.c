#include <SDL2/SDL.h>
#include "../Headers/structs.h"
#include "../Headers/TRODO.h"
#include <stdlib.h>

t_data data;  // Global data definition

static int ft_lst_size(t_map *lst)
{
    int count = 0;
    while (lst)
    {
        if (lst->content[0])
            count++;
        lst = lst->next;
    }
    return count;
}

static void check_map()
{
    int i;
    int j;
    data.enm_nb = 0;
    i = -1;
    while (data.map[++i])
    {
        j = -1;
        while (data.map[i][++j])
        {
            if (!ft_strchr(MAP_CHAR, data.map[i][j]))
                error("Error:\ninvalid map character\n", 1);
            if (data.map[i][j] != ' ' && data.map[i][j] != '1')
            {
                if (!i || !j || j + 1 == data.w_map[i] || i + 1 == data.h_map
                    || data.map[i][j + 1] == ' ' || data.map[i][j - 1] == ' '
                    || data.map[i + 1][j] == ' ' || data.map[i - 1][j] == ' ')
                    error("Error:\ninvalid map\n", 1);
                if (data.map[i][j] == 'N' || data.map[i][j] == 'W' || data.map[i][j] == 'S' || data.map[i][j] == 'E')
                {
                    data.dir.s = (4 * (data.map[i][j] == 'N') + 8 * (data.map[i][j] == 'W') + 12 * (data.map[i][j] == 'S')) * ANGLES;
                    data.dir.angle = 90 * (data.map[i][j] == 'S') + 180 * (data.map[i][j] == 'W') + 270 * (data.map[i][j] == 'N');
                    data.dir.x = j * 50 + 10;
                    data.dir.y = i * 50 + 10;
                    data.dir.px = data.dir.x;
                    data.dir.py = data.dir.y;
                    data.map[i][j] = '0';
                    data.door_map[i][j] = '0';
                }
                if (data.map[i][j] == '*')
                {
                    data.enemy[data.enm_nb].x = j * 50 + 24;
                    data.enemy[data.enm_nb].y = i * 50 + 24;
                    data.map[i][j] = '0';
                    data.door_map[i][j] = '0';
                    data.enm_nb++;
                }
            }
        }
    }
    data.enemy_count = data.enm_nb;
}

static void parse_map(t_map *it)
{
    int i;
    i = 0;
    data.h_map = ft_lst_size(it);
    data.map = (char **)malloc(sizeof(char *) * (data.h_map + 1));
    if (!data.map)
        error("Error:\nmemory allocation failed\n", 1);
    data.door_map = (char **)malloc(sizeof(char *) * (data.h_map + 1));
    if (!data.door_map)
    {
        free(data.map);
        error("Error:\nmemory allocation failed\n", 1);
    }
    data.w_map = (int *)malloc(sizeof(int) * (data.h_map));
    if (!data.w_map)
    {
        free(data.map);
        free(data.door_map);
        error("Error:\nmemory allocation failed\n", 1);
    }
    data.game_map = it;
    while (it)
    {
        if (it->content[0])
        {
            data.w_map[i] = ft_strlen(it->content);
            data.door_map[i] = ft_substr(it->content, 0, data.w_map[i]);
            data.map[i] = ft_substr(it->content, 0, data.w_map[i]);
            if (!data.door_map[i] || !data.map[i])
                error("Error:\nmemory allocation failed\n", 1);
            i++;
        }
        else
            error("Error:\ninvalid map\n", 1);
        it = it->next;
    }
    data.map[i] = NULL;
    data.door_map[i] = NULL;
}

static t_map *read_map_file(const char *file_name)
{
    int fd;
    char *line;
    t_map *map = NULL;
    t_map *new_node;

    fd = open(file_name, O_RDONLY);
    if (fd < 0)
        error("Error:\ncannot open map file\n", 1);

    while ((line = get_next_line(fd)) != NULL)
    {
        new_node = ft_lst_new(line);
        if (!new_node)
        {
            ft_lst_clear(&map, free);
            close(fd);
            error("Error:\nmemory allocation failed\n", 1);
        }
        ft_lst_add_back(&map, new_node);
    }

    close(fd);
    return map;
}

int parsing(char *file_name)
{
    t_map *map;

    if (!file_name)
        return 0;

    // Read the map file into a linked list
    map = read_map_file(file_name);
    if (!map)
        return 0;

    // Skip empty lines at the beginning
    while (map && !map->content[0])
        map = map->next;

    // Parse the map data
    parse_map(map);

    // Validate the map
    check_map();

    return 1;
}
