#include "shell.h"

int renumber_history(info_t *info);

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

/**
 * handle_open_file_error - Handle open file error
 * @prog_name: Name of the program (usually argv[0])
 * @file_name: Name of the file that could not be opened (usually argv[1])
 */
void handle_open_file_error(const char *prog_name, const char *file_name)
{
	_write_string_stderr(prog_name);
	_write_string_stderr(": cannot open ");
	_write_string_stderr(file_name);
	_write_string_stderr("\n");
}

/**
 * read_command_history - Read command history from a file into a linked list
 * @info: A pointer to the info_t structure
 *
 * Return: Number of history entries read
 */
int read_command_history(info_t *info)
{
	char *buf = read_history_from_file_internal(info, HIST_FILE);

	if (buf == NULL)
		return (0);

	int linecount = 0;
	int last = 0;
	size_t buf_length = _strlen(buf);

	for (size_t i = 0; i < buf_length; i++)
	{
		if (buf[i] == '\n')
		{
			buf[i] = '\0';
			build_history_list(info, buf + last, linecount++);
			last = i + 1;
		}
	}

	if (last != buf_length)
		build_history_list(info, buf + last, linecount++);

	free(buf);
	info->histcount = linecount;

	while (info->histcount >= HIST_MAX)
	{
		delete_node_at_index(&(info->history), 0);
		info->histcount--;
	}

	renumber_history(info);

	return (info->histcount);
}
