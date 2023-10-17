#include "shell.h"

/**
 * count_words - Count the number of words in a string using delimiters.
 * @str: The input string.
 * @delimiters: The delimiter string.
 *
 * Return: The number of words found.
 */
static int count_words(const char *str, char *delimiters)
{
	int nmwords = 0;

	if (str == NULL || str[0] == '\0')
		return 0;

	if (!delimiters)
		delimiters = "	";
	for (int i = 0; str[i] != '\0'; i++)
	{
		if (!is_delim(str[i], delimiters) &&
		(is_delim(str[i + 1], delimiters) || !str[i + 1))
			nmwords++;
	}

	return nmwords;
}

/**
 * split_words - Split a string into words using delimiters.
 * @str: The input string.
 * @delimiters: The delimiter string.
 * @nmwords: The number of words.
 *
 * Return: A pointer to an array of strings, or NULL on failure.
 */
static char **split_words(const char *str, char *delimiters, int nmwords)
{
	char **s = malloc((nmwords + 1) * sizeof(char *));

	if (!s)
		return NULL;

	int i = 0;
	int j = 0;

	for (i = 0, j = 0; j < nmwords; j++)
	{
		while (is_delim(str[i], delimiters))
			i++;

		int k = 0;

		while (!is_delim(str[i + k], delimiters) && str[i + k)
			k++;

		s[j] = malloc((k + 1) * sizeof(char));

		if (!s[j])
		{
			for (k = 0; k < j; k++)
			{
				free(s[k]);
			}
			free(s);
			return NULL;
		}

		for (int m = 0; m < k; m++)
		{
			s[j][m] = str[i++];
		}
		s[j][k] = '\0';
	}

	s[j] = NULL;
	return s;
}

/**
 * strtow - Split a string into words using delimiters.
 * @str: The input string.
 * @delimiters: The delimiter string.
 *
 * Return: A pointer to an array of strings, or NULL on failure.
 */
char **strtow(const char *str, const char *delimiters)
{
	int nmwords = count_words(str, delimiters);

	if (nmwords == 0)
		return (NULL);

	return (split_words(str, delimiters, nmwords));
}
