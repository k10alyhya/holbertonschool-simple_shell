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
 * handle_builtin - Handles shell built-in commands
 * @args: Command arguments
 * @line: Input buffer
 * @last_status: Status of the last command
 *
 * Return: 1 if a built-in was handled, otherwise 0
 */
int handle_builtin(char **args, char *line, int *last_status)
{
	int i;

	if (strcmp(args[0], "exit") == 0)
	{
		free(line);
		exit(*last_status);
	}

	if (strcmp(args[0], "env") == 0)
	{
		for (i = 0; environ[i] != NULL; i++)
		{
			write(STDOUT_FILENO, environ[i], strlen(environ[i]));
			write(STDOUT_FILENO, "\n", 1);
		}
		*last_status = 0;
		return (1);
	}

	return (0);
}

/**
 * run_command - Runs an executable command
 * @args: Command arguments
 * @path: Full executable path
 * @line: Input buffer
 * @last_status: Status of the last command
 */
void run_command(char **args, char *path, char *line, int *last_status)
{
	pid_t pid;
	int status;

	pid = fork();

	if (pid == -1)
	{
		perror("fork");
		free(path);
		return;
	}

	if (pid == 0)
	{
		if (execve(path, args, environ) == -1)
		{
			free(path);
			free(line);
			exit(EXIT_FAILURE);
		}
	}

	wait(&status);

	if (WIFEXITED(status))
		*last_status = WEXITSTATUS(status);

	free(path);
}

/**
 * execute_command - Executes a command or built-in
 * @line: Command line to execute
 * @program_name: Name of the shell program
 */
void execute_command(char *line, char *program_name)
{
	char *args[64];
	char *token;
	char *actual_path;
	static int last_status;
	int i = 0;

	token = strtok(line, " \t");

	while (token != NULL && i < 63)
	{
		args[i++] = token;
		token = strtok(NULL, " \t");
	}

	args[i] = NULL;

	if (args[0] == NULL || handle_builtin(args, line, &last_status))
		return;

	actual_path = get_path(args[0]);

	if (actual_path == NULL)
	{
		print_error(program_name, args[0]);
		last_status = 127;
		return;
	}

	run_command(args, actual_path, line, &last_status);
}
