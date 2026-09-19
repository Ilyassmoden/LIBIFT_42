#include "libft.h"
#include <stdio.h>
char	*ft_strrchr(const char *s, int c)
{
   char *ptr = (char*)s;
   char *temp = NULL;
    while(*ptr)
    {
        if(*ptr == c)
            temp = ptr;
        ptr++;
    }
    if(c == 0)
        return ptr;
    return temp;
}
