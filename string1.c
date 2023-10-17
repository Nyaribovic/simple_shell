#include "shell.h"

/**
 * string_copy - Copy a string from src to dest.
 * @dest: The destination buffer.
 * @src: The source string.
 *
 * Return: A pointer to the destination buffer.
 */
char *string_copy(char *dest, const char *src)
{
	int i = 0;

	if (dest == src || src == NULL)
		return (dest);

	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';

	return (dest);
}

/**
 * string_duplicate - Duplicate a string.
 * @str: The string to duplicate.
 *
 * Return: A pointer to the duplicated string, or NULL on failure.
 */
char *string_duplicate(const char *str)
{
	int length = 0;
	char *duplicate;

	if (str == NULL)
		return (NULL);

	while (str[length] != '\0')
		length++;

	duplicate = malloc(sizeof(char) * (length + 1));
	if (duplicate == NULL)
		return (NULL);

	string_copy(duplicate, str);
	return (duplicate);
}

/**
 * string_print - Print a string to stdout.
 * @str: The string to be printed.
 *
 * Return: Nothing.
 */
void string_print(const char *str)
{
	if (str == NULL)
		return;

	while (*str != '\0')
	{
		character_print(*str);
		str++;
	}
}

/**
 * character_print - Write a character to stdout.
 * @c: The character to print.
 *
 * Return: On success, 1. On error, -1 is returned.
 */
int character_print(char c)
{
	static int i;
	static char buffer[WRITE_BUF_SIZE];

	if (c == 1 || i >= WRITE_BUF_SIZE)
	{
		write(1, buffer, i);
		i = 0;
	}

	if (c != 1 )
		buffer[i++] = c;

	return (1);
}
