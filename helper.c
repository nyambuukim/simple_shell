#include "shell.h"

char *get_pid(void);
void free_args(char **args, char **front);
void variable_replacement(char **args, int *exe_ret);
char *get_env_value(char *beginning, int len);

/**
 * free_args - Frees arg memory
 * @args: A ncommands/arguments.
 * @front: Ang of args.
 */

void free_args(char **args, char **front)

{
	size_t index;

	for (index = 0; args[index] || args[index + 1]; index++)
		free(args[index]);

	free(front);
}


/**
 * get_pid - Gets process ID.
 * Description: Opens the stat file*
 * Return: PID/ NULL (failure).
 */

char *get_pid(void)

{
	size_t index = 0;
	char *buffer;
	ssize_t file;

	file = open("/proc/self/stat", O_RDONLY);
	if (file == -1)
	{
		perror("Cant read file");
		return (NULL);
	}
	buffer = malloc(120);
	if (!buffer)
	{
		close(file);
		return (NULL);
	}
	read(file, buffer, 120);
	while (buffer[index] != ' ')
		index++;
	buffer[index] = '\0';

	close(file);
	return (buffer);
}

/**
 * get_env_value - Get value env variable.
 * @beginning: env var.
 * @len: The length.
 * Return: 0 *
 */

char *get_env_value(char *beginning, int len)
{
	char **var_addr;
	char *replacement = NULL, *temp, *var;

	var = malloc(len + 1);
	if (!var)
		return (NULL);
	var[0] = '\0';
	_strncat(var, beginning, len);

	var_addr = _getenv(var);
	free(var);
	if (var_addr)
	{
		temp = *var_addr;
		while (*temp != '=')
			temp++;
		temp++;
		replacement = malloc(_strlen(temp) + 1);
		if (replacement)
			_strcpy(replacement, temp);
	}

	return (replacement);
}

/**
 * variable_replacement - Handl var rep.
 * @line: Command and arguments.
 * @exe_ret:the last exec cmd.
 */

void variable_replacement(char **line, int *exe_ret)

{
	int x, k = 0, len;
	char *replacement = NULL, *old_line = NULL, *new_line;

	old_line = *line;
	for (x = 0; old_line[x]; x++)
	{
		if (old_line[x] == '$' && old_line[x + 1] &&
		    old_line[x + 1] != ' ')
		{
			if (old_line[x + 1] == '$')
			{
				replacement = get_pid();
				k = x + 2;
			}
			else if (old_line[x + 1] == '?')
			{
				replacement = _itoa(*exe_ret);
				k = x + 2;
			}
			else if (old_line[x + 1])
			{
				for (k = x + 1; old_line[k] &&
						old_line[k] != '$' &&
					     old_line[k] != ' '; k++)
					;
				len = k - (x + 1);
				replacement = get_env_value(&old_line[x + 1], len);
			}
			new_line = malloc(x + _strlen(replacement)
					  + _strlen(&old_line[k]) + 1);
			if (!line)
				return;
			new_line[0] = '\0';
			_strncat(new_line, old_line, x);
			if (replacement)
			{
				_strcat(new_line, replacement);
				free(replacement);
				replacement = NULL;
			}
			_strcat(new_line, &old_line[k]);
			free(old_line);
			*line = new_line;
			old_line = new_line;
			x = -1;
		}
	}
}

