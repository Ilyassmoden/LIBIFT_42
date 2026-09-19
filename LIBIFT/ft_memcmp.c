#include "libft.h"
int ft_memcmp(const void *s1, const void *s2, size_t n)
{
    const unsigned char *ptrs2 = (unsigned char*)s2;
    const unsigned char *ptrs1 = (unsigned char*)s1;
    if(n == 0)
        return 0;
    if(*ptrs2 != *ptrs1)
    {
        return *ptrs1 - *ptrs2;
    }
    return ft_memcmp((unsigned char*)s1 + 1,(unsigned char*)s2 + 1,n - 1);
}
