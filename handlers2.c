#include "shell.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

/**
 * handle_shell_file_args - Execute commands from a
 * shell script file.
 *
 * @file_path: Path to the shell script file.
 * @env: An array of environment variables.
 */
void handle_shell_file_args(char *file_path, char **env)
{
	int file_d, i;
	char r_char[1], buffer[1024];
	(void) env;

	file_d = open(file_path, O_RDONLY);
	if (file_d < 0)
	{
		perror(SHELL_NAME);
		exit(EXIT_FAILURE);
	}

	i = 0;
	while (read(file_d, r_char, 1) > 0)
	{
		buffer[i] = *r_char;
		if (*r_char == '\n')
		{
			buffer[i] = '\0';
			/* printf("%s\n", buffer); */
			execute_command(buffer, env);
			i = -1;
		}
		i++;
	}
}