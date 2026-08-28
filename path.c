#include "main.h"

/**
 * build_full_path - Combines directory, slash, and command into a single path
 * @dir: Directory path
 * @command: Command name
 *
 * Return: Pointer to newly allocated string containing the full path,
 *         or NULL on failure.
 */
char *build_full_path(char *dir, char *command)
{
	size_t len;
	char *full_path;

	len = strlen(dir) + 1 + strlen(command) + 1;
	full_path = malloc(len);

	if (full_path == NULL)
		return (NULL);

	strcpy(full_path, dir);
	strcat(full_path, "/");
	strcat(full_path, command);

	return (full_path);
}

/**
 * _getenv - Gets the value of an environment variable
 * @name: Name of the variable to search for
 *
 * Return: Pointer to the variable value, or NULL if not found.
 */
char *_getenv(const char *name)
{
	int i;
	size_t len;

	if (name == NULL || environ == NULL)
		return (NULL);

	len = strlen(name);

	for (i = 0; environ[i] != NULL; i++)
	{
		if (strncmp(environ[i], name, len) == 0 && environ[i][len] == '=')
			return (environ[i] + len + 1);
	}

	return (NULL);
}

/**
 * get_path - Finds the full executable path of a command using PATH
 * @command: The command name to find
 *
 * Return: Full path to command if found and executable, NULL otherwise.
 */
char *get_path(char *command)
{
	char *path_value;
	char *path_copy;
	char *token;
	char *full_path;
	struct stat st;

	if (command == NULL || command[0] == '\0')
		return (NULL);

	if (strchr(command, '/') != NULL)
	{
		if (stat(command, &st) == 0)
			return (strdup(command));
		return (NULL);
	}
	path_value = _getenv("PATH");
	if (path_value == NULL || path_value[0] == '\0')
		return (NULL);
	path_copy = strdup(path_value);
	if (path_copy == NULL)
		return (NULL);
	token = strtok(path_copy, ":");
	while (token != NULL)
	{
		full_path = build_full_path(token, command);
		if (full_path != NULL)
		{
			if (stat(full_path, &st) == 0)
			{
				free(path_copy);
				return (full_path);
			}
			free(full_path);
		}
		token = strtok(NULL, ":");
	}
free(path_copy);
return (NULL);
}
