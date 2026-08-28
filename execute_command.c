#include "main.h"

/**
 * print_error - Prints the standard shell error message to stderr
 * @prog: Program name
 * @cmd: Command name
 */
void print_error(char *prog, char *cmd)
{
	write(STDERR_FILENO, prog, strlen(prog));
	write(STDERR_FILENO, ": 1: ", 5);
	write(STDERR_FILENO, cmd, strlen(cmd));
	write(STDERR_FILENO, ": not found\n", 12);
}

/**
 * execute_command - Executes a command or built-in in a child process
 * @line: Command line to execute
 * @program_name: Name of the shell program
 */
void execute_command(char *line, char *program_name)
{
	char *args[64];
	char *token;
	char *actual_path;
	int i = 0, j, status;
	static int last_status;
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

	if (strcmp(args[0], "exit") == 0)
	{
		free(line);
		exit(last_status);
	}

	if (strcmp(args[0], "env") == 0)
	{
		for (j = 0; environ[j] != NULL; j++)
		{
			write(STDOUT_FILENO, environ[j], strlen(environ[j]));
			write(STDOUT_FILENO, "\n", 1);
		}
		last_status = 0;
		return;
	}

	actual_path = get_path(args[0]);
	if (actual_path == NULL)
	{
		print_error(program_name, args[0]);
		last_status = 127;
		if (!isatty(STDIN_FILENO))
		{
			free(line);
			exit(127);
		}
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
			free(line);
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		wait(&status);
		if (WIFEXITED(status))
			last_status = WEXITSTATUS(status);
		free(actual_path);
	}
}