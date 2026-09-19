#include "libft.h"

char *ft_strjoin(char **strs,char *sep,int size)
{
    int i = 0;
    int len  = (int)ft_strlen(sep) * (size - 1);
    len++;
    while(i < size)
    {
        len += ft_strlen(strs[i]);
        i++;
    }
    char *str = malloc(len);
    if(!str)
        return NULL;
    i = 0;
    str[0] = '\0';
    while(i < size)
    {
        ft_strlcat(str,strs[i],len);
        if(i + 1 != size)
            ft_strlcat(str,sep,len);
        i++;
    }
    return str; 
}
