#include "shell.h"

char *get_args(char *line, int *exe_ret);
int check_args(char **args);
int run_args(char **args, char **front, int *exe_ret);
int handle_args(int *exe_ret);
int call_args(char **args, char **front, int *exe_ret);

/**
 * get_args - command from stdio.
 * @line: Buffer
 * @exe_ret: Return value.
 * Return: NULL/Pointer.
 * TJ.
 */

char *get_args(char *line, int *exe_ret)
{
	size_t num = 0;
	ssize_t read;
	char *prompt = "$ ";

	if (line)
		free(line);

	read = _getline(&line, &num, STDIN_FILENO);
	if (read == -1)
		return (NULL);
	if (read == 1)
	{
		hist++;
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, prompt, 2);
		return (get_args(line, exe_ret));
	}

	line[read - 1] = '\0';
	variable_replacement(&line, exe_ret);
	handle_line(&line, read);

	return (line);
}

/**
 * call_args - Partitions operand.
 * @args: Array arguments.
 * @front: Beginning of args.
 * @exe_ret: Return value.
 * Return: Return value.
 */

int call_args(char **args, char **front, int *exe_ret)
{
	int ret, i;

	if (!args[0])
		return (*exe_ret);
	for (i = 0; args[i]; i++)
	{
		if (_strncmp(args[i], "||", 2) == 0)
		{
			free(args[i]);
			args[i] = NULL;
			args = replace_aliases(args);
			ret = run_args(args, front, exe_ret);
			if (*exe_ret != 0)
			{
				args = &args[++i];
				i = 0;
			}
			else
			{
				for (i++; args[i]; i++)
					free(args[i]);
				return (ret);
			}
		}
		else if (_strncmp(args[i], "&&", 2) == 0)
		{
			free(args[i]);
			args[i] = NULL;
			args = replace_aliases(args);
			ret = run_args(args, front, exe_ret);
			if (*exe_ret == 0)
			{
				args = &args[++i];
				i = 0;
			}
			else
			{
				for (i++; args[i]; i++)
					free(args[i]);
				return (ret);
			}
		}
	}
	args = replace_aliases(args);
	ret = run_args(args, front, exe_ret);
	return (ret);
}

/**
 * run_args - Execution command.
 * @args: arguments.
 * @front: A double pointer.
 * @exe_ret: Return val.
 * Return: The xecuted command.
 */

int run_args(char **args, char **front, int *exe_ret)
{
	int ret, index;
	int (*builtin)(char **args, char **front);

	builtin = get_builtin(args[0]);

	if (builtin)
	{
		ret = builtin(args + 1, front);
		if (ret != EXIT)
			*exe_ret = ret;
	}
	else
	{
		*exe_ret = execute(args, front);
		ret = *exe_ret;
	}

	hist++;

	for (index = 0; args[index]; index++)
		free(args[index]);

	return (ret);
}

/**
 * handle_args - Gets, calls, and runs the execution of a command.
 * @exe_ret: The return value of the parent process' last executed command.
 *
 * Return: If an end-of-file is read - END_OF_FILE (-2).
 *	   If the input cannot be tokenized - -1.
 *	   O/w - The exit value of the last executed command.
 */
int handle_args(int *exe_ret)
{
	int ret = 0, i;
	char **args, *line = NULL, **front;

	line = get_args(line, exe_ret);
	if (!line)
		return (END_OF_FILE);

	args = _strtok(line, " ");
	free(line);
	if (!args)
		return (ret);
	if (check_args(args) != 0)
	{
		*exe_ret = 2;
		free_args(args, args);
		return (*exe_ret);
	}
	front = args;

	for (i = 0; args[i]; i++)
	{
		if (_strncmp(args[i], ";", 1) == 0)
		{
			free(args[i]);
			args[i] = NULL;
			ret = call_args(args, front, exe_ret);
			args = &args[++i];
			i = 0;
		}
	}
	if (args)
		ret = call_args(args, front, exe_ret);

	free(front);
	return (ret);
}

/**
 * check_args - Checks	for ';', ';;', '&&', '||'.
 * @args: Tokenized cmds and args.
 * Return:  - 2, Success - 0.
 */

int check_args(char **args)
{
	size_t index;
	char *cur, *nex;

	for (index = 0; args[index]; index++)
	{
		cur = args[index];
		if (cur[0] == ';' || cur[0] == '&' || cur[0] == '|')
		{
			if (index == 0 || cur[1] == ';')
				return (create_error(&args[index], 2));
			nex = args[index + 1];
			if (nex && (nex[0] == ';' || nex[0] == '&' || nex[0] == '|'))
				return (create_error(&args[index + 1], 2));
		}
	}
	return (0);
}
