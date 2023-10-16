#include "shell.h"

/**
 * add_node - Add a node to the start of the list
 * @head: Address of pointer to head node
 * @str: str field of the node
 * @num: Node index used by history
 *
 * Return: Pointer to the new node
 */
list_t *add_node(list_t **head, const char *str, int num)
{
	if (!head)
		return (NULL);

	list_t *new_head = malloc(sizeof(list_t));

	if (!new_head)
		return (NULL);

	_memset((void *)new_head, 0, sizeof(list_t));
	new_head->num = num;

	if (str)
	{
		new_head->str = _strdup(str);

		if (!new_head->str)
		{
			free(new_head);
			return (NULL);
		}
	}

	new_head->next = *head;
	*head = new_head;

	return (new_head);
}

/**
 * add_node_end - Add a node to the end of the list
 * @head: Address of pointer to head node
 * @str: str field of the node
 * @num: Node index used by history
 *
 * Return: Pointer to the new node
 */
list_t *add_node_end(list_t **head, const char *str, int num)
{
	if (!head)
		return (NULL);

	list_t *new_node = malloc(sizeof(list_t));
	list_t *node = *head;

	if (!new_node)
		return (NULL);

	_memset((void *)new_node, 0, sizeof(list_t));
	new_node->num = num;

	if (str)
	{
		new_node->str = _strdup(str);

		if (!new_node->str)
		{
			free(new_node);
			return (NULL);
		}
	}

	if (node)
	{
		while (node->next)
			node = node->next;
		node->next = new_node;
	}
	else
		*head = new_node;

	return (new_node);
}

/**
 * print_node_string - Print the str element of a node
 * @node: Pointer to a list_t node
 */
void print_node_string(const list_t *node)
{
	if (node)
		_puts(node->str ? node->str : "(nil)");
	_puts("\n");
}

/**
 * print_list_strings - Print all str elements in a list_t linked list
 * @head: Pointer to the first node
 *
 * Return: The number of nodes in the list
 */
size_t print_list_strings(const list_t *head)
{
	size_t count = 0;

	while (head)
	{
		print_node_string(head);
		head = head->next;
		count++;
	}
	return (count);
}

/**
 * delete_node_at_index - Deletes the node at a given index
 * @head: A pointer to the address of the first node
 * @index: The index of the node to delete
 *
 * Return: 1 on success, 0 on failure
 */
int delete_node_at_index(list_t **head, unsigned int index)
{
	if (!head || !*head)
		return (0);

	if (index == 0)
	{
		list_t *temp = *head;
		*head = (*head)->next;
		free(temp->str);
		free(temp);
		return (1);
	}

	list_t *current = *head;
	list_t *prev = NULL;

	for (unsigned int i = 0; i < index; i++)
	{
		if (!current)
			return (0); /* Index out of range */
		prev = current;
		current = current->next;
	}

	if (!current)
		return (0); /* Index out of range */

	prev->next = current->next;
	free(current->str);
	free(current);

	return (1);
}
