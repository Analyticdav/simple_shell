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

/**
 * handle_cd - Change the current working directory.
 *
 * @cmd: The command containing the arguments
 * for changing the directory.
 * @env: An array of environment variables.
 * Return: 0 on success, -1 on failure.
 */
int handle_cd(char *cmd, char **env)
{
	char *token, *HOME, *home_token, *PREV_PWD, *prev_token;
	int i = 0;
	char CD[] = "cd";

	while (cmd[i] != '\0' || CD[i] != '\0')
	{
		if (CD[i] == '\0')
			break;
		if (cmd[i] != CD[i])
			return (-1);
		i++;
	}
	token = strtok(cmd, " ");
	token = strtok(NULL, " ");
	if (token == NULL)
	{
		HOME = _getenv("HOME", env);
		if (HOME != NULL)
		{
			home_token = strtok(HOME, "=");
			home_token = strtok(NULL, "=");
			chdir(home_token);
		}
	}
	else if (_strcmp(token, "-") == 0)
	{
		PREV_PWD = _getenv("OLDPWD", env);
		if (HOME != NULL)
		{
			prev_token = strtok(PREV_PWD, "=");
			prev_token = strtok(NULL, "=");
			chdir(prev_token);
		}
	}
	else
		perror(cmd);
	return (0);
}
