#include "shell.h"

void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
ssize_t _getline(char **lineptr, size_t *n, FILE *stream);
void assign_lineptr(char **lineptr, size_t *n, char *buffer, size_t b);

/**
 * _realloc - Reallocate a mem block. 
 * @ptr:  previously allocated memory.
 * @old_size: allocated space for ptr.
 * @new_size: new memory block.
 * Return: 0/ NULL.         
 **/

void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)

{
	void *memo;
	char *ptr_copy, *filler;
	unsigned int ind;

	if (new_size == old_size)
		return (ptr);

	if (ptr == NULL)
	{
		memo = malloc(new_size);
		if (memo == NULL)
			return (NULL);

		return (memo);
	}

	if (new_size == 0 && ptr != NULL)
	{
		free(ptr);
		return (NULL);
	}

	ptr_copy = ptr;
	memo = malloc(sizeof(*ptr_copy) * new_size);
	if (memo == NULL)
	{
		free(ptr);
		return (NULL);
	}

	filler = memo;

	for (ind = 0; ind < old_size && ind < new_size; ind++)
		filler[ind] = *ptr_copy++;

	free(ptr);
	return (memo);
}

/**
 * assign_lineptr - Reassigns.
 * @lineptr: A buffer.
 * @n:  lineptr size.
 * @buffer: string.
 * @b: The size.
 */

void assign_lineptr(char **lineptr, size_t *n, char *buffer, size_t b)

{
	if (*lineptr == NULL)
	{
		if (b > 120)
			*n = b;
		else
			*n = 120;
		*lineptr = buffer;
	}
	else if (*n < b)
	{
		if (b > 120)
			*n = b;
		else
			*n = 120;
		*lineptr = buffer;
	}
	else
	{
		_strcpy(*lineptr, buffer);
		free(buffer);
	}
}

/**
 * _getline - input stream.
 * @lineptr: A buffer input.
 * @n: lineptr.
 * @stream: stream read from.
 * Return: bytes read.
 */

ssize_t _getline(char **lineptr, size_t *n, FILE *stream)

{
	static ssize_t input;
	ssize_t rest;
	char c = 'x', *buffer;
	int re;

	if (input == 0)
		fflush(stream);
	else
		return (-1);
	input = 0;

	buffer = malloc(sizeof(char) * 120);
	if (!buffer)
		return (-1);

	while (c != '\n')
	{
		re = read(STDIN_FILENO, &c, 1);
		if (re == -1 || (re == 0 && input == 0))
		{
			free(buffer);
			return (-1);
		}
		if (re == 0 && input != 0)
		{
			input++;
			break;
		}

		if (input >= 120)
			buffer = _realloc(buffer, input, input + 1);

		buffer[input] = c;
		input++;
	}
	buffer[input] = '\0';

	assign_lineptr(lineptr, n, buffer, input);

	rest = input;
	if (re != 0)
		input = 0;
	return (rest);
}

