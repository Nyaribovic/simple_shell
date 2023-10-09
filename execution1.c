#include "shell.h"

/**
 * split_path - Split the PATH variable into individual paths
 * @pathstr: The PATH string
 *
 * Return: An array of strings containing individual paths
 */
char **split_path(const char *pathstr)
{
	if (!pathstr)
		return (NULL);

	char **paths = NULL;
	int path_count = 0, i = 0, start = 0;

	while (pathstr[i])
	{
		if (pathstr[i] == ':')
		{
			char *path = extract_path(pathstr, start, i);

			if (path)
			{
				paths = realloc(paths, sizeof(char *) * (path_count + 1));
				paths[path_count] = path;
				path_count++;
			}
			start = i + 1;
		}
		i++;
	}

	char *path = extract_path(pathstr, start, i);

	if (path)
	{
		paths = realloc(paths, sizeof(char *) * (path_count + 1));
		paths[path_count] = path;
		path_count++;
	}

	if (path_count == 0)
	{
		free(paths);
		paths = NULL;
	}

	return (paths);
}

/**
 * find_command_path - Find the full path of a command in the PATH variable
 * @pathstr: The PATH string
 * @cmd: The command to find
 *
 * Return: A dynamically allocated string containing the full path of the
 *         the command or NULL if not found
 */
char *find_command_path(const char *pathstr, const char *cmd)
{
	if (!pathstr || !cmd)
		return (NULL);

	if (cmd[0] == '.' && (cmd[1] == '/' || cmd[1] == '\\') && is_executable(cmd))
		return (strdup(cmd));

	char **paths = split_path(pathstr);
	char *command_path = NULL;

	if (paths)
	{
		for (int i = 0; paths[i] != NULL; i++)
		{
			command_path = find_command_in_path(paths[i], cmd);
			if (command_path)
			{
				free(paths);
				return (command_path);
			}
		}
		free(paths);
	}

	return (NULL);
}
