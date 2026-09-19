
#include <stdio.h>
#include <string.h>
#include "libft.h"
#include <stdlib.h>

void *ft_memmove(void *dest,const void *src, size_t n)
{
    //SOVINE PROBLEM MEMORY OVERLAP
    unsigned char *ptrtoDest = (unsigned char *)dest;
    unsigned char *ptrtoSrc = (unsigned char *)src;
    if(n == 0)
        return dest;
    if(ptrtoDest > ptrtoSrc)
    {
        size_t i = n;
        while(i > 0)
        {
            i--;
            ptrtoDest[i] = ptrtoSrc[i];
        }
    }
    else 
    {
        size_t i = 0;
        while(i < n)
        {
            ptrtoDest[i] = ptrtoSrc[i];
            i++;
        }
    }
   
    return dest;
}
/*
int	g_tests = 0;
int	g_failed = 0;

void	print_status(const char *name, int success)
{
	g_tests++;

	if (success)
		printf("✅ %s\n", name);
	else
	{
		printf("❌ %s\n", name);
		g_failed++;
	}
}

void	test_case(const char *name, const char *initial,
		size_t dest_index, size_t src_index, size_t n)
{
	char	expected[100];
	char	actual[100];

	memset(expected, 0, sizeof(expected));
	memset(actual, 0, sizeof(actual));

	memcpy(expected, initial, strlen(initial) + 1);
	memcpy(actual, initial, strlen(initial) + 1);

	memmove(expected + dest_index, expected + src_index, n);
	ft_memmove(actual + dest_index, actual + src_index, n);

	print_status(name, memcmp(expected, actual, sizeof(expected)) == 0);

	if (memcmp(expected, actual, sizeof(expected)) != 0)
	{
		printf("   Expected: %s\n", expected);
		printf("   Actual  : %s\n", actual);
		printf("   dest = %zu, src = %zu, n = %zu\n",
				dest_index, src_index, n);
	}
}

void	test_binary(const char *name, size_t dest_index,
		size_t src_index, size_t n)
{
	unsigned char expected[100];
	unsigned char actual[100];
	size_t i;

	i = 0;
	while (i < sizeof(expected))
	{
		expected[i] = (unsigned char)(i + 1);
		actual[i] = expected[i];
		i++;
	}

	memmove(expected + dest_index, expected + src_index, n);
	ft_memmove(actual + dest_index, actual + src_index, n);

	print_status(name, memcmp(expected, actual, sizeof(expected)) == 0);
}


int	main(void)
{
	size_t i;
	size_t dest;
	size_t src;
	size_t n;
	char name[100];

	printf("===== BASIC TESTS =====\n");

	test_case("Basic 01", "ABCDEFGHIJ", 0, 5, 5);
	test_case("Basic 02", "ABCDEFGHIJ", 5, 0, 5);
	test_case("Basic 03", "ABCDEFGHIJ", 2, 7, 3);
	test_case("Basic 04", "ABCDEFGHIJ", 7, 2, 3);
	test_case("Basic 05", "ABCDEFGHIJ", 0, 0, 10);
	test_case("Basic 06", "ABCDEFGHIJ", 1, 1, 0);
	test_case("Basic 07", "ABCDEFGHIJ", 3, 3, 4);
	test_case("Basic 08", "ABCDEFGHIJ", 0, 9, 1);
	test_case("Basic 09", "ABCDEFGHIJ", 9, 0, 1);
	test_case("Basic 10", "ABCDEFGHIJ", 4, 0, 6);

	printf("\n===== OVERLAP TESTS =====\n");

	test_case("Overlap 01", "ABCDE", 1, 0, 3);
	test_case("Overlap 02", "ABCDE", 0, 1, 4);
	test_case("Overlap 03", "ABCDEFGHIJ", 2, 0, 8);
	test_case("Overlap 04", "ABCDEFGHIJ", 0, 2, 8);
	test_case("Overlap 05", "ABCDEFGHIJ", 3, 1, 7);
	test_case("Overlap 06", "ABCDEFGHIJ", 1, 3, 7);
	test_case("Overlap 07", "ABCDEFGHIJ", 4, 0, 10);
	test_case("Overlap 08", "ABCDEFGHIJ", 0, 4, 6);
	test_case("Overlap 09", "ABCDEFGHIJ", 1, 0, 9);
	test_case("Overlap 10", "ABCDEFGHIJ", 0, 1, 9);

	printf("\n===== DIFFERENT LENGTHS =====\n");

	test_case("Length 00", "ABCDEFGHIJKLMNOPQRSTUVWXYZ", 5, 0, 0);
	test_case("Length 01", "ABCDEFGHIJKLMNOPQRSTUVWXYZ", 5, 0, 1);
	test_case("Length 02", "ABCDEFGHIJKLMNOPQRSTUVWXYZ", 5, 0, 2);
	test_case("Length 03", "ABCDEFGHIJKLMNOPQRSTUVWXYZ", 5, 0, 3);
	test_case("Length 04", "ABCDEFGHIJKLMNOPQRSTUVWXYZ", 5, 0, 4);
	test_case("Length 05", "ABCDEFGHIJKLMNOPQRSTUVWXYZ", 5, 0, 5);
	test_case("Length 06", "ABCDEFGHIJKLMNOPQRSTUVWXYZ", 5, 0, 10);
	test_case("Length 07", "ABCDEFGHIJKLMNOPQRSTUVWXYZ", 5, 0, 15);
	test_case("Length 08", "ABCDEFGHIJKLMNOPQRSTUVWXYZ", 0, 5, 1);
	test_case("Length 09", "ABCDEFGHIJKLMNOPQRSTUVWXYZ", 0, 5, 5);
	test_case("Length 10", "ABCDEFGHIJKLMNOPQRSTUVWXYZ", 0, 5, 10);

	printf("\n===== BINARY DATA TESTS =====\n");

	test_binary("Binary 01", 0, 10, 20);
	test_binary("Binary 02", 10, 0, 20);
	test_binary("Binary 03", 1, 0, 50);
	test_binary("Binary 04", 0, 1, 50);
	test_binary("Binary 05", 25, 10, 30);
	test_binary("Binary 06", 10, 25, 30);
	test_binary("Binary 07", 0, 0, 100);
	test_binary("Binary 08", 50, 0, 50);
	test_binary("Binary 09", 0, 50, 50);

	printf("\n===== RANDOM TESTS =====\n");

	srand(42);
	i = 0;
	while (i < 1000)
	{
		unsigned char expected[100];
		unsigned char actual[100];
		size_t j;

		j = 0;
		while (j < sizeof(expected))
		{
			expected[j] = (unsigned char)(rand() % 256);
			actual[j] = expected[j];
			j++;
		}

		dest = rand() % 70;
		src = rand() % 70;
		n = rand() % 31;

		memmove(expected + dest, expected + src, n);
		ft_memmove(actual + dest, actual + src, n);

		snprintf(name, sizeof(name), "Random test %zu", i + 1);

		if (memcmp(expected, actual, sizeof(expected)) == 0)
			print_status(name, 1);
		else
		{
			print_status(name, 0);
			printf("   dest = %zu, src = %zu, n = %zu\n",
					dest, src, n);
			break;
		}
		i++;
	}

	printf("\n===== SUMMARY =====\n");
	printf("Total tests : %d\n", g_tests);
	printf("Failed      : %d\n", g_failed);

	if (g_failed == 0)
		printf("🎉 ALL TESTS PASSED!\n");
	else
		printf("⚠️ SOME TESTS FAILED!\n");

	return (g_failed != 0);
}
    */