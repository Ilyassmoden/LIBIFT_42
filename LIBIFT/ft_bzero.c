#include <string.h>
void ft_bzero(void *s,size_t n)
{
    unsigned char *ptr = (unsigned char*)s;
    size_t i = 0;
    while(i < n)
    {
        *ptr = 0;
        i++;
        ptr++;
    }
}