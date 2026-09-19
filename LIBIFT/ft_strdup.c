#include "libft.h"
#include <stdio.h>

char *ft_strdup(char *_s)
{
    char *str = malloc(ft_strlen(_s) + 1);
    char *ptr =  str;
    if(!str)
        return NULL;
    while(*_s)
    {
        *str = *_s;
        _s++;
        str++;
    }
    *str = *_s;
    return ptr;
}
