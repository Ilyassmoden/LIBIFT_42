#include "libft.h"
#include <stdio.h>
char*ft_strnstr(char *big, char *little, size_t len)
{
   if(little[0] == '\0' && len == 0)
        return big;
    if(len == 0 && little[0] != '\0')
            return NULL;
    if(little[0] == '\0')
        return big;
    if(len == 0)
        return NULL;
    size_t i = 0;
    while(big[i] && i < len)
    {
        if(i + ft_strlen(little) <= len)
        {
            int b = ft_strncmp(little,big + i,ft_strlen(little));
            if(b == 0)
            return big + i;
        }
        i++;
    }
    return NULL;
}
