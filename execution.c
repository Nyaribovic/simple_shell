#include "shell.h"

/**
 * is_executable - Check if a file is an executable command
 * @path: Path to the file
 *
 * Return: 1 if true, 0 otherwise
 */
int is_executable(const char *path)
{
	struct stat st;

	if (!path || stat(path, &st) != 0)
		return (0);

	return (S_ISREG(st.st_mode) && (st.st_mode & S_IXUSR));
}

/**
 * extract_path - Extract a substring from the PATH variable
 * @pathstr: The PATH string
 * @start: Starting index
 * @stop: Stopping index
 *
 * Return: A dynamically allocated string containing the extracted path
 */
char *extract_path(const char *pathstr, int start, int stop)
{
	if (!pathstr || start < 0 || start >= stop)
		return (NULL);

	int length = stop - start;
	char *path = malloc(length + 1);

	if (path)
	{
		strncpy(path, pathstr + start, length);
		path[length] = '\0';
	}

	return (path);
}

/**
 * create_full_path - Create the full path by appending a command to a path
 * @path: The base path
 * @cmd: The command
 *
 * Return: A dynamically allocated string containing the full path
 */
char *create_full_path(const char *path, const char *cmd)
{
	if (!path || !cmd)
		return (NULL);

	char *full_path = malloc(strlen(path) + strlen(cmd) + 2);

	if (full_path)
	{
		sprintf(full_path, "%s/%s", path, cmd);
	}

	return (full_path);
}

/**
 * is_command_executable - Check if a command is executable in a specific path
 * @path: The path to check
 * @cmd: The command to find
 *
 * Return: 1 if true, 0 otherwise
 */
int is_command_executable(const char *path, const char *cmd)
{
	char *full_path = create_full_path(path, cmd);
	int is_exec = 0;

	if (full_path)
	{
		is_exec = is_executable(full_path);
		free(full_path);
	}

	return (is_exec);
}

/**
 * find_command_in_path - Find the command in a given path
 * @path: The path to search
 * @cmd: The command to find
 *
 * Return: The full path to the command or NULL if not found
 */
char *find_command_in_path(const char *path, const char *cmd)
{
	char *full_path = create_full_path(path, cmd);
	char *command_path = NULL;

	if (full_path)
	{
		if (is_command_executable(path, cmd))
		{
			command_path = full_path;
		}
		else
		{
			free(full_path);
		}
	}

	return (command_path);
}
