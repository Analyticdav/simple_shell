#include "shell.h"
#include <stdarg.h>
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
 * @env: An array of environment variables
 */
void prompt(char **env)
{
	char *s_line = NULL;
	size_t s_len = 0;
	size_t read = 0;

	signal(SIGINT, HANDLE_CTRL_C);
	while (1)
	{
		write(STDOUT_FILENO, PROMPT_SYMBOL, _strlen(PROMPT_SYMBOL));
		read = getline(&s_line, &s_len, stdin);

		if ((int)read == -1)
		{
			/*write(STDOUT_FILENO, "\n", 1);*/
			free(s_line);
			exit(0);
		}

		s_line[read - 1] = '\0';

		check_exit(s_line);
		execute_command(s_line, env);
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
		handle_path_to_cmd(cmd, args, env);
		free(args);
		free_list(head);
		return;
	}
	handle_cmd(cmd, args, env);
	free(args);
	free_list(head);
}
/**
 * _getenv - Extract the requested environment variable @_env.
 *
 * This function searches through the environment variables
 * for the _env variable and returns its value, which
 *
 * @_env: environment variable to extract.
 * @env: An array of environment variable.
 * Return: Pointer to the variable value, or NULL if not found.
 */
char *_getenv(char *_env, char **env)
{
	int i, j;
	char **env_cpy;
	int env_found = 0;

	env_cpy = env;
	i = 0;
	while (env_cpy[i] != NULL && env_found == 0)
	{
		for (j = 0; env_cpy[i][j] != '=' && _env[j] != '\0'; j++)
		{
			if (env_cpy[i][j] != _env[j])
			{
				env_found = 0;
				break;
			}
			env_found = 1;
		}
		if (env_found)
			return (env_cpy[i]);
		i++;
	}
	return (NULL);
}

/**
 * print_env - print out all environment variables.
 *
 * @env: An array of environment variable.
 */
void print_env(char **env)
{
	int i = 0;
	char **p_env, new_line = '\n';

	p_env = env;
	while (p_env[i] != NULL)
	{
		write(STDOUT_FILENO, p_env[i], _strlen(p_env[i]));
		write(STDOUT_FILENO, &new_line, 1);
		i++;
	}
}
/**
 * check_exit - Check and handle the 'exit' command.
 *
 * This function checks if the command matches the 'exit' command and,
 * if so, extracts the exit status argument and terminates the
 * shell with the provided status code.
 *
 * @cmd: The command to check for the 'exit' command.
 */
void check_exit(char *cmd)
{
	int i, j, exit_status;
	char *exit_arg;
	char _exit[] = "exit";

	i = j = 0;
	while (_exit[i] != '\0')
	{
		if (cmd[i] != _exit[i])
			return;
		i++;
	}
	if (cmd[i] == '\0')
	{
		free(cmd);
		exit(0);
	}
	exit_arg = cmd + i + 1;

	exit_status = _atoi(exit_arg);

	if (exit_status == -1)
	{
		free(cmd);
		write(STDOUT_FILENO, SHELL_NAME ": numeric argument required\n", 32);
		exit(2);
	}
	free(cmd);
	exit(exit_status);
}
