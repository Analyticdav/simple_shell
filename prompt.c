#include "shell.h"
#include <stddef.h>
#include <string.h>
#include <syscall.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <sys/wait.h>

void prompt(char *env[])
{
	char *s_line = NULL;
	size_t s_len = 0;
	size_t read = 0;
	int child_pid;
	int wstatus;

	signal(SIGINT, HANDLE_CTRL_C);
	while ((int)read != -1)
	{
		write(STDOUT_FILENO, PROMPT_SYMBOL, _strlen(PROMPT_SYMBOL));
		read = getline(&s_line, &s_len, stdin);
		s_line[read - 1] = '\0';

		if ((int)read == EOF)
		{
			write(STDOUT_FILENO, "\n", 1);
			exit(1);
		}
		child_pid = fork();

		if (child_pid == 0)
		{
			execute_command(s_line, env);
			write(STDOUT_FILENO, "\n", 1);
		}
		else
			wait(&wstatus);
	}
	free(s_line);
}
void execute_command(char *cmd, char** env)
{
	char *args[10];
	char *PATH;
	char *cmd_path_prefix;
	char *cmd_path;

	PATH = extract_path(env);

	args[0] = cmd;
	args[1] = NULL;

	cmd_path_prefix = strtok(PATH, ":");
	while (cmd_path_prefix != NULL)
	{
		cmd_path = _strcat(cmd_path_prefix, cmd);
		if (execve(cmd_path, args, NULL) != -1)
		{
			free(cmd_path);
			break;
		}
		free(cmd_path);
		cmd_path_prefix = strtok(NULL, ":");
	}
	perror(*args);
	exit(1);
}

char *extract_path(char **env)
{
	char *token;
	int i;

	i = 0;
	while (env[i] != 0)
	{
		token = strtok(env[i], "=");
		if (_strcmp(token, "PATH") == 0)
		{
			token = strtok(NULL, "=");
			return (token);
		}
		i++;
	}
	return (NULL);
}
