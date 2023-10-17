#include "shell.h"

/**
 *_eputs - Prints the string input.
 * @str: String.
 * Return: 0(success).
 * Tinnie & Jay.
 */

void _eputs(char *str)

{
	int index = 0;

	if (!str)
		return;
	while (str[index] != '\0')
	{
		_eputchar(str[index]);
		index++;
	}
}

/**
 * _eputchar - Writes a character c to stderr.
 * @c: Character printout.
 * Return: 1 (success).
 * -1(error) set errno.
 */

int _eputchar(char c)

{
	static int v;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || v >= WRITE_BUF_SIZE)
	{
		write(2, buf, v);
		v = 0;
	}
	if (c != BUF_FLUSH)
		buf[v++] = c;
	return (1);
}

/**
 * _putfd - Character c to file descriptor.
 * @c: Character to print.
 * @fd: Filedescriptor.
 * Return: 1(success).
 * 1(error) errno set.
 */

int _putfd(char c, int fd)

{
	static int in;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || in >= WRITE_BUF_SIZE)
	{
		write(fd, buf, in);
		in = 0;
	}
	if (c != BUF_FLUSH)
		buf[in++] = c;
	return (1);
}

/**
 *_putsfd - Print input string.
 * @str: String.
 * @fd: Filedescriptor.
 * Return: No of char.
 */

int _putsfd(char *str, int fd)

{
	int in = 0;

	if (!str)
		return (0);
	while (*str)
	{
		in += _putfd(*str++, fd);
	}
	return (in);
}
