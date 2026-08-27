#include "main.h"

/**
 * trim_spaces - Removes leading and trailing spaces from input
 * @line: Input string
 *
 * Return: Pointer to trimmed string
 */
char *trim_spaces(char *line)
{
	char *end;

	while (*line == ' ' || *line == '\t')
		line++;

	if (*line == '\0')
		return (line);

	end = line;

	while (*end != '\0')
		end++;

	end--;

	while (end > line && (*end == ' ' || *end == '\t'))
	{
		*end = '\0';
		end--;
	}

	return (line);
}
