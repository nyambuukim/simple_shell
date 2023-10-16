#include "shell.h"

/**
 **_strncpy - Copy string.
 *@dest: Destination.
 *@src: Source.
 *@n:Character account.
 *Return: Concatenated string.
 *Tinnie & Jay.
 */

char *_strncpy(char *dest, char *src, int n)

{
	int x, y;
	char *s = dest;

	x = 0;
	while (src[x] != '\0' && x < n - 1)
	{
		dest[x] = src[x];
		x++;
	}
	if (x < n)
	{
		y = x;
		while (y < n)
		{
			dest[j] = '\0';
			y++;
		}
	}
	return (s);
}

/**
 **_strncat - Concatenates 2 strings.
 *@dest: String one.
 *@src: String two.
 *@n: Byte count.
 *Return: Concatenated string.
 */

char *_strncat(char *dest, char *src, int n)

{
	int a, b;
	char *s = dest;

	a = 0;
	b = 0;
	while (dest[a] != '\0')
		a++;
	while (src[b] != '\0' && b < n)
	{
		dest[a] = src[b];
		a++;
		b++;
	}
	if (b < n)
		dest[a] = '\0';
	return (s);
}

/**
 **_strchr - Locate character string.
 *@s: String parsed.
 *@c: Character.
 *Return: pointer  s.
 */

char *_strchr(char *s, char c)

{
	do {
		if (*s == c)
			return (s);
	} while (*s++ != '\0');

	return (NULL);
}
/*T&J*/
