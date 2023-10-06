#include "shell.h"

/**
 * free_and_null - Frees a pointer and sets it to NULL
 * @ptr: Address of the pointer to free
 *
 * Return: 1 if freed, 0 if the pointer is already NULL
 */
int free_and_null(void **ptr)
{
	if (ptr != NULL && *ptr != NULL)
	{
		free(*ptr);
		*ptr = NULL;
		return (1);
	}
	return (0);
}
