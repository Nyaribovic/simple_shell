#include "shell.h"

/**
 * read_history_from_file - Read command history from a file
 * @info: Pointer to the parameter struct
 * @filename: The name of the history file
 *
 * Return: Histcount on success, 0 on failure
 */
int read_history_from_file(info_t *info, char *filename)
{
	char *buf = read_history_from_file_internal(info, filename);

	if (buf == NULL)
		return (0);

	int linecount = 0;
	int last = 0;

	for (ssize_t i = 0; i < _strlen(buf); i++)
	{
		if (buf[i] == '\n')
		{
			buf[i] = '\0';
			build_history_list(info, buf + last, linecount++);
			last = i + 1;
		}
	}

	if (last != _strlen(buf))
		build_history_list(info, buf + last, linecount++);

	free(buf);
	info->histcount = linecount;

	while (info->histcount-- >= HIST_MAX)
		delete_node_at_index(&(info->history), 0);

	renumber_history(info);

	return (info->histcount);
}

/**
 * build_history_list - Add an entry to the history linked list
 * @info: Pointer to the parameter struct
 * @buf: Buffer
 * @linecount: History line count
 *
 * Return: Always 0
 */
int build_history_list(info_t *info, char *buf, int linecount)
{
	list_t *node = NULL;

	if (info->history)
		node = info->history;

	add_node_end(&node, buf, linecount);

	if (!info->history)
		info->history = node;

	return (0);
}
