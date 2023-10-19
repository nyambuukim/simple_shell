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
	size_t size;
	int i;

	for (size = 0; environ[size]; size++)
		;

	new_environ = malloc(sizeof(char *) * (size + 1));
	if (!new_environ)
		return (NULL);

	for (i = 0; environ[i]; i++)
	{
		new_environ[i] = malloc(_strlen(environ[i]) + 1);

		if (!new_environ[i])
		{
			for (i--; i >= 0; i--)
			free(new_environ[i]);
			free(new_environ);
			return (NULL);
		}
		_strcpy(new_environ[i], environ[i]);
	}
	new_environ[i] = NULL;

	return (new_environ);
}

/**
* free_env - Frees environment.
*/

void free_env(void)

{
	int index;

	for (index = 0; environ[index]; index++)
	free(environ[index]);
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
	int ind, length;

	length = _strlen(var);
	for (ind = 0; environ[ind]; ind++)
	{
		if (_strncmp(var, environ[ind], length) == 0)
		return (&environ[ind]);
	}
	return (NULL);
}
/*TJ*/
