#include "shell.h"
#include <stdio.h>

/**
 * interactive - checks if the shell is in interactive mode
 * @info: pointer to info_t struct
 *
 * Return: 1 if interactive mode, 0 otherwise
 */
int interactive(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * is_delim - checks if a character is a delimiter
 * @c: the character to check
 * @delim: string containing delimiters
 *
 * Return: 1 if true, 0 if false
 */
int is_delim(char c, const char *delim)
{
	while (*delim)
	{
	if (*delim == c)
		return (1);
	delim++;
	}
	return (0);
}

/**
 * _isalpha - checks if a character is alphabetic
 * @c: the character to check
 *
 * Return: 1 if c is alphabetic, 0 otherwise
 */
int _isalpha(int c)
{
	return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));
}

/**
 * _atoi - converts a string to an integer
 * @s: the string to be converted
 *
 * Return: the converted number if valid, 0 otherwise
 */
int _atoi(char *s)
{
	int i = 0;
	int sign = 1;
	int result = 0;

	/* Handle leading whitespace */
	while (s[i] == ' ')
		i++;

	/* Handle sign */
	if (s[i] == '-')
	{
		sign = -1;
		i++;
	}

	/* Calculate the integer value */
	while (s[i] >= '0' && s[i] <= '9')
	{
		result = result * 10 + (s[i] - '0');
		i++;
	}

	return (result * sign);
}
