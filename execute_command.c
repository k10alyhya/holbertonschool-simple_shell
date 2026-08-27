#include "main.h"

/**
 * execute_command - Executes a command in a child process
 * @line: Command line to execute
 * @program_name: Name of the shell program
 */
void execute_command(char *line, char *program_name)
{
	char *args[64];
	char *token;
	int i = 0;
	pid_t pid;

	token = strtok(line, " \t");

	while (token != NULL && i < 63)
	{
		args[i] = token;
		i++;
		token = strtok(NULL, " \t");
	}

	args[i] = NULL;

	if (args[0] == NULL)
		return;

	pid = fork();

	if (pid == -1)
	{
		perror("fork");
		return;
	}

	if (pid == 0)
	{
		if (execve(args[0], args, environ) == -1)
		{
			perror(program_name);
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		wait(NULL);
	}
}
