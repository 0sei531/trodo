#include "../Headers/TRODO.h"
#include <stdlib.h>

// Function to create a new list element
t_map *ft_lst_new(void *content)
{
    t_map *new;

    new = (t_map *)malloc(sizeof(t_map)); // Allocate memory for a new node
    if (!new)
        return (NULL); // Return NULL if malloc fails
    new->content = content; // Assign the provided content to the node
    new->next = NULL; // Set next pointer to NULL
    return (new);
}

// Function to calculate the size of the list recursively
int ft_lst_size(t_map *lst)
{
    if (!lst)
        return (0); // Return 0 if the list is empty
    return (ft_lst_size(lst->next) + 1); // Recursively calculate the size of the list
}
