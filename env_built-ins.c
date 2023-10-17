#include "shell.h"

int shellby_env(char **args, char __attribute__((__unused__)) **front);
int shellby_unsetenv(char **args, char __attribute__((__unused__)) **front);
int shellby_setenv(char **args, char __attribute__((__unused__)) **front);

/**
 * shellby_env - Current environment.
 * @args: Arguments.
 * @front: Beginning of args.
 * Return: Error -1.
 *         Success 0.
 */

int shellby_env(char **args, char __attribute__((__unused__)) **front)

{
        int inx;
        char onc = '\n';

        if (!environ)
                return (-1);

        for (inx = 0; environ[inx]; inx++)
        {
                write(STDOUT_FILENO, environ[inx], _strlen(environ[inx]));
                write(STDOUT_FILENO, &onc, 1);
        }

        (void)args;
        return (0);
}

/**
 * shellby_setenv - Add env to PATH.
 * @args: Arguments.
 * @front: Beginning of args.
 * Return: error -1.
 *         Success- 0.
 */
int shellby_setenv(char **args, char __attribute__((__unused__)) **front)
{
        char **env_var = NULL, **new_environ, *new_value;
        size_t siz;
        int inde;

        if (!args[0] || !args[1])
                return (create_error(args, -1));

        new_value = malloc(_strlen(args[0]) + 1 + _strlen(args[1]) + 1);
        if (!new_value)
                return (create_error(args, -1));
        _strcpy(new_value, args[0]);
        _strcat(new_value, "=");
        _strcat(new_value, args[1]);

        env_var = _getenv(args[0]);
        if (env_var)
        {
                free(*env_var);
                *env_var = new_value;
                return (0);
        }
        for (siz = 0; environ[siz]; siz++);

        new_environ = malloc(sizeof(char *) * (siz + 2));
        if (!new_environ)
        {
                free(new_value);
                return (create_error(args, -1));
        }

        for (inde = 0; environ[inde]; inde++)
                new_environ[inde] = environ[inde];

        free(environ);
        environ = new_environ;
        environ[inde] = new_value;
        environ[inde + 1] = NULL;

        return (0);
}

/**
 * shellby_unsetenv - Delete PATH.
 * @args: Arguments.
 * @front: Beginning of args.
 * Return: Error -1.
 *         Success - 0.
 */

int shellby_unsetenv(char **args, char __attribute__((__unused__)) **front)

{
        char **env_var, **new_environ;
        size_t size;
        int indx, ind2;

        if (!args[0])
                return (create_error(args, -1));
        env_var = _getenv(args[0]);
        if (!env_var)
                return (0);

        for (size = 0; environ[size]; size++)
                ;

        new_environ = malloc(sizeof(char *) * size);
        if (!new_environ)
                return (create_error(args, -1));

        for (indx = 0, ind2 = 0; environ[indx]; indx++)
        {
                if (*env_var == environ[indx])
                {
                        free(*env_var);
                        continue;
                }
                new_environ[ind2] = environ[indx];
                ind2++;
        }
        free(environ);
        environ = new_environ;
        environ[size - 1] = NULL;

        return (0);
}

