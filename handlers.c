#include "shell.h"
#include <unistd.h>

void HANDLE_CTRL_C(int signum)
{
	(void) signum;
	write(STDOUT_FILENO, "\n", 1);
	write(STDOUT_FILENO, PROMPT_SYMBOL, _strlen(PROMPT_SYMBOL));
	return;
}
