#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/stat.h>

/**
 * HANDLE_CTRL_C - Handle the Ctrl+C signal.
 *
 * This function handles the Ctrl+C signal by writing
 * a newline character and the shell prompt symbol
 * to the standard output.
 *
 * @signum: The signal number (unused).
 */
void HANDLE_CTRL_C(int signum)
{
	(void) signum;
	write(STDOUT_FILENO, "\n", 1);
	write(STDOUT_FILENO, PROMPT_SYMBOL, _strlen(PROMPT_SYMBOL));
}

/**
 * handle_path_to_cmd - Handle the command with explicit path.
 *
 * This function extracts the last part of the command
 * from the path, assigns it as the first argument in
 * the 'args' array, and then attempts to execute the command.
 * If execution fails, an error message is printed.
 *
 * @cmd: The full command with path.
 * @env: The environment variables.
 * @args: An array of command arguments.
 */
void handle_path_to_cmd(char *cmd, char **args, char **env)
{
	char *cmd_copy, *cmd_path, *last_token;
	int child_pid, wstatus;

	last_token = NULL;
	cmd_copy = malloc(_strlen(cmd) + 1);
	_strcpy(cmd_copy, cmd); /*Store a copy of the command*/
	cmd_path = strtok(cmd, "/");
	while (cmd_path != NULL)
	{
		last_token = cmd_path;
		cmd_path = strtok(NULL, "/");
	}
	args[0] = last_token;

	if (access(cmd_copy, F_OK) == 0)
	{
		child_pid = fork();
		if (child_pid == 0)
		{
			if (execve(cmd_copy, args, env) != -1)
			{
				free(cmd_copy);
				perror(SHELL_NAME);
			}
			exit(0);
		}
		else
			wait(&wstatus);
	}
	free(cmd_copy);
}
/**
 * handle_cmd - Handle the command with search through PATH.
 *
 * This function searches for the command in the directories
 * specified by the PATH environment variable. It attempts to
 * execute the command with each directory
 * until successful or all directories are exhausted.
 *
 * @cmd: The command to be executed.
 * @env: The environment variables.
 * @args: An array of command arguments.
 */
void handle_cmd(char *cmd, char **args, char **env)
{
	char *cmd_path_prefix, *cmd_path, *path_env_cpy, *path_env;
	int child_pid, wstatus;

	path_env = _getenv("PATH", env);
	path_env_cpy = malloc(_strlen(path_env) + 1);

	_strcpy(path_env_cpy, path_env);
	path_env_cpy[_strlen(path_env)] = '\0';
	cmd_path_prefix = strtok(path_env_cpy, ":");
	while (cmd_path_prefix != NULL)
	{
		cmd_path = _strpathcat(cmd_path_prefix, cmd);
		if (cmd_path == NULL)
		{
			perror(SHELL_NAME);
		}
		if (access(cmd_path, F_OK) == 0)
		{
			child_pid = fork();
			if (child_pid == 0)
			{
				if (execve(cmd_path, args, env) != -1)
				{
					perror(SHELL_NAME);
					free(path_env_cpy);
					free(cmd_path);
				}
			}
			else
			{
				wait(&wstatus);
				free(path_env_cpy);
				free(cmd_path);
				return;
			}
		}
		free(cmd_path);
		cmd_path_prefix = strtok(NULL, ":");
	}
	free(path_env_cpy);
}
/**
 * handle_command_with_args - Handle a command with arguments.
 *
 * This function tokenizes the command string into arguments
 * and stores them in the 'args' array. The linked list
 * 'head' is used to build the argument list.
 *
 * @cmd: The command with arguments.
 * @head: A pointer to the head of a linked list.
 * Return: An array of command arguments.
 */
char **handle_command_with_args(char *cmd, list_t **head)
{
	int i = 0;
	char *token;
	int arg_count = 0;
	char **args;
	list_t *copy;

	token = strtok(cmd, " ");
	add_node_end(head, token);
	/*This checks tokens and add them to the linked list*/
	while (token != NULL)
	{
		add_node_end(head, token);
		token = strtok(NULL, " ");
	}
	arg_count = list_len(*head);
	args = malloc((sizeof(list_t *) * arg_count) + 1);

	copy = (*head)->next; /*Copy the next node for iteration*/
	for (i = 0; copy != NULL; i++)
	{
		args[i] = copy->arg;
		copy = copy->next;
	}
	args[i] = NULL;
	return (args);
}
