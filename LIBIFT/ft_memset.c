#include <stdlib.h>
#include <stdio.h>
#include <string.h>
void *ft_memset(void *s,int c,size_t n)
{
    unsigned char *ptr = (unsigned char*)s;
    size_t i = 0;
    while(i < n)
    {
        *ptr = c;
        i++;
        ptr++;
    }
    return s;
}
/*
int main ()
{
    char po[5] = {30,60,90,32,13};
    ft_memset(po,67,4);
    for(int i = 0;i < 5;i++)
    {
        printf("%d ",po[i]);
    }
}*/