#include "shell.h"

/**
 * _myhistory - Displays history list starting at 0.
 * @info: Structure containing ars.
 *  Return: Always 0
 *  Tinnie & Jay.
 */

int _myhistory(info_t *info)
{
	print_list(info->history);
	return (0);
}

/**
 * unset_alias - Sets the alias of string
 * @info: Parameter structure.
 * @str: String.
 * Return: 0(success), 1\(error).
 */

int unset_alias(info_t *info, char *str)

{
	char *pt, c;
	int rest;

	p = _strchr(str, '=');
	if (!pt)
		return (1);
	c = *pt;
	*pt = 0;
	rest = delete_node_at_index(&(info->alias),
		get_node_index(info->alias, node_starts_with(info->alias, str, -1)));
	*pt = c;
	return (rest);
}

/**
 * set_alias - Alias of string.
 * @info: Parameter structuer.
 * @str: Alias of the string.
 * Return: 0(success) & 1(error).
 */

int set_alias(info_t *info, char *str)

{
	char *pt;

	pt = _strchr(str, '=');
	if (!pt)
		return (1);
	if (!*++pt)
		return (unset_alias(info, str));

	unset_alias(info, str);
	return (add_node_end(&(info->alias), str, 0) == NULL);
}

/**
 * print_alias - Alias of the string.
 * @node: Alias of the node.
 * Return: 0(success), 1(error).
 */

int print_alias(list_t *node)

{
	char *pt = NULL, *a = NULL;

	if (node)
	{
		pt = _strchr(node->str, '=');
		for (a = node->str; a <= pt; a++)
			_putchar(*a);
		_putchar('\'');
		_puts(p + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * _myalias - mimics builtin Alias.
 * @info: Structure containing potential args.
 *  Return:0(success)
 */
int _myalias(info_t *info)
{
	int d = 0;
	char *pt = NULL;
	list_t *node = NULL;

	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			print_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (d = 1; info->argv[d]; d++)
	{
		pt = _strchr(info->argv[pt], '=');
		if (pt)
			set_alias(info, info->argv[d]);
		else
			print_alias(node_starts_with(info->alias, info->argv[d], '='));
	}

	return (0);
}
/* T&J */
