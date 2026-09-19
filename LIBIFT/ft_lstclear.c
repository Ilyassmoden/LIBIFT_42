#include "libft.h"
void ft_lstclear(t_list **lst, void (*del)(void *))
{
    if ((*lst) == NULL)
        return;

    while ((*lst) != NULL)
    {
        t_list *c = (*lst)->next;
        del((*lst)->content);
        free(*lst);
        (*lst) = c;
    }
}
