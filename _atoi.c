#include "shell.h"

/**
 * interactive - True if shell = interactive mode.
 * @info: Struct address.
 * Return: 1 (interactive mode) 0 (otherwise).
 * Tinnie & Jay.
 */

int interactive(info_t *info)

{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * is_delim - Checks character delimeter.
 * @c: Char to check.
 * @delim: Delimeter string.
 * Return: 1(true) 0(false).
 */

int is_delim(char c, char *delim)
{
	while (*delim)
		if (*delim++ == c)
			return (1);
	return (0);
}

/**
 *_isalpha - Alphabetic character.
 *@c: Character to input.
 *Return: 1(alphabetic) 0 (otherwise).
 */

int _isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 *_atoi - Converts string to integer.
 *@s: String to convert.
 *Return: 0 no numbers in string.
 */

int _atoi(char *s)
{
	int index, sign = 1, flag = 0, output;
	unsigned int result = 0;

	for (index = 0;  s[index] != '\0' && flag != 2; index++)
	{
		if (s[index] == '-')
			sign *= -1;

		if (s[index] >= '0' && s[index] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (s[index] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

	if (sign == -1)
		output = -result;
	else
		output = result;

	return (output);
}
/*T&J*/
