#include "shell.h"
#include <stdio.h>

/**
 * main - Entry point of the shell program.
 *
 * This function serves as the entry point of the shell program.
 * If the number of arguments is 1, it starts the interactive
 * shell prompt using the prompt function.
 *
 * @argc: The number of command-line arguments.
 * @argv: An array of pointers to command-line arguments.
 * @env: An array of environment variables.
 * Return: Always 0 (Success).
 */
int main(int argc, char *argv[], char *env[])
{
	/* int i; */

	(void) argv;
	if (argc == 1)
	{
		prompt(env);
	}

	return (0);
}
