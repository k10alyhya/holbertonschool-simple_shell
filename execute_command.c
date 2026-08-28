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
	char *actual_path;
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

	actual_path = get_path(args[0]);
	if (actual_path == NULL)
	{
		perror(program_name);
		return;
	}

	pid = fork();

	if (pid == -1)
	{
		perror("fork");
		free(actual_path);
		return;
	}

	if (pid == 0)
	{
		if (execve(actual_path, args, environ) == -1)
		{
			perror(program_name);
			free(actual_path);
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		wait(NULL);
		free(actual_path);
	}
}