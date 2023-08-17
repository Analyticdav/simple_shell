#include "shell.h"

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
