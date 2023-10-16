#include "shell.h"

/**
 * _myenv - Prints current environment.
 * @info: Structure containing potential args.
 * Return: 0(success).
 * Tinnie & Jay.
 */

int _myenv(info_t *info)

{
	print_list_str(info->env);
	return (0);
}

/**
 * _getenv - Value of environment_variable.
 * @info: Structure containing argument.
 * @name: Name of environment variable.
 * Return: Values.
 */

char *_getenv(info_t *info, const char *name)

{
	list_t *node = info->env;
	char *pt;

	while (node)
	{
		p = starts_with(node->str, name);
		if (p && *pt)
			return (p);
		node = node->next;
	}
	return (NULL);
}

/**
 * _mysetenv - New or modified env variable.
 * @info: Structure containing potentoial args.
 *  Return: 0(success).
 */

int _mysetenv(info_t *info)

{
	if (info->argc != 3)
	{
		_eputs("Incorrect number of argument\n");
		return (1);
	}
	if (_setenv(info, info->argv[1], info->argv[2]))
		return (0);
	return (1);
}

/**
 * _myunsetenv - Remov env var.
 * @info: Structure of potentoial args.
 *  Return: Always 0.
 */

int _myunsetenv(info_t *info)

{
	int in;

	if (info->argc == 1)
	{
		_eputs("Too few arguements.\n");
		return (1);
	}
	for (in = 1; in <= info->argc; in++)
		_unsetenv(info, info->argv[in]);

	return (0);
}

/**
 * populate_env_list - Env linked_list.
 * @info: Structure of potential_args.
 * Return: 0(success).
 */

int populate_env_list(info_t *info)

{
	list_t *node = NULL;
	size_t in;

	for (in = 0; environ[in]; in++)
		add_node_end(&node, environ[in], 0);
	info->env = node;
	return (0);
}

