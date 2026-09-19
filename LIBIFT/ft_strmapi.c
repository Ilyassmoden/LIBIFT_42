#include "libft.h"
char *ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
    unsigned int i = 0;
    size_t len = ft_strlen(s);
    char *str =  malloc(len + 1);
    if(!str)
        return NULL;
    while(s[i])
    {
        str[i] = f(i,s[i]);
        i++;
    }
    str[i] = '\0';
    return str;
}
