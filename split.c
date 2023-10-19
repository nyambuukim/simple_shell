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

	int i = 0, length = 0;

	while (*(str + i) && *(str + i) != *delim)
	{
		length++;
		i++;
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
	int i, token = 0, length = 0;

	for (i = 0; *(str + i); i++)
		length++;
	for (i = 0; i < length; i++)
	{
		if (*(str + i) != *delim)
		{
		token++;
		i += token_len(str + i, delim);
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
	int i = 0, token, s, letter, l;

	token = count_tokens(line, delim);
	if (token == 0)
	return (NULL);

	ptr = malloc(sizeof(char *) * (token + 2));
	if (!ptr)
		return (NULL);

	for (s = 0; s < token; s++)
	{
	while (line[i] == *delim)
		i++;

	letter = token_len(line + i, delim);

	ptr[s] = malloc(sizeof(char) * (letter + 1));
	if (!ptr[s])
	{
		for (i -= 1; i >= 0; i--)
		free(ptr[i]);
		free(ptr);
		return (NULL);
	}
	for (l = 0; l < letter; l++)
	{
		ptr[s][l] = line[i];
		i++;
	}
	ptr[s][l] = '\0';
	}
	ptr[s] = NULL;
	ptr[s + 1] = NULL;

	return (ptr);
}
