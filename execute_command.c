#include "main.h"

/**
 * print_error - Prints the standard shell error message to stderr
 * @prog: Program name (e.g. ./hsh)
 * @cmd: Command name (e.g. ls)
 */
void print_error(char *prog, char *cmd)
{
	write(STDERR_FILENO, prog, strlen(prog));
	write(STDERR_FILENO, ": 1: ", 5);
	write(STDERR_FILENO, cmd, strlen(cmd));
	write(STDERR_FILENO, ": not found\n", 12);
}

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
		print_error(program_name, args[0]);
		/* في حال كان غير تفاعلي (Piped)، يجب الخروج بكود 127 */
		if (!isatty(STDIN_FILENO))
			exit(127);
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