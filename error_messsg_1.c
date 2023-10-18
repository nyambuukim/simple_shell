#include "shell.h"

/**
 * char *error_1(char **args);
char *error_env(char **args);
char *error_2_cd(char **args);
char *error_2_syntax(char **args);
char *error_2_exit(char **args);
*/

/**
 * error_env - Shellby_env errors.
 * @args: Arguments.
 * Return: Error string.
 */

char *error_env(char **args)

{
	char *error, *hist_str;
	int length;

	hist_str = _itoa(hist);
	if (!hist_str)
		return (NULL);

	args--;
	length = _strlen(name) + _strlen(hist_str) + _strlen(args[0]) + 45;
	error = malloc(sizeof(char) * (length + 1));
	if (!error)
	{
		free(hist_str);
		return (NULL);
	}

	_strcpy(error, name);
	_strcat(error, ": ");
	_strcat(error, hist_str);
	_strcat(error, ": ");
	_strcat(error, args[0]);
	_strcat(error, ": Unable to add/remove from environment\n");

	free(hist_str);
	return (error);
}

/**
 * error_1 - Shellby_alias errors.
 * @args: Arguments passed to the command.
 * Return: Error string.
 */

char *error_1(char **args)

{
	char *error;
	int length;

	length = _strlen(name) + _strlen(args[0]) + 13;
	error = malloc(sizeof(char) * (length + 1));
	if (!error)
		return (NULL);

	_strcpy(error, "alias: ");
	_strcat(error, args[0]);
	_strcat(error, " not found\n");

		return (error);
}

/**
 * error_2_exit - Shellby_exit errors.
 * @args: Arguments.
 * Return: Error string.
 */

char *error_2_exit(char **args)

{
	char *error, *hist_str;
	int length;

	hist_str = _itoa(hist);
	if (!hist_str)
		return (NULL);

	length = _strlen(name) + _strlen(hist_str) + _strlen(args[0]) + 27;
	error = malloc(sizeof(char) * (length + 1));
	if (!error)
	{
		free(hist_str);
		return (NULL);
	}

	_strcpy(error, name);
	_strcat(error, ": ");
	_strcat(error, hist_str);
	_strcat(error, ": exit: Illegal number: ");
	_strcat(error, args[0]);
	_strcat(error, "\n");

	free(hist_str);
	return (error);
}

/**
 * error_2_cd - Shellby_cd errors.
 * @args: Arguments.
 * Return: Error string.
 */

char *error_2_cd(char **args)

{
	char *error, *hist_str;
	int length;

	hist_str = _itoa(hist);
	if (!hist_str)
		return (NULL);

	if (args[0][0] == '-')
		args[0][2] = '\0';
	length = _strlen(name) + _strlen(hist_str) + _strlen(args[0]) + 24;
	error = malloc(sizeof(char) * (length + 1));
	if (!error)
	{
		free(hist_str);
		return (NULL);
	}

	_strcpy(error, name);
	_strcat(error, ": ");
	_strcat(error, hist_str);
	if (args[0][0] == '-')
		_strcat(error, ": cd: ilegal option ");
	else
		_strcat(error, ": cd: canno't cd to ");
	_strcat(error, args[0]);
	_strcat(error, "\n");

	free(hist_str);
	return (error);
}

/**
 * error_2_syntax - Syntax errors.
 * @args: Arguments.
 * Return: Error string.
 */

char *error_2_syntax(char **args)

{
	char *error, *hist_str;
	int length;

	hist_str = _itoa(hist);
	if (!hist_str)
		return (NULL);

	length = _strlen(name) + _strlen(hist_str) + _strlen(args[0]) + 33;
	error = malloc(sizeof(char) * (length + 1));
	if (!error)
	{
		free(hist_str);
		return (NULL);
	}

	_strcpy(error, name);
	_strcat(error, ": ");
	_strcat(error, hist_str);
	_strcat(error, ": Syntax error: \"");
	_strcat(error, args[0]);
	_strcat(error, "\" unexpected End\n");

	free(hist_str);
	return (error);
}

