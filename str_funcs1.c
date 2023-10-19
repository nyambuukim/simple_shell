#include "shell.h"


int _strlen(const char *s);
char *_strcat(char *dest, const char *src);
char *_strncat(char *dest, const char *src, size_t n);
char *_strcpy(char *dest, const char *src);

/**
* _strlen - Length-string.
* @s: String character pointer.
* Return: Length.
*/

int _strlen(const char *s)
{
	int len = 0;

	if (!s)
	return (len);
	for (len = 0; s[len]; len++)
		;
	return (len);
}

/**
* _strcpy - Copy string at ptr src
* @dest: Destination pointer.
* @src: Source Pointer.
* Return: Destination.
*/


char *_strcpy(char *dest, const char *src)

{
	size_t ink;

	for (ink = 0; src[ink] != '\0'; ink++)
	dest[ink] = src[ink];
	dest[ink] = '\0';
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
	char *destinTemp;
	const char *srceTemp;

	destinTemp = dest;
	srceTemp =  src;

	while (*destinTemp != '\0')
	destinTemp++;

	while (*srceTemp != '\0')
	*destinTemp++ = *srceTemp++;
	*destinTemp = '\0';
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
	size_t index;

	for (index = 0; index < n && src[index] != '\0'; index++)
	dest[dest_len + index] = src[index];
	dest[dest_len + index] = '\0';

	return (dest);
}
