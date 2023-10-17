#include "shell.h"

char **_copyenv(void);
char **_getenv(const char *var);
void free_env(void);

/**
* _copyenv - Environment.
* Return: NULL/Pointer.
*
**/

char **_copyenv(void)

{
	char **new_environ;
	size_t sz;
	int ind;

	for (sz = 0; environ[sz]; sz++)
		;

	new_environ = malloc(sizeof(char *) * (sz + 1));
	if (!new_environ)
		return (NULL);

	for (ind = 0; environ[ind]; ind++)
	{
		new_environ[ind] = malloc(_strlen(environ[ind]) + 1);

	if (!new_environ[ind])
		{
		for (ind--; ind >= 0; ind--)
		free(new_environ[ind]);
		free(new_environ);
		return (NULL);
		}
		_strcpy(new_environ[ind], environ[ind]);
	}
	new_environ[ind] = NULL;

	return (new_environ);
}

/**
* free_env - Frees environment.
*/

void free_env(void)

{
	int indx;

		for (indx = 0; environ[indx]; indx++)
		free(environ[indx]);
		free(environ);
}

/**
* _getenv -  PATH.
* @var: Environmental variable.
* Return: NULL/ Pointer.
*
*/

char **_getenv(const char *var)

{
	int i, length;

	length = _strlen(var);
	for (i = 0; environ[i]; i++)
	{
	if (_strncmp(var, environ[i], length) == 0)
	return (&environ[i]);
	}
	return (NULL);
}

