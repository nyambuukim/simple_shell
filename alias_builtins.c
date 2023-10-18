#include "shell.h"

int shellby_alias(char **args, char __attribute__((__unused__)) **front);
void set_alias(char *var_name, char *value);
void print_alias(alias_t *alias);

/**
* shellby_alias - Builtin command print/set alias.
* @args: Array_arguments.
* @front: Double pointer(args_begin).
* Return: -1(error), 0(Success) .
* Tinnie & Jay.
*/

int shellby_alias(char **args, char __attribute__((__unused__)) **front)

{
	alias_t *temp = aliases;
	int index, ret = 0;
	char *value;

	if (!args[0])
	{
		while (temp)
		{
			print_alias(temp);
			temp = temp->next;
		}
		return (ret);
	}
		for (index = 0; args[index]; index++)
		{
			temp = aliases;
			value = _strchr(args[index], '=');
			if (!value)
			{
			while (temp)
			{
			if (_strcmp(args[index], temp->name) == 0)
				{
					print_alias(temp);
					break;
				}
					temp = temp->next;
			}
				if (!temp)
				ret = create_error(args + index, 1);
			}
			else
				set_alias(args[index], value);
		}
	return (ret);
}

/**
* set_alias - Assign alias new vlue.
* * @var_name: Name alias.
*  @value: Value assigned alias. Initial char '='.
*/

void set_alias(char *var_name, char *value)

{
	alias_t *temp = aliases;
	int length, x, l;
	char *new_value;

	*value = '\0';
	value++;
		length = _strlen(value) - _strspn(value, "'\"");
		new_value = malloc(sizeof(char) * (length + 1));
	if (!new_value)
	return;
		for (x = 0, l = 0; value[x]; x++)
		{
			if (value[x] != '\'' && value[x] != '"')
			new_value[l++] = value[x];
		}
			new_value[l] = '\0';
		while (temp)
		{
			if (_strcmp(var_name, temp->name) == 0)
			{
				free(temp->value);
				temp->value = new_value;
				break;
			}
			temp = temp->next;
		}
		if (!temp)
			add_alias_end(&aliases, var_name, new_value);
}

/**
* print_alias - Format name='value'.
* @alias: Alias Pointer.
*/

void print_alias(alias_t *alias)
{
	char *alias_string;
	int length = _strlen(alias->name) + _strlen(alias->value) + 4;

	alias_string = malloc(sizeof(char) * (length + 1));
		if (!alias_string)
			return;
	_strcpy(alias_string, alias->name);
	_strcat(alias_string, "='");
	_strcat(alias_string, alias->value);
	_strcat(alias_string, "'\n");

	write(STDOUT_FILENO, alias_string, length);
	free(alias_string);
}

/**
* replace_aliases - Replace duplicate alias with value.
* @args: 2D pointer to the argts.
* Return: 2D pointer to the argmts.
*/

	char **replace_aliases(char **args)
{
	alias_t *temp;
	int i;
	char *new_value;

	if (_strcmp(args[0], "alias") == 0)
	return (args);
	for (i = 0; args[i]; i++)
	{
		temp = aliases;
		while (temp)
		{
			if (_strcmp(args[i], temp->name) == 0)
			{
				new_value = malloc(sizeof(char) * (_strlen(temp->value) + 1));
				if (!new_value)
				{
					free_args(args, args);
					return (NULL);
				}
				_strcpy(new_value, temp->value);
				free(args[i]);
				args[i] = new_value;
				i--;
				break;
			}
				temp = temp->next;
		}
	}

	return (args);
}

