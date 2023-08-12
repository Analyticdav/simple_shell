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
	while (1)
	{
		write(STDOUT_FILENO, PROMPT_SYMBOL, _strlen(PROMPT_SYMBOL));
		read = getline(&s_line, &s_len, stdin);
		s_line[read - 1] = '\0';

		if ((int)read == EOF)
		{
			write(STDOUT_FILENO, "\n", 1);
			free(s_line);
			exit(0);
		}
		child_pid = fork();

		if (child_pid == 0)
		{
			execute_command(s_line, env);
			exit(0);
		}
		else
			wait(&wstatus);
	}
	free(s_line);
}
void execute_command(char *cmd, char** env)
{
	char *args[10];
	char *path_env;
	char *cmd_path_prefix, *cmd_copy;
	char *cmd_path, *last_token;

	/*Check if the command is a path*/
	/*If it is, execute it instead*/
	if (*cmd == '/')
	{
		last_token = NULL;
		cmd_copy = malloc(_strlen(cmd));
		_strcpy(cmd_copy, cmd); /*Store a copy of the command*/
		cmd_path = strtok(cmd, "/");
		while (cmd_path != NULL)
		{
			last_token = cmd_path;
			cmd_path = strtok(NULL, "/");
		}
		args[0] = last_token;
		args[1] = NULL;
		if (execve(cmd_copy, args, env) != -1)
		{
			perror(cmd);
			exit(EXIT_FAILURE);
		}
		free(cmd_copy);
	}
	path_env = extract_path(env);
	if (path_env == NULL)
	{
		perror(cmd);
		exit(EXIT_FAILURE);
	}

	args[0] = cmd;
	args[1] = NULL;

	cmd_path_prefix = strtok(path_env, ":");
	while (cmd_path_prefix != NULL)
	{
		cmd_path = _strcat(cmd_path_prefix, cmd);
		if (cmd_path == NULL)
		{
			perror(cmd);
			exit(EXIT_FAILURE);
		}
		if (execve(cmd_path, args, env) != -1)
		{
			free(cmd_path);
			break;
		}
		free(cmd_path);
		cmd_path_prefix = strtok(NULL, ":");
	}
	perror(*args);
	exit(EXIT_FAILURE);
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
