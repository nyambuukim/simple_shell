#include "shell.h"

/**
 * clear_info - init info_t structure.
 * @info: struct address.
 * Return: 0(success).
 * Tinnie & Jay.
 */

void clear_info(info_t *info)

{
	info->arg = NULL;
	info->argv = NULL;
	info->path = NULL;
	info->argc = 0;
}

/**
 * set_info - Init info_t structure.
 * @info: Struct_address.
 * @av:Argument vector.
 * Return: 0(success).
 */

void set_info(info_t *info, char **av)
{
	int ind = 0;

	info->fname = av[0];
	if (info->arg)
	{
		info->argv = strtow(info->arg, " \t");
		if (!info->argv)
		{

			info->argv = malloc(sizeof(char *) * 2);
			if (info->argv)
			{
				info->argv[0] = _strdup(info->arg);
				info->argv[1] = NULL;
			}
		}
		for (ind = 0; info->argv && info->argv[ind]; ind++)
			;
		info->argc = ind;

		replace_alias(info);
		replace_vars(info);
	}
}

/**
 * free_info - Free info_t struct_field.
 * @info: Struct-address.
 * @all: True while free fields.
 */

void free_info(info_t *info, int all)

{
	ffree(info->argv);
	info->argv = NULL;
	info->path = NULL;
	if (all)
	{
		if (!info->cmd_buf)
			free(info->arg);
		if (info->env)
			free_list(&(info->env));
		if (info->history)
			free_list(&(info->history));
		if (info->alias)
			free_list(&(info->alias));
		ffree(info->environ);
			info->environ = NULL;
		bfree((void **)info->cmd_buf);
		if (info->readfd > 2)
			close(info->readfd);
		_putchar(BUF_FLUSH);
	}
}
