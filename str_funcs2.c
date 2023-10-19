#include "shell.h"

int _strncmp(const char *s1, const char *s2, size_t n);
int _strspn(char *s, char *accept);
char *_strchr(char *s, char c);
int _strcmp(char *s1, char *s2);

/**
* _strchr - Character locate.
* @s: The string.
* @c: The character.
* Return: Pointer/NULL.
*/

char *_strchr(char *s, char c)

{
	int i;

	for (i = 0; s[i]; i++)
	{
		if (s[i] == c)
		return (s + i);
	}

	return (NULL);
}

/**
* _strspn - Gets the length of a prefix substring.
* @s: The string.
* @accept: The prefix.
* Return: Bytes.
*/


int _strspn(char *s, char *accept)
{
	int byt = 0;
	int ind;

	while (*s)
	{
		for (ind = 0; accept[ind]; ind++)
		{
			if (*s == accept[ind])
			{
				byt++;
				break;
			}
		}
		s++;
	}
	return (byt);
}

/**
* _strcmp - Compar strng.
* @s1: first string.
* @s2: second string.
* Return: 0
*/


int _strcmp(char *s1, char *s2)
{
	while (*s1 && *s2 && *s1 == *s2)
	{
		s1++;
		s2++;
	}

		if (*s1 != *s2)
		return (*s1 - *s2);

	return (0);
}

/**
* _strncmp - Compare two strings.
* @s1: string.
* @s2: string.
* @n: bytes
* Return: 0.
*/


int _strncmp(const char *s1, const char *s2, size_t n)
{
	size_t in;

	for (in = 0; s1[in] && s2[in] && in < n; in++)
	{
		if (s1[in] > s2[in])
		return (s1[in] - s2[in]);
		else if (s1[in] < s2[in])
		return (s1[in] - s2[in]);
	}
		if (in == n)
		return (0);
		else
		return (-15);
}

