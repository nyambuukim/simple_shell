#include "shell.h"

char *fill_path_dir(char *path);
list_t *get_path_dir(char *path);

/**
 * get_location - Loc of command_path.
 * @command: Command.
 * Return: Pathname/Null(Error).
 */

char *get_location(char *command)

{
	char **path, *tmp;
	list_t *dirs, *head;
	struct stat stir;

	path = _getenv("PATH");
	if (!path || !(*path))
		return (NULL);

	dirs = get_path_dir(*path + 5);
	head = dirs;

	while (dirs)
	{
		tmp = malloc(_strlen(dirs->dir) + _strlen(command) + 2);
		if (!tmp)
			return (NULL);

		_strcpy(tmp, dirs->dir);
		_strcat(tmp, "/");
		_strcat(tmp, command);

		if (stat(tmp, &stir) == 0)
		{
			free_list(head);
			return (tmp);
		}

		dirs = dirs->next;
		free(tmp);
	}

	free_list(head);

	return (NULL);
}

/**
 * fill_path_dir - Copies PATH.
 * @path: The : of directories.
 * Return: Path copy.
 */

char *fill_path_dir(char *path)

{
	int is, len = 0;
	char *path_copy, *pwkd;

	pwkd = *(_getenv("PWD")) + 4;
	for (is = 0; path[is]; is++)
	{
		if (path[is] == ':')
		{
			if (path[is + 1] == ':' || is == 0 || path[is + 1] == '\0')
				len += _strlen(pwkd) + 1;
			else
				len++;
		}
		else
			len++;
	}
	path_copy = malloc(sizeof(char) * (len + 1));
	if (!path_copy)
		return (NULL);
	path_copy[0] = '\0';
	for (is = 0; path[is]; is++)
	{
		if (path[is] == ':')
		{
			if (is == 0)
			{
				_strcat(path_copy, pwkd);
				_strcat(path_copy, ":");
			}
			else if (path[is + 1] == ':' || path[is + 1] == '\0')
			{
				_strcat(path_copy, ":");
				_strcat(path_copy, pwkd);	
			}
			else
				_strcat(path_copy, ":");
		}
		else
		{
		_strncat(path_copy, &path[is], 1);
		}
	}
	return (path_copy);
}

/**
 * get_path_dir - Tokenizer.
 * @path:on-separated list of directories
* Return: A pointer.
 */

list_t *get_path_dir(char *path)
{
	int indx;
	char **dirst, *path_copy;
	list_t *head = NULL;

	path_copy = fill_path_dir(path);
	if (!path_copy)
		return (NULL);
	dirst = _strtok(path_copy, ":");
	free(path_copy);
	if (!dirst)
		return (NULL);

	for (indx = 0; dirst[indx]; indx++)
	{
		if (add_node_end(&head, dirst[indx]) == NULL)
		{
			free_list(head);
			free(dirst);
			return (NULL);
		}
	}

	free(dirst);

	return (head);
}
