#include "shell.h"

int count_tokens(char *str, char *delim);
int token_len(char *str, char *delim);
char **_strtok(char *line, char *delim);

/**
* token_len - delimiter index.
* @str: The string.
* @delim: The delimiter.
* Return:0
**/

int token_len(char *str, char *delim)

{

	int indx = 0, length = 0;

	while (*(str + indx) && *(str + indx) != *delim)
	{
	length++;
	indx++;
	}

return (length);
}

/**
* count_tokens - Delimited words.
* @str: string.
* @delim: delimiter.
* Return: String count.
*/

int count_tokens(char *str, char *delim)

{
	int ix, token = 0, length = 0;

	for (ix = 0; *(str + ix); ix++)
		length++;
	for (ix = 0; ix < length; ix++)
	{
		if (*(str + ix) != *delim)
		{
			token++;
			ix += token_len(str + ix, delim);
		}
	}
	return (token);
}

/**
* _strtok - Tokenizer.
* @line: String.
* @delim: delimiter.
* Return: Pointer.
*/

char **_strtok(char *line, char *delim)

{
	char **ptr;
	int index = 0, token, let, letters, l;

	token = count_tokens(line, delim);
		if (token == 0)
			return (NULL);

	ptr = malloc(sizeof(char *) * (token + 2));
		if (!ptr)
			return (NULL);

		for (let = 0; let < token; let++)
		{
		while (line[index] == *delim)
			index++;

		letters = token_len(line + index, delim);

		ptr[let] = malloc(sizeof(char) * (letters + 1));
		if (!ptr[let])
		{
			for (index -= 1; index >= 0; index--)
			free(ptr[index]);
			free(ptr);
			return (NULL);
		}
		for (let = 0; let < letters; l++)
		{
		ptr[let][l] = line[index];
			index++;
		}
			ptr[let][l] = '\0';
		}
			ptr[let] = NULL;
			ptr[let + 1] = NULL;

	return (ptr);
}

