#include "shell.h"

/**
 * clear_info - Initializes info_t struct
 * @info: Struct address
 */
void clear_info(info_t *info)
{
	info->arg = NULL;
	info->argv = NULL;
	info->path = NULL;
	info->argc = 0;
}

/**
 * set_info - Initializes info_t struct
 * @info: Struct address
 * @av: Argument vector
 */
void set_info(info_t *info, char **av)
{
	int i = 0;

	info->fname = av[0];
	if (info->arg)
	{
		info->argv = strtow(info->arg, " \t");
		if (!info->argv)
		{
			info->argv = malloc(sizeof(char *) * 2);
			if (info->argv)
			{
				info->argv[0] = string_duplicate(info->arg);
				info->argv[1] = NULL;
			}
		}
		while (info->argv && info->argv[i])
		{
			i++;
		}
		info->argc = i;

		replace_alias(info);
		replace_vars(info);
	}
}

/**
 * free_info - Frees info_t struct fields
 * @info: Struct address
 * @all: True if freeing all fields
 */
void free_info(info_t *info, int all)
{
	free_string_array(info->argv);
	info->argv = NULL;
	info->path = NULL;

	if (all)
	{
		if (!info->cmd_buf)
			free(info->arg);

		free_list(&(info->env));
		free_list(&(info->history));
		free_list(&(info->alias));
		free_string_array(info->environ);
		info->environ = NULL;
		free_and_null((void **)&info->cmd_buf);

		if (info->readfd > 2)
			close(info->readfd);

		_write_character_stderr(1);
	}
}
