#include "shell.h"

/**
 * _strlen - Returns the length of a string.
 * @s: The string to determine the length of.
 *
 * Return: The length of the string.
 */
int _strlen(const char *s)
{
	int length = 0;

	if (s)
	{
		while (s[length])
		{
			length++;
		}
	}
	return (length);
}

/**
 * _strcmp - Compares two strings lexicographically.
 * @s1: The first string.
 * @s2: The second string.
 *
 * Return: 0 if s1 is equal to s2, a positive value if s1 is greater, and
 * a negative value if s1 is smaller.
 */
int _strcmp(const char *s1, const char *s2)
{
	while (*s1 && *s2 && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	return (*s1 - *s2);
}

/**
 * starts_with - Checks if a string starts with a specific substring.
 * @haystack: The string to search.
 * @needle: The substring to find at the beginning of the haystack.
 *
 * Return: A pointer to the character after the matched substring or NULL.
 */
char *starts_with(const char *haystack, const char *needle)
{
	while (*needle)
	{
		if (*needle != *haystack)
		{
			return (NULL);
		}
		needle++;
		haystack++;
	}
	return ((char *)haystack);
}

/**
 * _strcat - Concatenates two strings.
 * @dest: The destination buffer.
 * @src: The source buffer to append to the destination.
 *
 * Return: A pointer to the destination buffer.
 */
char *_strcat(char *dest, const char *src)
{
	char *destination = dest;

	while (*dest)
	{
		dest++;
	}

	while (*src)
	{
		*dest++ = *src++;
	}

	*dest = '\0';
	return (destination);
}
