
#include "libft.h"
void *ft_memchr(const void *s, int c, size_t n)
{
    unsigned char *ptr = (unsigned char *)s;
   
    size_t i = 0;
    while(i < n)
    {
       if(*ptr == (unsigned char )c)
       {
            return ptr; 
       }
       ptr++;
       i++;
    }
    return NULL;
}


/*int	main(void)
{
	unsigned char	data[100];
	void			*result1;
	void			*result2;
	int				i;
	int				c;
	size_t			n;

	srand(time(NULL));

	for (i = 0; i < 100; i++)
		data[i] = rand() % 256;

	for (i = 0; i < 10000; i++)
	{
		c = rand() % 256;
		n = rand() % 101;

		result1 = ft_memchr(data, c, n);
		result2 = memchr(data, c, n);

		if (result1 != result2)
		{
			printf("KO at test %d\n", i + 1);
			printf("c = %d, n = %zu\n", c, n);
			printf("Expected: %p\n", result2);
			printf("Got:      %p\n", result1);
			return (1);
		}
	}

	printf("OK: 10000 tests passed!\n");
	return (0);
}*/