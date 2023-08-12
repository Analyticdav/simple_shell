#include "shell.h"
#include <stdio.h>
#include <stdlib.h>

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
int _strlen(char *s)
{
	int i;

	i = 0;
	while (s[i] != '\0')
		++i;
	return (i);
}
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
	while(i < l_s1)
	{
		arr[i] = s1[i];
		i++;
	}
	arr[i] = '/';
	i = 0;
	while(i < l_s2)
	{
		arr[l_s1 + i + 1] = s2[i];
		i++;
	}
	arr[l_s1 + l_s2 + 1] = '\0';
	return (arr);
}
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
