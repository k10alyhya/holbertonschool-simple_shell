#include "main.h"

/**
 * execute_command - Executes a command in a child process
 * @line: Command to execute
 * @program_name: Name of the shell program
 */
void execute_command(char *line, char *program_name)
{
	char *argv[2];
	pid_t pid;

	argv[0] = line;
	argv[1] = NULL;

	pid = fork();

	if (pid == -1)
	{
		perror("fork");
		return;
	}

	if (pid == 0)
	{
		if (execve(line, argv, environ) == -1)
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
