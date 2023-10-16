#include "shell.h"

/**
 * list_length - determines the length of a linked list
 * @h: pointer to the first node
 *
 * Return: size of the list
 */
size_t list_length(const list_t *h)
{
	size_t length = 0;

	while (h)
	{
		h = h->next;
		length++;
	}

	return (length);
}

/**
 * list_to_strings - converts a list of strings into an array of strings
 * @head: pointer to the first node
 *
 * Return: array of strings
 */
char **list_to_strings(list_t *head)
{
	list_t *node = head;
	size_t list_size = list_length(head);
	size_t i, j;
	char **str_array;
	char *str;

	if (!head || list_size == 0)
		return (NULL);

	str_array = malloc(sizeof(char *) * (list_size + 1));

	if (!str_array)
		return (NULL);

	for (i = 0; node; node = node->next, i++)
	{
		str = malloc(_strlen(node->str) + 1);

		if (!str)
		{
			for (j = 0; j < i; j++)
				free(str_array[j];

			free(str_array);
			return (NULL);
		}

		str = _strcpy(str, node->str);
		str_array[i] = str;
	}

	str_array[i] = NULL;
	return (str_array);
}

/**
 * print_linked_list - prints all elements of a list_t linked list
 * @h: pointer to the first node
 *
 * Return: size of the list
 */
size_t print_linked_list(const list_t *h)
{
	size_t length = 0;

	while (h)
	{
		_puts(convert_number(h->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next;
		length++;
	}

	return (length);
}

/**
 * find_node_starts_with - finds a node whose string starts with a prefix
 * @node: pointer to the list head
 * @prefix: string to match
 * @c: the next character after the prefix to match
 *
 * Return: matching node or NULL
 */
list_t *find_node_starts_with(list_t *node, char *prefix, char c)
{
	char *p = NULL;

	while (node)
	{
		p = starts_with(node->str, prefix);

		if (p && ((c == -1) || (*p == c)))
			return (node);

		node = node->next;
	}

	return (NULL);
}

/**
 * get_node_index - gets the index of a node within a list
 * @head: pointer to list head
 * @node: pointer to the node
 *
 * Return: index of the node or -1
 */
ssize_t get_node_index(list_t *head, list_t *node)
{
	size_t index = 0;

	while (head)
	{
		if (head == node)
			return (index);

		head = head->next;
		index++;
	}

	return (-1);
}
