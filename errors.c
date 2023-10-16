#include "shell.h"

/**
 * _erratoi - convert String to integer.
 * @s: String for convertion
 * Return: 0 (numbers in string),-1(error).
 * Tinnie & Jay.
 */

int _erratoi(char *s)

{
	int ind = 0;
	unsigned long int result = 0;

	if (*s == '+')
		s++;

	for (ind = 0;  s[ind] != '\0'; ind++)
	{
		if (s[ind] >= '0' && s[ind] <= '9')
		{
			result *= 10;
			result += (s[ind] - '0');
			if (result > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (result);
}

/**
 * print_error - Print error message.
 * @info: Info struct.
 * @estr: String error type.
 * Return: 0(success), 1(error).
 */

void print_error(info_t *info, char *estr)

{
	_eputs(info->fname);
	_eputs(": ");
	print_d(info->line_count, STDERR_FILENO);
	_eputs(": ");
	_eputs(info->argv[0]);
	_eputs(": ");
	_eputs(estr);
}

/**
 * print_d - Print decimal.
 * @input: Input
 * @fd: Filedescriptor.
 * Return: No of chars printed.
 */

int print_d(int input, int fd)

{
	int (*__putchar)(char) = _putchar;
	int i, count = 0;
	unsigned int _abs_, current;

	if (fd == STDERR_FILENO)
		__putchar = _eputchar;
	if (input < 0)
	{
		_abs_ = -input;
		__putchar('-');
		count++;
	}
	else
		_abs_ = input;
	current = _abs_;
	for (i = 1000000000; i > 1; i /= 10)
	{
		if (_abs_ / i)
		{
			__putchar('0' + current / i);
			count++;
		}
		current %= i;
	}
	__putchar('0' + current);
	count++;

	return (count);
}

/**
 * convert_number - converter function, a clone of itoa
 * @num: The number.
 * @base: The base.
 * @flags: Argument flags.
 * Return: str.
 */


char *convert_number(long int num, int base, int flags)
{
	static char *array;
	static char buffer[50];
	char sign = 0;
	char *potr;
	unsigned long n = num;

	if (!(flags & CONVERT_UNSIGNED) && num < 0)
	{
		n = -num;
		sign = '-';

	}
	array = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49];
	*potr = '\0';

	do	{
		*--potr = array[n % base];
		n /= base;
	} while (n != 0);

	if (sign)
		*--potr = sign;
	return (potr);
}

/**
 * remove_comments - Replaces '#' with '\0'
 * @buf: Address of modifying strin.
 * Return: 0(success).
 */

void remove_comments(char *buf)

{
	int in;

	for (in = 0; buf[in] != '\0'; in++)
		if (buf[in] == '#' && (!in || buf[in - 1] == ' '))
		{
			buf[in] = '\0';
			break;
		}
}
/*T&J*/
