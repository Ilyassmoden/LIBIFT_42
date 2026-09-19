#include "libft.h"
#include <stdio.h>
int ft_atoi(const char *str)
{
    int i = 0;
    while(str[i] == '\n' || str[i] == ' ' 
        || str[i] == '\t' || str[i] == '\r' || str[i] == '\v' 
        || str[i] == '\f')
        i++;
    int s = 1;
    if(str[i] == '-' || str[i] == '+')
    {
        if(str[i] == '-')
            s *= -1;
        i++;
    }
    int r = 0;
    while((str[i]  >= '0' && str[i] <=  '9' ))
    {
        r =  r * 10 + (str[i] - '0');
        i++;
    }
    return r  * s;
}
