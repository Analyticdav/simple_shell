#include "shell.h"
#include <stdlib.h>

/**
 * _atoi - Convert a string to an integer.
 *
 * This function converts a string `s` to an integer
 * and returns the result.
 *
 * @s: The string to convert to an integer.
 * Return: The converted integer, or -1 if conversion fails.
 */
int _atoi(char *s)
{
	int i;
	int a_to_int = 0;

	for (i = 0; s[i] != '\0'; i++)
	{
		a_to_int *= 10;
		if (!(s[i] >= 48 && s[i] <= 57))
			return (-1);

		a_to_int += s[i] - 48;

	}
	return (a_to_int);
}

/**
 * _strcat - Concatenate two strings.
 *
 * This function concatenates two strings `s1` and `s2`. It returns a newly
 * allocated string containing the concatenated result.
 *
 * @s1: The first string.
 * @s2: The second string.
 * Return: Pointer to the concatenated string, or NULL on failure.
 */
char *_strcat(char *s1, char *s2)
{
	int i;
	char *arr;
	int l_s1, l_s2;

	l_s1 = _strlen(s1);
	l_s2 = _strlen(s2);

	arr = malloc(l_s1 + l_s2 + 2);
	if (arr == NULL)
		return (NULL);
	i = 0;
	while (i < l_s1)
	{
		arr[i] = s1[i];
		i++;
	}
	i = 0;
	while (i < l_s2)
	{
		arr[l_s1 + i + 1] = s2[i];
		i++;
	}
	arr[l_s1 + l_s2 + 1] = '\0';
	return (arr);
}
