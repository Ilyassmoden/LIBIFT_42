
#include "libft.h"

 int	is_set(char const *set, char c)
{
	size_t	i;

	i = 0;
	while (set[i])
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}

size_t	get_first(char const *s1, char const *set)
{
	size_t	first;

	first = 0;
	while (s1[first] && is_set(set, s1[first]))
		first++;
	return (first);
}

size_t	get_last(char const *s1, char const *set, size_t len)
{
	size_t	last;

	if (len == 0)
		return (0);
	last = len - 1;
	while (last > 0 && is_set(set, s1[last]))
		last--;
	return (last);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	first;
	size_t	last;
	size_t	i;
	char	*str;

	if (!s1 || !set)
		return (NULL);
	first = get_first(s1, set);
	last = get_last(s1, set, ft_strlen(s1));
	if (first > last || !s1[0])
		return (ft_strdup(""));
	str = malloc(sizeof(char) * (last - first + 2));
	if (!str)
		return (NULL);
	i = 0;
	while (first <= last)
		str[i++] = s1[first++];
	str[i] = '\0';
	return (str);
}
