#ifndef SHELL_H_
#define SHELL_H_

#include <stddef.h>
#define SHELL_NAME "hsh"
#define PROMPT_SYMBOL "($) "
/**
 * struct list_s - A singly linked list node structure.
 *
 * @next: Pointer to the next node in the linked list.
 * @arg: Pointer to a string argument stored in the node.
 */
typedef struct list_s
{
		struct list_s *next;
		char *arg;
} list_t;

void prompt(char *env[]);
int _strlen(char *s);
void HANDLE_CTRL_C(int signum);
void execute_command(char *cmd, char **env);
int _strcmp(char *s1, char *s2);
char *extract_path(char **env);
char *_strcat(char *s1, char *s2);
char *_strpathcat(char *s1, char *s2);
void _strcpy(char *dest, char *src);
char *_strstrp(char *s);
void handle_path_to_cmd(char *cmd, char **args, char **env);
char **handle_command_with_args(char *cmd, list_t **head);
void handle_cmd(char *cmd, char **args, char **env);
size_t list_len(const list_t *h);
list_t *add_node_end(list_t **head, char *str);
void free_list(list_t *head);
char *_getenv(char *_env, char **env);
void check_exit(char *cmd);
int _atoi(char *s);
void handle_shell_file_args(char *file_path, char **env);

#endif /*!SHELL_H_*/
