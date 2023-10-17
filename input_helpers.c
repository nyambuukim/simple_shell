#include "shell.h"

int call_args(char **args, char **front, int *exe_ret);
char *get_args(char *line, int *exe_ret);
int run_args(char **args, char **front, int *exe_ret);
int check_args(char **args);
int handle_args(int *exe_ret);

/**
 * get_args - command from stdio.
 * @line: Buffer
 * @exe_ret: Return value.
 * Return: NULL/Pointer.
 * TJ.
 */
char *get_args(char *line, int *exe_ret)

{
	size_t nu = 0;
	ssize_t reader;
        char *prompts = "$ ";

        if (line)
                free(line);

        reader = _getline(&line, &nu, STDIN_FILENO);
        if (reader == -1)
                return (NULL);
        if (reader == 1)
        {
                hist++;
                if (isatty(STDIN_FILENO))
                        write(STDOUT_FILENO, prompts, 2);
                return (get_args(line, exe_ret));
        }

        line[reader - 1] = '\0';
        variable_replacement(&line, exe_ret);
        handle_line(&line, reader);

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
	int ret, inx;

	if (!args[0])
		return (*exe_ret);
	for (inx = 0; args[inx]; inx++)
	{
		if (_strncmp(args[inx], "||", 2) == 0)
		{
			free(args[inx]);
			args[inx] = NULL;
			args = replace_aliases(args);
			ret = run_args(args, front, exe_ret);
			if (*exe_ret != 0)
			{
				args = &args[++inx];
				inx = 0;
			}
			else
			{
				for (inx++; args[inx]; inx++)
					free(args[inx]);
				return (ret);
			}
		}
		else if (_strncmp(args[inx], "&&", 2) == 0)
		{
			free(args[inx]);
			args[inx] = NULL;
			args = replace_aliases(args);
			ret = run_args(args, front, exe_ret);
			if (*exe_ret == 0)
			{
				args = &args[++inx];
				inx = 0;
			}
			else
			{
				for (inx++; args[inx]; inx++)
					free(args[inx]);
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
 * @front: A double pointe.
 * @exe_ret: The return v
 * Return: The xecuted command.
 */

int run_args(char **args, char **front, int *exe_ret)

{
	int rent, im;
	int (*builtin)(char **args, char **front);

	builtin = get_builtin(args[0]);

	if (builtin)
	{
		rent = builtin(args + 1, front);
		if (rent != EXIT)
			*exe_ret = rent;
	}
	else
	{
		*exe_ret = execute(args, front);
                rent = *exe_ret;
        }

        hist++;

        for (im = 0; args[im]; im++)
                free(args[im]);

        return (rent);
}

/**
 * handle_args - Get/call/run cmd.
 * @exe_ret: The parent proces.
 * * Return: END OF FILE (-2).
 *         Untokenized -1.
 *         O/w - eExit value.
 */

int handle_args(int *exe_ret)

{
        int rent = 0, inx;
        char **args, *line = NULL, **front;

        line = get_args(line, exe_ret);
        if (!line)
                return (END_OF_FILE);

        args = _strtok(line, " ");
        free(line);
        if (!args)
                return (rent);
        if (check_args(args) != 0)
        {
                *exe_ret = 2;
                free_args(args, args);
                return (*exe_ret);
        }
        front = args;

        for (inx = 0; args[inx]; inx++)
        {
                if (_strncmp(args[inx], ";", 1) == 0)
                {
                        free(args[inx]);
                        args[inx] = NULL;
                        rent = call_args(args, front, exe_ret);
                        args = &args[++inx];
                        inx = 0;
                }
        }
        if (args)
                rent = call_args(args, front, exe_ret);

        free(front);
        return (rent);
}

/**
 * check_args - Checks  for ';', ';;', '&&', '||'.
 * @args: Tokenized cmds and args.
 * Return:  - 2,therwise - 0.
 */

int check_args(char **args)
{
        size_t in;
        char *curr, *nxt;

        for (in = 0; args[in]; in++)
        {
                curr = args[in];
                if (curr[0] == ';' || curr[0] == '&' || curr[0] == '|')
                {
                        if (in == 0 || curr[1] == ';')
                                return (create_error(&args[in], 2));
                        nxt = args[in + 1];
                        if (nxt && (nxt[0] == ';' || nxt[0] == '&' || nxt[0] == '|'))
                                return (create_error(&args[in + 1], 2));
                }
        }
        return (0);
}

