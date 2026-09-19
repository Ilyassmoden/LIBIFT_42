#include "libft.h"
t_list *ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
    t_list *new_lst = NULL;
    while(lst != NULL)
    {
       t_list *new = malloc(sizeof(t_list));
       if(!new)
        {
            ft_lstclear(&new_lst,del);
            return NULL;
        }
       new->content = lst->content;
       new->next = NULL;
       new->content = f(new->content);
       
        ft_lstadd_back(&new_lst,new);
        lst = lst->next;
    }
    return new_lst;
}
