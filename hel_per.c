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
        size_t in;

        for (in = 0; args[in] || args[in + 1]; in++)
                free(args[in]);

        free(front);
}

/**
 * get_pid - Gets process ID.
 * Description: Opens the stat file*
 * Return: PID/ NULL (failure).
 */

char *get_pid(void)
{
        size_t in = 0;
        char *buffers;
        ssize_t files;

        files = open("/proc/self/stat", O_RDONLY);
        if (files == -1)
        {
                perror("Cant read file");
                return (NULL);
        }
        buffers = malloc(120);
        if (!buffers)
        {
                close(files);
                return (NULL);
        }
        read(files, buffers, 120);
        while (buffers[in] != ' ')
                in++;
        buffers[in] = '\0';

        close(files);
        return (buffers);
}

/**
 * get_env_value - Get value env variable.
 * @beginning: env var.
 * @len: The length 
 * Return: 0 *
 */

char *get_env_value(char *beginning, int len)

{
        char **var_addres;
        char *replacement = NULL, *tmp, *vari;

        vari = malloc(len + 1);
        if (!vari)
                return (NULL);
        vari[0] = '\0';
        _strncat(vari, beginning, len);

        var_addres = _getenv(vari);
        free(vari);
        if (var_addres)
        {
                tmp = *var_addres;
                while (*tmp != '=')
                        tmp++;
                tmp++;
                replacement = malloc(_strlen(tmp) + 1);
                if (replacement)
                        _strcpy(replacement, tmp);
        }

        return (replacement);
}

/**
 * variable_replacement - Handl var rep.
 * @line: Command and arguments.
 * @exe_ret:the last exec cmd.
 *
 * 
 */

void variable_replacement(char **line, int *exe_ret)

{
        int a, k = 0, len;
        char *replacement = NULL, *old_line = NULL, *new_line;

        old_line = *line;
        for (a = 0; old_line[a]; a++)
        {
                if (old_line[a] == '$' && old_line[a + 1] &&
		    old_line[a + 1] != ' ')
                {
                        if (old_line[a + 1] == '$')
                        {
                                replacement = get_pid();
                                k = a + 2;
                        }
                        else if (old_line[a + 1] == '?')
                        {
                                replacement = _itoa(*exe_ret);
                                k = a + 2;
                        }
                        else if (old_line[a + 1])
                        {
                                for (k = a + 1; old_line[k] &&
                                                old_line[k] != '$' &&
					     old_line[k] != ' '; k++)
                                        ;
                                len = k - (a + 1);
                                replacement = get_env_value(&old_line[a + 1], len);
                        }
                        new_line = malloc(a + _strlen(replacement)
                                          + _strlen(&old_line[k]) + 1);
                        if (!line)
                                return;
                        new_line[0] = '\0';
                        _strncat(new_line, old_line, a);
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
                        a = -1;
                }
        }
}

