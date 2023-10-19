#include "shell.h"

/**
 * _print_string - Prints an input string to stderr.
 * @str: The string to be printed.
 * Return: Nothing.
 */
void _print_string(char *str)
{
	int i = 0;

	if (!str)
		return;

	while (str[i] != '\0')
	{
		_write_character_stderr(str[i]);
		i++;
	}
}

/**
 * _write_character_stderr - Writes a character to stderr.
 * @c: The character to print.
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _write_character_stderr(int c)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(2, buf, i);
		i = 0;
	}

	if (c != BUF_FLUSH)
		buf[i++] = (char)c;

	return (1);
}

/**
 * _write_character_fd - Writes a character to a given file descriptor.
 * @c: The character to print.
 * @fd: The file descriptor to write to.
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _write_character_fd(char c, int fd)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(fd, buf, i);
		i = 0;
	}

	if (c != BUF_FLUSH)
		buf[i++] = c;

	return (1);
}

/**
 * _print_string_fd - Prints an input string to a given file descriptor.
 * @str: The string to be printed.
 * @fd: The file descriptor to write to.
 * Return: The number of characters printed.
 */
int _print_string_fd(char *str, int fd)
{
	int i = 0;

	if (!str)
		return (0);

	while (*str)
	{
		i += _write_character_fd(*str++, fd);
	}

	return (i);
}

/**
 * _write_string_stderr - Writes a string to stderr.
 * @str: The string to print.
 */
void _write_string_stderr(const char *str)
{
	int i = 0;

	if (!str)
		return;

	while (str[i] != '\0')
	{
		_write_character_stderr(str[i]);
		i++;
	}
}
