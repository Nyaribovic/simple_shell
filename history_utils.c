#include "shell.h"

/**
 * get_history_file - Get the history file path
 * @info: Pointer to the parameter struct
 *
 * Return: Allocated string containing the history file path
 */
char *get_history_file(info_t *info)
{
	char *home_dir = _getenv(info, "HOME=");

	if (!home_dir)
		return (NULL);

	char *history_file = malloc(_strlen(home_dir) + _strlen(HIST_FILE) + 2);

	if (!history_file)
		return (NULL);

	_strcpy(history_file, home_dir);
	_strcat(history_file, "/");
	_strcat(history_file, HIST_FILE);

	return (history_file);
}

/**
 * write_history_to_file_internal - Write history to file
 * @info: Pointer to the parameter struct
 * @filename: The name of the history file
 *
 * Return: 1 on success, -1 on failure
 */
int write_history_to_file_internal(info_t *info, char *filename)
{
	ssize_t fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);

	if (fd == -1)
		return (-1);

	list_t *node = info->history;

	while (node)
	{
		_putsfd(node->str, fd);
		_putfd('\n', fd);
		node = node->next;
	}

	_putfd(BUF_FLUSH, fd);
	close(fd);

	return (1);
}

/**
 * read_history_from_file_internal - Read history from file
 * @info: Pointer to the parameter struct
 * @filename: The name of the history file
 *
 * Return: A string containing the history contents, or NULL on failure
 */
char *read_history_from_file_internal(info_t *info, char *filename)
{
	ssize_t fd = open(filename, O_RDONLY);

	if (fd == -1)
		return (NULL);

	struct stat st;

	if (fstat(fd, &st) != 0)
	{
		close(fd);
		return (NULL);
	}

	char *buf = malloc(st.st_size + 1);

	if (!buf)
	{
		close(fd);
		return (NULL);
	}

	ssize_t rdlen = read(fd, buf, st.st_size);

	close(fd);

	if (rdlen <= 0)
	{
		free(buf);
		return (NULL);
	}

	buf[st.st_size] = '\0';

	return (buf);
}
