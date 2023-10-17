#include "shell.h"

void help_alias(void);
void help_cd(void);
void help_help(void);
void help_all(void);
void help_exit(void);


/**
* help_all - Builtin shellby commands.
*/

void help_all(void)

{
	char *msg = "Shellby\nCommands already defined.\n";

write(STDOUT_FILENO, msg, _strlen(msg));
msg = "Type 'help' to view.\nType 'help_name' to specify ";
write(STDOUT_FILENO, msg, _strlen(msg));
msg = "the function 'name'.\n\n  alias   \t";
write(STDOUT_FILENO, msg, _strlen(msg));
msg = "alias [NAME[='VALUE'] ...]\n  cd    \tcd   ";
write(STDOUT_FILENO, msg, _strlen(msg));
msg = "[DIRECTORY]\n  exit    \texit [STATUS]\n  env     \tenv";
write(STDOUT_FILENO, msg, _strlen(msg));
msg = "\n  setenv  \tsetenv [VARIABLE] [VALUE]\n  unsetenv\t";
write(STDOUT_FILENO, msg, _strlen(msg));
msg = "unsetenv [VARIABLE]\n";
write(STDOUT_FILENO, msg, _strlen(msg));
}

/**
* help_alias - Shellby builtin 'alias'.
*/

void help_alias(void)

{
char *msg = "alias: alias [NAME[='VALUE'] ...]\n\tHandle all aliases.\n";

write(STDOUT_FILENO, msg, _strlen(msg));
msg = "\n\talias: Print list aliases, Single line, in ";
write(STDOUT_FILENO, msg, _strlen(msg));
msg = "the format NAME='VALUE'.\n\talias_name [name-2 ...]:print";
write(STDOUT_FILENO, msg, _strlen(msg));
msg = " alias name, name-2, etc. one_line, in ";
write(STDOUT_FILENO, msg, _strlen(msg));
msg = "form NAME='VALUE'.\n\talias NAME='VALUE' [...]: Define";
write(STDOUT_FILENO, msg, _strlen(msg));
msg = " alias for each NAME where VALUE is prsnt. If NAME ";
write(STDOUT_FILENO, msg, _strlen(msg));
msg = "alias exist, replace with VALUE.\n";
write(STDOUT_FILENO, msg, _strlen(msg));
}

/**
* help_cd - Shellby builtin command 'cd'.
*/
void help_cd(void)
{
char *msg = "cd: cd [DIRECTORY]\n\tChange the current dir of ";

write(STDOUT_FILENO, msg, _strlen(msg));
msg = " process to DIR.\n\n\tIf no argument, the ";
write(STDOUT_FILENO, msg, _strlen(msg));
msg = "command cd $HOME. If argument '-' is";
write(STDOUT_FILENO, msg, _strlen(msg));
msg = " present, the command cd $OLDPWD.\n\n";
write(STDOUT_FILENO, msg, _strlen(msg));
msg = "\tThe env var PWD & OLDPWD are update ";
write(STDOUT_FILENO, msg, _strlen(msg));
msg = "change of dir.\n";
write(STDOUT_FILENO, msg, _strlen(msg));
}

/**
* help_exit - Shellby builtin command 'exit'.
*/

void help_exit(void)

{
	char *msg = "exit: exit [STATUS]\n\tExit shell.\n\n\tThe ";

write(STDOUT_FILENO, msg, _strlen(msg));
msg = "STATUS argument is the int to exit shell.";
write(STDOUT_FILENO, msg, _strlen(msg));
msg = " No argument, the command is ";
write(STDOUT_FILENO, msg, _strlen(msg));
msg = " exit 0.\n";
write(STDOUT_FILENO, msg, _strlen(msg));
}

/**
* help_help - Shellby builtin command 'help'.
*/

	void help_help(void)
{
char *msg = "help: help\n\tShellby builtin commands.\n";

write(STDOUT_FILENO, msg, _strlen(msg));
msg = "\n      help [BUILTIN NAME]\n\tSee each ";
write(STDOUT_FILENO, msg, _strlen(msg));
msg = "builtin command info.\n";
write(STDOUT_FILENO, msg, _strlen(msg));
}

