#include "shell.h"

/**
 * read_input_buffer - Read input into a buffer.
 * @info: Structure containing potential arguments.
 * @buf: Address of the buffer to read input into.
 * @len: Address of the length variable.
 *
 * Return: Bytes read.
 */
ssize_t read_input_buffer(info_t *info, char **buf, size_t *len)
{
	ssize_t bytes_read = 0;
	size_t len_p = 0;

	if (!*len)
	{
		free(*buf);
		*buf = NULL;
		signal(SIGINT, sigintHandler);
		#if USE_GETLINE
		bytes_read = getline(buf, &len_p, stdin);
		#else
		bytes_read = custom_getline(info, buf, &len_p);
		#endif

		if (bytes_read > 0)
		{
			handle_input(info, buf, &len, bytes_read);
		}
	}
	return (bytes_read);
}

/**
 * get_input_line - Get a line without the newline character.
 * @info: Structure containing potential arguments.
 *
 * Return: Bytes read.
 */
ssize_t get_input_line(info_t *info)
{
	static char *cmd_chain_buffer;
	static size_t current_pos, chain_start_pos, buffer_len;
	ssize_t bytes_read = 0;
	char **buf_ptr = &(info->arg), *current_command;

	_putchar(BUF_FLUSH);
	bytes_read = read_input_buffer(info, &cmd_chain_buffer, &buffer_len);
	if (bytes_read == -1)
		return (-1);

	if (buffer_len)
	{
		chain_start_pos = current_pos;
		current_command = cmd_chain_buffer + current_pos;
		process_command_chain(info, cmd_chain_buffer, &chain_start_pos,
		current_pos, buffer_len);
		current_pos = chain_start_pos + 1;

		if (current_pos >= buffer_len)
		{
			reset_buffer_positions(&current_pos, &buffer_len, info);
		}

		*buf_ptr = current_command;
		return (_strlen(current_command));
	}

	*buf_ptr = cmd_chain_buffer;
	return (bytes_read);
}

/**
 * custom_getline - Gets the next line of input from STDIN.
 * @info: Structure containing potential arguments.
 * @ptr: Address of the pointer to the buffer, preallocated or NULL.
 * @length: Size of the preallocated ptr buffer if not NULL.
 * Return: Bytes read.
 */
int custom_getline(info_t *info, char **ptr, size_t *length)
{
	static char buffer[READ_BUF_SIZE];
	static size_t current_pos, buffer_len;
	size_t k;
	ssize_t bytes_read = 0, total_bytes_read = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && length)
		total_bytes_read = *length;

	if (current_pos == buffer_len)
	{
		current_pos = buffer_len = 0;
	}

	do	{
		bytes_read = read_input_buffer(info, buffer, &buffer_len);

		if (bytes_read == -1 || (bytes_read == 0 && buffer_len == 0))
			return (-1);

		c = strchr(buffer + current_pos, '\n');
		k = c ? 1 + (size_t)(c - buffer) : buffer_len;
		new_p = _realloc(p, total_bytes_read, total_bytes_read ?
		total_bytes_read + k : k + 1);

		if (!new_p)
		{
			handle_memory_error(p);
			return (-1);
		}
		handle_buffer(info, &p, &new_p, total_bytes_read,
		buffer + current_pos, k - current_pos);

		current_pos = k;
	} while (!c);

	*ptr = p;
	return (total_bytes_read);
}

/**
 * sigintHandler - Blocks Ctrl-C.
 * @sig_num: The signal number.
 * Return: void
 */
void sigintHandler(__attribute__((unused)) int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}
