#include "shell.h"

/**
 * _custom_strncpy - Copies a string.
 * @dest: The destination string to be copied to.
 * @src: The source string.
 * @n: The number of characters to be copied.
 *
 * Return: The concatenated string.
 */
char *_custom_strncpy(char *dest, const char *src, size_t n)
{
	size_t i;

	for (i = 0; i < n && src[i] != '\0'; i++)
	{
		dest[i] = src[i];
	}

	dest[i] = '\0'; /* Ensure null-terminated string */

	return (dest);
}

/**
 * _custom_strncat - Concatenates two strings.
 * @dest: The destination string.
 * @src: The source string.
 * @n: The maximum number of characters to concatenate.
 *
 * Return: The concatenated string.
 */
char *_custom_strncat(char *dest, const char *src, size_t n)
{
	size_t dest_len = strlen(dest);
	size_t i;

	for (i = 0; i < n && src[i] != '\0'; i++)
	{
		dest[dest_len + i] = src[i];
	}

	dest[dest_len + i] = '\0'; /* Ensure null-terminated string */

	return (dest);
}

/**
 * _custom_strchr - Locates a character in a string.
 * @s: The string to be parsed.
 * @c: The character to look for.
 *
 * Return: A pointer to the first occurrence of 'c' in 's',
 * or NULL if not found.
 */
char *_custom_strchr(const char *s, int c)
{
	while (*s != '\0')
	{
		if (*s == c)
		{
			return ((char *)s);
		}
		s++;
	}

	return (NULL); /* Character not found */
}
