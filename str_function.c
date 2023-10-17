#include "shell.h"

int _strlen(const char *s);
char *_strncat(char *dest, const char *src, size_t n);
char *_strcat(char *dest, const char *src);
char *_strcpy(char *dest, const char *src);

/**
* _strlen - Length-string.
* @s: String character pointer.
* Return: Length.
*/

int _strlen(const char *s)

{

	int lengh = 0;


	if (!s)
	return (lengh);
	for (lengh = 0; s[lengh]; lengh++);
return (lengh);
}

/**
* _strcpy - Copy string at ptr src
* @dest: Destination pointer.
* @src: Source Pointer.
* Return: Destination.
*/

char *_strcpy(char *dest, const char *src)

{
	size_t sz;

	for (sz = 0; src[sz] != '\0'; sz++)
	dest[sz] = src[sz];
	dest[sz] = '\0';
return (dest);
}

/**
* _strcat - Concantenate_strings.
* @dest: Destination.
* @src: Source.
* Return: dest.
*/

char *_strcat(char *dest, const char *src)
{
	char *destTempr;
	const char *srcTempr;

	destTempr = dest;
	srcTempr =  src;

		while (*destTempr != '\0')
			destTempr++;

		while (*srcTempr != '\0')
		*destTempr++ = *srcTempr++;
		*destTempr = '\0';
return (dest);
}

/**
* _strncat - Concantenateswith n bytes.
* @dest: Destination.
* @src: Source.
* @n: bytes copied frm src.
* Return: destination.
*/

char *_strncat(char *dest, const char *src, size_t n)

{
	size_t dest_len = _strlen(dest);
	size_t sz;

			for (sz = 0; sz < n && src[sz] != '\0'; sz++)
			dest[dest_len + sz] = src[sz];
			dest[dest_len + sz] = '\0';

return (dest);
}
/*TJ*/
