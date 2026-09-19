#include "libft.h"
#include <stdio.h>
int ft_strncmp(const char *s1, const char *s2, size_t n)
{
    char *ptrs2 = (char*)s2;
    char *ptrs1 = (char*)s1;
    if(n == 0)
        return 0;
    if((*ptrs1 == '\0'  || *ptrs2 == '\0') && (n > 0))
    {
        return *ptrs1 - *ptrs2;
    }
   
    if(*ptrs2 != *ptrs1)
    {
        return *ptrs1 - *ptrs2;
    }
    return ft_strncmp((char*)s1 + 1,(char*)s2 + 1,n - 1);
}