#include "libft.h"

char *ft_substr(char const *s, unsigned int start, size_t len)
{
    if(!s)
        return NULL;
    if((unsigned int )ft_strlen(s) < start)
    {
        char *ptr  = malloc(1);
        if(!ptr)
            return NULL;
        ptr[0] = '\0';
        return ptr;
    }
    size_t lan = ft_strlen(s) - start + 1;
    char *str  = malloc(lan);
    if(!str)
        return NULL;
    size_t j = 0;
    while(s[start] && j < lan && j < len)
    {
        str[j] = s[start];
        j++;
        start++;
    }
    str[j] = '\0';
    return str;
}
