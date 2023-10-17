#include "shell.h"

/**
 * get_environ - String array copy environment.
 * @info: Structure containing potential args.
 * Return: 0(Success).
 * Tinnie & Jay.
 */

char **get_environ(info_t *info)

{
	if (!info->environ || info->env_changed)
	{
		info->environ = list_to_strings(info->env);
		info->env_changed = 0;
	}

	return (info->environ);
}

/**
 * _unsetenv - Remove env_variable.
 * @info: Structure containing args.
 *  Return: 1 (delete), 0
 * @var: env_var property.
 */

int _unsetenv(info_t *info, char *var)

{
	list_t *node = info->env;
	size_t i = 0;
	char *poi;

	if (!node || !var)
		return (0);

	while (node)
	{
		poi = starts_with(node->str, var);
		if (poi && *poi == '=')
		{
			info->env_changed = delete_node_at_index(&(info->env), i);
			i = 0;
			node = info->env;
			continue;
		}
		node = node->next;
		i++;
	}
	return (info->env_changed);
}

/**
 * _setenv - Initialize a new environment variable,
 *             or modify an existing one
 * @info: Structure containing args.
 * @var: env_var property.
 * @value: env_var value.
 *  Return: 0(success).
 */

int _setenv(info_t *info, char *var, char *value)

{
	char *buf = NULL;
	list_t *node;
	char *p;

	if (!var || !value)
		return (0);

	buf = malloc(_strlen(var) + _strlen(value) + 2);
	if (!buf)
		return (1);
	_strcpy(buf, var);
	_strcat(buf, "=");
	_strcat(buf, value);
	node = info->env;
	while (node)
	{
		p = starts_with(node->str, var);
		if (p && *p == '=')
		{
			free(node->str);
			node->str = buf;
			info->env_changed = 1;
			return (0);
		}
		node = node->next;
	}
	add_node_end(&(info->env), buf, 0);
	free(buf);
	info->env_changed = 1;
	return (0);
}
