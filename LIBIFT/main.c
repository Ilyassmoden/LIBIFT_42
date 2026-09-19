#include "libft.h"

#include <ctype.h>
#include <fcntl.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/* ========================================================= */
/*                       GLOBAL RESULTS                       */
/* ========================================================= */

static int	g_total;
static int	g_passed;
static int	g_failed;

/* ========================================================= */
/*                         CHECK                              */
/* ========================================================= */

static void	check(int condition, const char *name)
{
	g_total++;
	if (condition)
	{
		g_passed++;
		printf("\033[32m[PASS]\033[0m %s\n", name);
	}
	else
	{
		g_failed++;
		printf("\033[31m[FAIL]\033[0m %s\n", name);
	}
}

/* ========================================================= */
/*                  LOCAL REFERENCE FUNCTIONS                */
/* ========================================================= */

/*
 * strnstr is not a standard GNU libc function on Fedora,
 * so we implement a local reference version for testing.
 */
static char	*ref_strnstr(const char *haystack,
				const char *needle, size_t len)
{
	size_t	i;
	size_t	j;

	if (needle[0] == '\0')
		return ((char *)haystack);
	i = 0;
	while (haystack[i] != '\0' && i < len)
	{
		j = 0;
		while (needle[j] != '\0'
			&& i + j < len
			&& haystack[i + j] == needle[j])
			j++;
		if (needle[j] == '\0')
			return ((char *)(haystack + i));
		i++;
	}
	return (NULL);
}

static size_t	ref_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	src_len;

	src_len = strlen(src);
	if (size == 0)
		return (src_len);
	i = 0;
	while (i + 1 < size && src[i] != '\0')
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (src_len);
}

static size_t	ref_strlcat(char *dst, const char *src, size_t size)
{
	size_t	dst_len;
	size_t	src_len;
	size_t	i;

	dst_len = 0;
	while (dst_len < size && dst[dst_len] != '\0')
		dst_len++;
	src_len = strlen(src);
	if (dst_len == size)
		return (size + src_len);
	i = 0;
	while (dst_len + i + 1 < size && src[i] != '\0')
	{
		dst[dst_len + i] = src[i];
		i++;
	}
	dst[dst_len + i] = '\0';
	return (dst_len + src_len);
}

/* ========================================================= */
/*                      CHARACTER FUNCTIONS                   */
/* ========================================================= */

static void	test_character_functions(void)
{
	int	c;
	int	x;

	printf("\n===== CHARACTER FUNCTIONS =====\n");

	c = 0;
	while (c <= 255)
	{
		check(!!ft_isalpha(c) == !!isalpha((unsigned char)c),
			"ft_isalpha");
		check(!!ft_isdigit(c) == !!isdigit((unsigned char)c),
			"ft_isdigit");
		check(!!ft_isalnum(c) == !!isalnum((unsigned char)c),
			"ft_isalnum");
		check(!!ft_isascii(c) == !!isascii(c),
			"ft_isascii");
		check(!!ft_isprint(c) == !!isprint((unsigned char)c),
			"ft_isprint");
		c++;
	}

	x = 0;
	while (x <= 255)
	{
		check(ft_toupper(x) == toupper((unsigned char)x),
			"ft_toupper");
		check(ft_tolower(x) == tolower((unsigned char)x),
			"ft_tolower");
		x++;
	}
}

/* ========================================================= */
/*                       MEMORY FUNCTIONS                     */
/* ========================================================= */

static void	test_memory_functions(void)
{
	char	a[128];
	char	b[128];
	char	*p;

	printf("\n===== MEMORY FUNCTIONS =====\n");

	memset(a, 'A', sizeof(a));
	memset(b, 'A', sizeof(b));

	p = ft_memset(a, 'X', 50);
	check(p == a, "ft_memset return");
	memset(b, 'X', 50);
	check(memcmp(a, b, sizeof(a)) == 0, "ft_memset content");

	memset(a, 'A', sizeof(a));
	ft_bzero(a, 50);
	check(a[0] == 0 && a[49] == 0 && a[50] == 'A',
		"ft_bzero");

	memset(a, 'A', sizeof(a));
	memset(b, 'A', sizeof(b));
	ft_memcpy(a, "Hello 1337", 11);
	memcpy(b, "Hello 1337", 11);
	check(memcmp(a, b, sizeof(a)) == 0, "ft_memcpy");

	strcpy(a, "0123456789");
	strcpy(b, "0123456789");
	ft_memmove(a + 2, a, 8);
	memmove(b + 2, b, 8);
	check(memcmp(a, b, 11) == 0, "ft_memmove overlap forward");

	strcpy(a, "0123456789");
	strcpy(b, "0123456789");
	ft_memmove(a, a + 2, 8);
	memmove(b, b + 2, 8);
	check(memcmp(a, b, 11) == 0, "ft_memmove overlap backward");

	memset(a, 'A', sizeof(a));
	a[77] = 'Z';
	check(ft_memchr(a, 'Z', sizeof(a)) == memchr(a, 'Z', sizeof(a)),
		"ft_memchr found");

	check(ft_memchr(a, 'Q', sizeof(a)) == memchr(a, 'Q', sizeof(a)),
		"ft_memchr not found");

	memset(a, 'A', sizeof(a));
	memset(b, 'A', sizeof(b));
	check((ft_memcmp(a, b, sizeof(a)) == 0)
		== (memcmp(a, b, sizeof(a)) == 0),
		"ft_memcmp equal");

	a[40] = 'B';
	check((ft_memcmp(a, b, sizeof(a)) < 0)
		== (memcmp(a, b, sizeof(a)) < 0),
		"ft_memcmp sign");

	memset(a, 'A', sizeof(a));
	memset(b, 'A', sizeof(b));
	check(ft_memset(a, 'Z', 0) == a, "ft_memset zero");

	(void)p;
}

/* ========================================================= */
/*                       STRING FUNCTIONS                     */
/* ========================================================= */

static void	test_string_functions(void)
{
	char	*a;
	char	*b;
	char	dst1[64];
	char	dst2[64];
	char	*strs[4];

	printf("\n===== STRING FUNCTIONS =====\n");

	check(ft_strlen("") == 0, "ft_strlen empty");
	check(ft_strlen("hello") == 5, "ft_strlen normal");
	check(ft_strlen("1337 Piscine") == 12, "ft_strlen sentence");

	check(ft_strchr("hello", 'h') == strchr("hello", 'h'),
		"ft_strchr first");
	check(ft_strchr("hello", 'o') == strchr("hello", 'o'),
		"ft_strchr last");
	check(ft_strchr("hello", 'x') == strchr("hello", 'x'),
		"ft_strchr missing");
	check(ft_strchr("hello", '\0') == strchr("hello", '\0'),
		"ft_strchr null");

	check(ft_strrchr("hello hello", 'h')
		== strrchr("hello hello", 'h'),
		"ft_strrchr");
	check(ft_strrchr("hello", '\0') == strrchr("hello", '\0'),
		"ft_strrchr null");

	check((ft_strncmp("abc", "abd", 3) < 0)
		== (strncmp("abc", "abd", 3) < 0),
		"ft_strncmp less");
	check((ft_strncmp("abd", "abc", 3) > 0)
		== (strncmp("abd", "abc", 3) > 0),
		"ft_strncmp greater");
	check(ft_strncmp("abc", "abc", 3) == 0,
		"ft_strncmp equal");
	check(ft_strncmp("abcdef", "abcxyz", 3) == 0,
		"ft_strncmp limited n");

	check(ft_strnstr("hello 1337 world", "1337", 15)
		== ref_strnstr("hello 1337 world", "1337", 15),
		"ft_strnstr found");
	check(ft_strnstr("hello 1337 world", "xyz", 15)
		== ref_strnstr("hello 1337 world", "xyz", 15),
		"ft_strnstr not found");
	check(ft_strnstr("hello", "", 0)
		== ref_strnstr("hello", "", 0),
		"ft_strnstr empty needle");

	memset(dst1, 'X', sizeof(dst1));
	memset(dst2, 'X', sizeof(dst2));
	check(ft_strlcpy(dst1, "Hello 1337", sizeof(dst1))
		== ref_strlcpy(dst2, "Hello 1337", sizeof(dst2)),
		"ft_strlcpy return");
	check(strcmp(dst1, dst2) == 0, "ft_strlcpy content");

	memset(dst1, 'X', sizeof(dst1));
	memset(dst2, 'X', sizeof(dst2));
	check(ft_strlcpy(dst1, "Hello", 4)
		== ref_strlcpy(dst2, "Hello", 4),
		"ft_strlcpy truncated return");
	check(memcmp(dst1, dst2, sizeof(dst1)) == 0,
		"ft_strlcpy truncated content");

	strcpy(dst1, "Hello");
	strcpy(dst2, "Hello");
	check(ft_strlcat(dst1, " 1337", sizeof(dst1))
		== ref_strlcat(dst2, " 1337", sizeof(dst2)),
		"ft_strlcat return");
	check(strcmp(dst1, dst2) == 0, "ft_strlcat content");

	a = ft_strdup("Hello 1337");
	check(a != NULL && strcmp(a, "Hello 1337") == 0,
		"ft_strdup");
	free(a);

	a = ft_substr("Hello 1337", 6, 4);
	check(a != NULL && strcmp(a, "1337") == 0,
		"ft_substr normal");
	free(a);

	a = ft_substr("Hello", 100, 10);
	check(a != NULL && strcmp(a, "") == 0,
		"ft_substr out of range");
	free(a);

	/*
	 * Your ft_strjoin prototype is:
	 * char *ft_strjoin(char **strs, char *sep, int size);
	 */
	strs[0] = "Hello";
	strs[1] = "1337";
	strs[2] = "Libft";
	strs[3] = NULL;
	a = ft_strjoin(strs, "-", 3);
	check(a != NULL && strcmp(a, "Hello-1337-Libft") == 0,
		"ft_strjoin");
	free(a);

	a = ft_strtrim("   hello 1337   ", " ");
	check(a != NULL && strcmp(a, "hello 1337") == 0,
		"ft_strtrim spaces");
	free(a);

	a = ft_strtrim("xxxHelloxxx", "x");
	check(a != NULL && strcmp(a, "Hello") == 0,
		"ft_strtrim custom");
	free(a);

	b = ft_strjoin(strs, "", 3);
	check(b != NULL && strcmp(b, "Hello1337Libft") == 0,
		"ft_strjoin empty separator");
	free(b);
}

/* ========================================================= */
/*                         FT_SPLIT                          */
/* ========================================================= */

static void	free_split(char **tab)
{
	int	i;

	if (!tab)
		return ;
	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

static void	test_split(void)
{
	char	**tab;

	printf("\n===== FT_SPLIT =====\n");

	tab = ft_split("hello world 1337", ' ');
	check(tab != NULL, "ft_split allocation");
	if (tab)
	{
		check(strcmp(tab[0], "hello") == 0, "ft_split word 1");
		check(strcmp(tab[1], "world") == 0, "ft_split word 2");
		check(strcmp(tab[2], "1337") == 0, "ft_split word 3");
		check(tab[3] == NULL, "ft_split NULL termination");
	}
	free_split(tab);

	tab = ft_split("   hello   world   ", ' ');
	check(tab != NULL && strcmp(tab[0], "hello") == 0
		&& strcmp(tab[1], "world") == 0
		&& tab[2] == NULL,
		"ft_split repeated delimiters");
	free_split(tab);

	tab = ft_split("     ", ' ');
	check(tab != NULL && tab[0] == NULL,
		"ft_split only delimiters");
	free_split(tab);

	tab = ft_split("", ' ');
	check(tab != NULL && tab[0] == NULL,
		"ft_split empty");
	free_split(tab);
}

/* ========================================================= */
/*                   CONVERSION / ALLOCATION                 */
/* ========================================================= */

static void	test_conversion_functions(void)
{
	char	*s;
	void	*p;
	size_t	i;

	printf("\n===== CONVERSION / ALLOCATION =====\n");

	check(ft_atoi("42") == 42, "ft_atoi 42");
	check(ft_atoi("-42") == -42, "ft_atoi -42");
	check(ft_atoi("+42") == 42, "ft_atoi +42");
	check(ft_atoi("   -42") == -42, "ft_atoi spaces");
	check(ft_atoi("\t\n\v\f\r -42") == -42,
		"ft_atoi whitespace");
	check(ft_atoi("123abc") == 123, "ft_atoi suffix");
	check(ft_atoi("abc123") == 0, "ft_atoi invalid");
	check(ft_atoi("0") == 0, "ft_atoi zero");
	check(ft_atoi("2147483647") == INT_MAX, "ft_atoi INT_MAX");
	check(ft_atoi("-2147483648") == INT_MIN, "ft_atoi INT_MIN");

	s = ft_itoa(0);
	check(s != NULL && strcmp(s, "0") == 0, "ft_itoa 0");
	free(s);

	s = ft_itoa(42);
	check(s != NULL && strcmp(s, "42") == 0, "ft_itoa 42");
	free(s);

	s = ft_itoa(-42);
	check(s != NULL && strcmp(s, "-42") == 0, "ft_itoa -42");
	free(s);

	s = ft_itoa(INT_MAX);
	check(s != NULL && strcmp(s, "2147483647") == 0,
		"ft_itoa INT_MAX");
	free(s);

	s = ft_itoa(INT_MIN);
	check(s != NULL && strcmp(s, "-2147483648") == 0,
		"ft_itoa INT_MIN");
	free(s);

	p = ft_calloc(100, sizeof(int));
	check(p != NULL, "ft_calloc allocation");

	if (p)
	{
		i = 0;
		while (i < 100 * sizeof(int))
		{
			if (((unsigned char *)p)[i] != 0)
				break ;
			i++;
		}
		check(i == 100 * sizeof(int), "ft_calloc zeroed memory");
		free(p);
	}

	p = ft_calloc((size_t)-1, 2);
	check(p == NULL, "ft_calloc overflow");
	free(p);
}

/* ========================================================= */
/*                    STRMAPI / STRITERI                     */
/* ========================================================= */

static char	to_upper_callback(unsigned int index, char c)
{
	(void)index;
	if (c >= 'a' && c <= 'z')
		return ((char)(c - ('a' - 'A')));
	return (c);
}

static void	iter_callback(unsigned int index, char *c)
{
	if (index % 2 == 0 && *c >= 'a' && *c <= 'z')
		*c = (char)(*c - ('a' - 'A'));
}

static void	test_mapi_iteri(void)
{
	char	*s;
	char	buffer[] = "abcdef";

	printf("\n===== STRMAPI / STRITERI =====\n");

	s = ft_strmapi("hello 1337", to_upper_callback);
	check(s != NULL && strcmp(s, "HELLO 1337") == 0,
		"ft_strmapi");
	free(s);

	ft_striteri(buffer, iter_callback);
	check(strcmp(buffer, "AbCdEf") == 0,
		"ft_striteri");
}

/* ========================================================= */
/*                       FD FUNCTIONS                        */
/* ========================================================= */

static void	test_fd_functions(void)
{
	int		fd;
	int		n;
	char	buffer[256];
	char	expected[] = "AHello1337\n-2147483648";

	printf("\n===== FD FUNCTIONS =====\n");

	fd = open("libft_test_output.txt",
			O_WRONLY | O_CREAT | O_TRUNC, 0644);
	check(fd >= 0, "open test file");
	if (fd < 0)
		return ;

	ft_putchar_fd('A', fd);
	ft_putstr_fd("Hello", fd);
	ft_putnbr_fd(1337, fd);
	ft_putendl_fd("", fd);
	ft_putnbr_fd(INT_MIN, fd);

	close(fd);

	fd = open("libft_test_output.txt", O_RDONLY);
	check(fd >= 0, "reopen test file");
	if (fd < 0)
		return ;

	n = read(fd, buffer, sizeof(buffer) - 1);
	if (n >= 0)
		buffer[n] = '\0';
	else
		buffer[0] = '\0';

	close(fd);

	check(n == (int)strlen(expected), "fd output length");
	check(strcmp(buffer, expected) == 0, "fd output content");

	unlink("libft_test_output.txt");
}

/* ========================================================= */
/*                      BONUS LIST HELPERS                   */
/* ========================================================= */

static void	free_content(void *content)
{
	free(content);
}

static void	double_content(void *content)
{
	int	*n;

	n = (int *)content;
	if (n)
		*n *= 2;
}

static void	*map_double(void *content)
{
	int	*new_value;

	if (!content)
		return (NULL);
	new_value = malloc(sizeof(int));
	if (!new_value)
		return (NULL);
	*new_value = (*(int *)content) * 2;
	return (new_value);
}

/* ========================================================= */
/*                     BONUS LINKED LIST                     */
/* ========================================================= */

static void	test_bonus(void)
{
	t_list	*list;
	t_list	*n1;
	t_list	*n2;
	t_list	*n3;
	t_list	*single;
	t_list	*mapped;
	int		*v1;
	int		*v2;
	int		*v3;
	int		*single_value;

	printf("\n===== BONUS LINKED LIST =====\n");

	v1 = malloc(sizeof(int));
	v2 = malloc(sizeof(int));
	v3 = malloc(sizeof(int));
	single_value = malloc(sizeof(int));

	if (!v1 || !v2 || !v3 || !single_value)
	{
		free(v1);
		free(v2);
		free(v3);
		free(single_value);
		check(0, "bonus setup allocation");
		return ;
	}

	*v1 = 10;
	*v2 = 20;
	*v3 = 30;
	*single_value = 99;

	n1 = ft_lstnew(v1);
	n2 = ft_lstnew(v2);
	n3 = ft_lstnew(v3);

	check(n1 != NULL, "ft_lstnew n1");
	check(n2 != NULL, "ft_lstnew n2");
	check(n3 != NULL, "ft_lstnew n3");

	list = n1;

	ft_lstadd_front(&list, n2);
	check(list == n2, "ft_lstadd_front");
	check(ft_lstsize(list) == 2, "ft_lstsize after front");

	ft_lstadd_back(&list, n3);
	check(ft_lstsize(list) == 3, "ft_lstadd_back");
	check(ft_lstlast(list) == n3, "ft_lstlast");

	ft_lstiter(list, double_content);
	check(*(int *)list->content == 40, "ft_lstiter first");
	check(*(int *)list->next->content == 20, "ft_lstiter second");
	check(*(int *)list->next->next->content == 60,
		"ft_lstiter third");

	mapped = ft_lstmap(list, map_double, free_content);
	check(mapped != NULL, "ft_lstmap allocation");

	if (mapped)
	{
		check(*(int *)mapped->content == 80,
			"ft_lstmap first");
		check(*(int *)mapped->next->content == 40,
			"ft_lstmap second");
		check(*(int *)mapped->next->next->content == 120,
			"ft_lstmap third");
		check(*(int *)list->content == 40,
			"ft_lstmap original unchanged");
	}

	single = ft_lstnew(single_value);
	check(single != NULL, "ft_lstnew single");

	if (single)
	{
		ft_lstdelone(single, free_content);
		check(1, "ft_lstdelone");
	}

	ft_lstclear(&mapped, free_content);
	check(mapped == NULL, "ft_lstclear mapped");

	ft_lstclear(&list, free_content);
	check(list == NULL, "ft_lstclear original");
}

/* ========================================================= */
/*                           MAIN                            */
/* ========================================================= */

int	main(void)
{
	printf("\n");
	printf("===============================================\n");
	printf("             LIBFT EXTREME TESTER             \n");
	printf("===============================================\n");

	test_character_functions();
	test_memory_functions();
	test_string_functions();
	test_split();
	test_conversion_functions();
	test_mapi_iteri();
	test_fd_functions();
	test_bonus();

	printf("\n===============================================\n");
	printf("                    RESULTS                  \n");
	printf("===============================================\n");
	printf("TOTAL  : %d\n", g_total);
	printf("\033[32mPASSED : %d\033[0m\n", g_passed);
	printf("\033[31mFAILED : %d\033[0m\n", g_failed);

	if (g_failed == 0)
		printf("\n\033[32m🔥 ALL TESTS PASSED 🔥\033[0m\n");
	else
		printf("\n\033[31m❌ SOME TESTS FAILED ❌\033[0m\n");

	printf("===============================================\n");

	return (g_failed != 0);
}