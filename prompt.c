#include "shell.h"
#include <stddef.h>
#include <string.h>
#include <syscall.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <sys/wait.h>

/**
 * prompt - Display a shell prompt and execute user commands.
 *
 * This function displays the shell prompt symbol and
 * continuously reads user input commands. It executes
 * the entered command using the execute_command function.
 *
 * @env: An array of environment variables.
 */
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

		if ((int)read == -1)
		{
			write(STDOUT_FILENO, "\n", 1);
			free(s_line);
			exit(0);
		}

		s_line[read - 1] = '\0';

		if (_strcmp(_strstrp(s_line), "exit") == 0)
		{
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
/**
 * execute_command - Execute a user command.
 *
 * This function prepares and executes a user command by
 * parsing the input command string, handling path-specific
 * commands, and managing child processes.
 *
 * @cmd: The user command to execute.
 * @env: An array of environment variables.
 */
void execute_command(char *cmd, char **env)
{
	char **args;
	list_t *head = NULL;

	cmd = _strstrp(cmd);
	if (*cmd == 0)
		return;
	args = handle_command_with_args(cmd, &head);
	/*Check if the command is a path. If it is, execute it instead*/
	if (*cmd == '/')
	{
		handle_path_to_cmd(cmd, env, args);
		free(args);
		return;
	}
	handle_cmd(cmd, env, args);
	perror(SHELL_NAME);
	free(args);
	free_list(head);
}
/**
 * extract_path - Extract the PATH environment variable.
 *
 * This function searches through the environment variables
 * for the PATH variable and returns its value, which
 * represents the directories to search for executables.
 *
 * @env: An array of environment variables.
 * Return: Pointer to the PATH value, or NULL if not found.
 */
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
