#include "shell.h"

/**
 * printEnvironment - Print the current environment variables.
 * @info: Structure containing potential arguments.
 *
 * Return: 0 on success, 1 on error.
 */
int printEnvironment(info_t *info)
{
	print_list_strings(info->env);
	return (0);
}

/**
 * getEnvironmentValue - Get the value of an environment variable.
 * @info: Structure containing potential arguments.
 * @name: Name of the environment variable.
 *
 * Return: The value of the environment variable, or NULL if not found.
 */
char *getEnvironmentValue(info_t *info, const char *name)
{
	list_t *node = info->env;
	char *value;

	while (node)
	{
		value = starts_with(node->str, name);
		if (value && *value)
			return (value);
		node = node->next;
	}
	return (NULL);
}

/**
 * setEnvironmentVariable - Initialize a new environment variable
 * or modify an existing one.
 * @info: Structure containing potential arguments.
 *
 * Return: 0 on success, 1 on error.
 */
int setEnvironmentVariable(info_t *info)
{
	if (info->argc != 3)
	{
		string_print("Usage: setenv VARIABLE VALUE\n");
		return (1);
	}

	if (_setenv(info, info->argv[1], info->argv[2]) == 0)
		return (0);

	string_print("Failed to set environment variable.\n");
	return (1);
}

/**
 * unsetEnvironmentVariable - Remove an environment variable.
 * @info: Structure containing potential arguments.
 *
 * Return: 0 on success, 1 on error.
 */
int unsetEnvironmentVariable(info_t *info)
{
	if (info->argc != 2)
	{
		string_print("Usage: unsetenv VARIABLE\n");
		return (1);
	}

	if (unsetenv(info->argv[1]) == 0)
		return (0);

	string_print("Failed to unset environment variable.\n");
	return (1);
}

/**
 * populateEnvironmentList - Populate the environment linked list.
 * @info: Structure containing potential arguments.
 *
 * Return: Always 0.
 */
int populateEnvironmentList(info_t *info)
{
	list_t *node = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		add_node_end(&node, environ[i], 0);

	info->env = node;
	return (0);
}
