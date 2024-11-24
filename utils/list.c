// list.c
#include "../Headers/TRODO.h"

t_map *ft_lst_new(void *content) {
    t_map *new_node = (t_map *)malloc(sizeof(t_map));
    if (!new_node)
        return NULL;
    
    new_node->content = (char *)content;
    new_node->next = NULL;
    return new_node;
}

void ft_lst_add_front(t_map **lst, t_map *new) {
    if (!lst || !new)
        return;
    
    new->next = *lst;
    *lst = new;
}

void ft_lst_add_back(t_map **lst, t_map *new) {
    if (!lst || !new)
        return;
        
    if (!*lst) {
        *lst = new;
        return;
    }
    
    t_map *current = *lst;
    while (current->next)
        current = current->next;
    current->next = new;
}

t_map *ft_lst_last(t_map *lst) {
    if (!lst)
        return NULL;
        
    while (lst->next)
        lst = lst->next;
    return lst;
}

void ft_lst_del_one(t_map *lst, void (*del)(void *)) {
    if (!lst || !del)
        return;
        
    del(lst->content);
    free(lst);
}

void ft_lst_clear(t_map **lst, void (*del)(void *)) {
    if (!lst || !*lst || !del)
        return;
        
    t_map *current = *lst;
    t_map *next;
    
    while (current) {
        next = current->next;
        ft_lst_del_one(current, del);
        current = next;
    }
    *lst = NULL;
}
