#include "shell.h"
#include <string.h>

/**
 * print_history - Print the history list, command per line.
 * @info: The info_t structure containing the history list.
 * Return: Always 0.
 */
int print_history(info_t *info)
{
	list_t *node = info->history;

	while (node)
	{
		string_print(node->str);
		character_print('\n');
		node = node->next;
	}

	return (0);
}

/**
 * unset_alias - Unset an alias.
 * @info: The info_t structure containing alias list.
 * @alias: The alias to unset.
 * Return: Always 0 on success, 1 on error.
 */
int unset_alias(info_t *info, char *alias)
{
	char *equal_sign = strchr(alias, '='); /* Use strchr from string.h*/
	int result;

	if (!equal_sign)
		return (1);

	*equal_sign = '\0'; /* Terminate the alias string at '=' */

	result = delete_node_at_index(&(info->alias),
		get_node_index(info->alias, find_node_starts_with(info->alias, alias, -1)));

	*equal_sign = '='; /* Restore the original string */

	return (result);
}

/**
 * set_alias - Set an alias to a string.
 * @info: The info_t structure containing alias list.
 * @alias: The alias to set.
 * Return: Always 0 on success, 1 on error.
 */
int set_alias(info_t *info, char *alias)
{
	char *equal_sign = strchr(alias, '='); /*Use strchr from string.h*/

	if (!equal_sign)
		return (1);

	*equal_sign = '\0'; /* Terminate the alias string at '=' */

	unset_alias(info, alias); /* Remove any existing alias with the same name */

	*equal_sign = '='; /* Restore the original string */

	return (add_node_end(&(info->alias), alias, 0) == NULL);
}

/**
 * print_alias - Print an alias string.
 * @node: The alias node.
 * Return: Always 0 on success, 1 on error.
 */
int print_alias(list_t *node)
{
	if (node)
	{
		char *equal_sign = strchr(node->str, '='); /* Use strchr from string.h*/

		if (equal_sign)
		{
			*equal_sign = '\0'; /* Terminate the alias string at '=' */
			string_print(node->str);
			*equal_sign = '='; /* Restore the original string */
			string_print("'");
			string_print(equal_sign + 1);
			string_print("'\n");
			return (0);
		}
		return (0);
	}
	return (1);
}
