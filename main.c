#include "main.h"

/**
 * main - Entry point for the simple shell
 * @argc: Number of command-line arguments
 * @argv: Array of command-line arguments
 *
 * Return: Always 0
 */
int main(int argc, char **argv)
{
	char *line = NULL;
	char *command;
	size_t size = 0;
	ssize_t chars_read;

	(void)argc;

	while (1)
	{
		if (isatty(STDIN_FILENO))
		{
			printf("$ ");
			fflush(stdout);
		}

		chars_read = getline(&line, &size, stdin);

		if (chars_read == -1)
			break;

		if (chars_read > 0 && line[chars_read - 1] == '\n')
			line[chars_read - 1] = '\0';

		command = trim_spaces(line);

		if (command[0] == '\0')
			continue;

		execute_command(command, argv[0]);
	}

	free(line);

	return (0);
}
