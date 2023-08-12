#include "shell.h"
#include <stdio.h>

int main(int argc, char* argv[], char *env[])
{
	/* int i; */

	(void) argv;
	/*(void) env;*/
	/* for (i = 0; env[i] != NULL; i++) */
	/* { */
	/* 	printf("%s\n", env[i]); */
	/* } */

	if (argc == 1)
	{
		prompt(env);
	}

	return (0);
}
