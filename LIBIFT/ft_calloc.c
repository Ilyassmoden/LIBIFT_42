#include "libft.h"
#include <stdio.h>
#include <stdint.h>
void *ft_calloc(size_t count, size_t size)
{
  
    if(count == 0 || size == 0)
    {
        void  *ptr  = malloc(count * size);
        if(!ptr)
            return NULL;
        return ptr;
    }
    if(18446744073709551615UL / count < size)
        return NULL;
    
    void  *ptr  = malloc(count * size);
        if(!ptr)
            return NULL;
        unsigned char *pt  = (unsigned char *)ptr;
        size_t i = 0;
        while(i < count * size)
        {
            pt[i] = 0;
            i++;
        }
        return ptr;
}
