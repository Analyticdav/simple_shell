#ifndef SHELL_H_
#define SHELL_H_

#define PROMPT_SYMBOL "($) "
void prompt(char *env[]);
int _strlen(char *s);
void HANDLE_CTRL_C(int signum);
void execute_command(char *cmd, char **env);
int _strcmp(char *s1, char *s2);
char *extract_path(char **env);
char *_strcat(char *s1, char *s2);

#endif /*!SHELL_H_*/
