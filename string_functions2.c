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
	int in;

	for (in = 0; s[in]; in++)
	{
	if (s[in] == c)
	return (s + in);
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
	int bytes = 0;
	int i;

	while (*s)
	{
	for (i = 0; accept[i]; i++)
	{
		if (*s == accept[i])
		{
		bytes++;
		break;
		}
	}
	s++;
	}
	return (bytes);
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

	size_t ind;

		for (ind = 0; s1[ind] && s2[ind] && ind < n; ind++)
		{
			if (s1[ind] > s2[ind])
				return (s1[ind] - s2[ind]);
			else if (s1[ind] < s2[ind])
				return (s1[ind] - s2[ind]);
		}
			if (ind == n)
				return (0);
			else
				return (-15);
}

