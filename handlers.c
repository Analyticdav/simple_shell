#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

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
void handle_path_to_cmd(char *cmd, char **env, char **args)
{
	char *cmd_copy;
	char *cmd_path, *last_token;

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

	if (execve(cmd_copy, args, env) != -1)
	{
		free(cmd_copy);
		perror(SHELL_NAME);
		exit(EXIT_FAILURE);
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
void handle_cmd(char *cmd, char **env, char **args)
{
	char *path_env, *cmd_path_prefix, *cmd_path;

	path_env = extract_path(env);
	if (path_env == NULL)
	{
		perror("No such file or directory");
		exit(EXIT_FAILURE);
	}
	cmd_path_prefix = strtok(path_env, ":");
	while (cmd_path_prefix != NULL)
	{
		cmd_path = _strcat(cmd_path_prefix, cmd);
		if (cmd_path == NULL)
		{
			perror(SHELL_NAME);
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
