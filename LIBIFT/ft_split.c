#include "libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

size_t	count_words(char const *str, char delimiter)
{
	size_t	i;
	size_t	word_count;
	int		is_check;

	i = 0;
	word_count = 0;
	is_check = 1;
	while (str[i])
	{
		if (str[i] == delimiter && is_check == 0)
		{
			word_count++;
			is_check = 1;
		}
		else if (str[i] != delimiter && is_check == 1)
			is_check = 0;
		i++;
	}
	if (i > 0 && str[i - 1] != delimiter)
		word_count++;
	return (word_count);
}

char	*copy_range(char const *str, int start, int end)
{
	char	*temp;
	char	*str_dup;
	int		i;

	temp = (char *)malloc(end - start + 1);
	if (!temp)
		return (NULL);
	i = 0;
	while (start < end)
		temp[i++] = str[start++];
	temp[i] = '\0';
	str_dup = ft_strdup(temp);
	free(temp);
	return (str_dup);
}

void	free__split(char **str_array, int allocated_count)
{
	while (allocated_count > 0)
	{
		allocated_count--;
		free(str_array[allocated_count]);
	}
	free(str_array);
}
static int	fill_split(char **str_array, char const *s, char c)
{
	int	i;
	int	arr_idx;
	int	is_check;
	int	start;

	i = 0;
	arr_idx = 0;
	is_check = 1;
	start = 0;
	while (s[i])
	{
		if (s[i] == c && is_check == 0)
		{
			str_array[arr_idx] = copy_range(s, start, i);
			if (!str_array[arr_idx])
				return (free__split(str_array, arr_idx), 0);
			arr_idx++;
			is_check = 1;
		}
		else if (s[i] != c && is_check == 1)
		{
			start = i;
			is_check = 0;
		}
		i++;
	}
	if (i > 0 && s[i - 1] != c)
	{
		str_array[arr_idx] = copy_range(s, start, i);
		if (!str_array[arr_idx])
			return (free__split(str_array, arr_idx), 0);
		arr_idx++;
	}
	str_array[arr_idx] = NULL;
	return (1);
}

char	**ft_split(char const *s, char c)
{
	char	**str_array;

	if (!s)
		return (NULL);
	str_array = (char **)malloc((count_words(s, c) + 1) * sizeof(char *));
	if (!str_array)
		return (NULL);
	if (!fill_split(str_array, s, c))
		return (NULL);
	return (str_array);
}
