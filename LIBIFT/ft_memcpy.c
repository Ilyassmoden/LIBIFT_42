#include "libft.h"
void *ft_memcpy(void *dest,void *src, size_t n)
{
    unsigned char *ptrtoDest = (unsigned char *)dest;
    unsigned char *ptrtoSrc = (unsigned char *)src;
    size_t i = 0;
    while(i < n)
    {
        ptrtoDest[i] = ptrtoSrc[i];
        i++;
    }
    return dest;
}
/*
int main ()
{
    char src[] = {1,2,7,3,8};
    char dest[9];
    ft_memcpy(dest,src,4);
    int i = 0;
    while(i < 6)
    {
        printf("%d ",dest[i]);
        i++;
    }
    char src2[] = {1,2,7,3,8};
    char dest2[9];
    memcpy(dest2,src2,4);
    i = 0;
    while(i < 6)
    {
        printf("%d ",dest2[i]);
        i++;
    }
}*/