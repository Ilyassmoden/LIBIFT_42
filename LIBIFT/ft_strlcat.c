#include "libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
    size_t len_src =  ft_strlen(src);
    size_t len_dest = ft_strlen(dest);
    if(size <= len_dest)
        return size + len_src;
    size_t size_modulo = size - len_dest;
    size_t i = len_dest;
    size_t j = 0;
    while(i < size_modulo +  len_dest - 1 && src[j])
    {
        dest[i] =  src[j];
        j++;
        i++;
    }
	dest[i] = '\0';
    return  len_dest + len_src;
}
