#include "shell.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * _strcmp - Compare two strings.
 *
 * This function compares two strings `s1` and `s2` and returns:
 * - Negative value if `s1` is less than `s2`.
 * - Positive value if `s1` is greater than `s2`.
 * - 0 if `s1` is equal to `s2`.
 *
 * @s1: The first string to compare.
 * @s2: The second string to compare.
 * Return: Comparison result.
 */
int _strcmp(char *s1, char *s2)
{
	int i;
	int l_s1, l_s2;

	l_s1 = _strlen(s1);
	l_s2 = _strlen(s2);
	i = 0;

	if (l_s1 != l_s2)
		return (l_s1 - l_s2);
	while (s1[i] != '\0')
	{
		if (s1[i] != s2[i])
			return (-1);
		i++;
	}
	return (0);
}
/**
 * _strlen - Calculate the length of a string.
 *
 * This function calculates and returns the length of the string `s`.
 *
 * @s: The string for which length is calculated.
 * Return: Length of the string.
 */
int _strlen(char *s)
{
	int i;

	i = 0;
	while (s[i] != '\0')
		++i;
	return (i);
}
/**
 * _strcat - Concatenate two strings with a '/' in between.
 *
 * This function concatenates two strings `s1` and `s2` with a '/'
 * character in between them. It returns a newly
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
	arr[i] = '/';
	i = 0;
	while (i < l_s2)
	{
		arr[l_s1 + i + 1] = s2[i];
		i++;
	}
	arr[l_s1 + l_s2 + 1] = '\0';
	return (arr);
}
/**
 * _strcpy - Copy a string from source to destination.
 *
 * This function copies the string from source `src` to destination `dest`.
 *
 * @dest: The destination buffer.
 * @src: The source string.
 */
void _strcpy(char *dest, char *src)
{
	int i;

	i = 0;
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
}
/**
 * _strstrp - Find the first non-whitespace character in a string.
 *
 * This function searches for the first non-whitespace character in the string
 * and returns a pointer to it.
 *
 * @s: The string to search.
 * Return: Pointer to the first non-whitespace character, or NULL if not found.
 */
char *_strstrp(char *s)
{
	int i;

	for (i = 0; s[i] == ' ' || s[i] == '\t' || s[i] == '\n'; i++)
	{};

	s = s + i;
	return (s);
}
