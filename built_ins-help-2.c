#include "shell.h"

void help_history(void);
void help_setenv(void);
void help_env(void);
void help_unsetenv(void);


/**
* help_env - Shellby builtin 'env'.
*/

void help_env(void)

{
	char *msg = "env: env\n\tPrint environment current.\n";

write(STDOUT_FILENO, msg, _strlen(msg));
}

/**
* help_setenv - Shellby builtin 'setenv'.
*/

void help_setenv(void)
{
char *msg = "setenv: setenv [VARIABLE] [VALUE]\n\tInit new Env";

write(STDOUT_FILENO, msg, _strlen(msg));
msg = "env var, or modify existing env.\n\n";
write(STDOUT_FILENO, msg, _strlen(msg));
msg = "\tFailure, print to STDERR.\n";
write(STDOUT_FILENO, msg, _strlen(msg));
}

/**
* help_unsetenv - Shellby builtin 'unsetenv'.
*/
void help_unsetenv(void)

{
	char *msg = "unsetenv: unsetenv [VARIABLE]\n\tRemove ";

write(STDOUT_FILENO, msg, _strlen(msg));
msg = "environmental variable.\n\n\tFailure, print a ";
write(STDOUT_FILENO, msg, _strlen(msg));
msg = "Message STDERR.\n";
write(STDOUT_FILENO, msg, _strlen(msg));
}

