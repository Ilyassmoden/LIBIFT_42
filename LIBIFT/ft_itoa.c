#include "libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <stdlib.h>

int	*count_digit(long n, int *len)
{
	int		count;
	int		*arr;
	long	g;

	count = 0;
	if (n < 0)
		n *= -1;
	g = n;
	while (n > 0)
	{
		count++;
		n /= 10;
	}
	*len = count;
	arr = malloc(sizeof(int) * (count));
	if (!arr)
		return (NULL);
	while (--count >= 0)
	{
		arr[count] = g % 10;
		g /= 10;
	}
	return (arr);
}

char	*is_zero_itoi(void)
{
	char	*str;

	str = malloc(2);
	if (!str)
		return (NULL);
	str[0] = '0';
	str[1] = '\0';
	return (str);
}

char	*cpy_itoi(int *arr, char *str, int n, int len)
{
	int	j;
	int	i;

	j = 0;
	i = 0;
	if (n < 0)
		str[j++] = '-';
	while (i < len)
	{
		str[j] = arr[i] + '0';
		i++;
		j++;
	}
	str[j] = '\0';
	free(arr);
	return (str);
}

char	*ft_itoa(int n)
{
	int		len;
	int		size;
	int		*arr;
	char	*str;

	if (n == 0)
		return (is_zero_itoi());
	len = 0;
	arr = count_digit(n, &len);
	if (!arr)
		return (NULL);
	size = len;
	if (n < 0)
		size++;
	str = malloc(size + 1);
	if (!str)
	{
		free(arr);
		return (NULL);
	}
	return (cpy_itoi(arr, str, n, len));
}
