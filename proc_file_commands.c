#include "shell.h"

int cant_open(char *file_path);
int proc_file_commands(char *file_path, int *exe_ret);

/**
 * cant_open - No fil/permissions.
 * @file_path: Path to file.
 * Return: 127.
 */

int cant_open(char *file_path)
{
	char *error, *hist_str;
	int length;

	hist_str = _itoa(hist);
	if (!hist_str)
		return (127);

	length = _strlen(name) + _strlen(hist_str) + _strlen(file_path) + 16;
	error = malloc(sizeof(char) * (length + 1));
	if (!error)
	{
		free(hist_str);
		return (127);
	}

	_strcpy(error, name);
	_strcat(error, ": ");
	_strcat(error, hist_str);
	_strcat(error, ": Can't open ");
	_strcat(error, file_path);
	_strcat(error, "\n");

	free(hist_str);
	write(STDERR_FILENO, error, length);
	free(error);
	return (127);
}

/**
 * proc_file_commands - Run internal commands.
 * @file_path: Path to file.
 * @exe_ret: Return cmd value.
 * Return: file can't open - 127.
 *	   If malloc fails - -1.
 */

int proc_file_commands(char *file_path, int *exe_ret)

{
	ssize_t file, b_read, in;
	unsigned int line_size = 0;
	unsigned int old_size = 120;
	char *line, **args, **front;
	char buffer[120];
	int ret;

	hist = 0;
	file = open(file_path, O_RDONLY);
	if (file == -1)
	{
		*exe_ret = cant_open(file_path);
		return (*exe_ret);
	}
	line = malloc(sizeof(char) * old_size);
	if (!line)
		return (-1);
	do {
		b_read = read(file, buffer, 119);
		if (b_read == 0 && line_size == 0)
			return (*exe_ret);
		buffer[b_read] = '\0';
		line_size += b_read;
		line = _realloc(line, old_size, line_size);
		_strcat(line, buffer);
		old_size = line_size;
	} while (b_read);
	for (in = 0; line[in] == '\n'; in++)
		line[in] = ' ';
	for (; in < line_size; in++)
	{
		if (line[in] == '\n')
		{
			line[in] = ';';
			for (in += 1; in < line_size && line[in] == '\n'; in++)
				line[in] = ' ';
		}
	}
	variable_replacement(&line, exe_ret);
	handle_line(&line, line_size);
	args = _strtok(line, " ");
	free(line);
	if (!args)
		return (0);
	if (check_args(args) != 0)
	{
		*exe_ret = 2;
		free_args(args, args);
		return (*exe_ret);
	}
	front = args;

	for (in = 0; args[in]; in++)
	{
		if (_strncmp(args[in], ";", 1) == 0)
		{
			free(args[in]);
			args[in] = NULL;
			ret = call_args(args, front, exe_ret);
			args = &args[++in];
			in = 0;
		}
	}

	ret = call_args(args, front, exe_ret);

	free(front);
	return (ret);
}

