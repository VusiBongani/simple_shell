#include "shell.h"

/**
 **_strncpy - copies a string.
 *@dest: the destination string.
 *@src: the original string.
 *@n: characters to be copied.
 *Return: the string.
 */
char *_strncpy(char *dest, char *src, int n)
{
	int i, j;
	char *k = dest;

	i = 0;
	while (src[i] != '\0' && i < n - 1)
	{
		dest[i] = src[i];
		i++;
	}
	if (i < n)
	{
		j = i;
		while (j < n)
		{
			dest[j] = '\0';
			j++;
		}
	}
	return (k);
}

/**
 **_strncat - concatenates two strings.
 *@dest: the first string.
 *@src: the second string.
 *@n: the amount of bytes.
 *Return: a string
 */
char *_strncat(char *dest, char *src, int n)
{
	int i, j;
	char *k = dest;

	i = 0;
	j = 0;
	while (dest[i] != '\0')
		i++;
	while (src[j] != '\0' && j < n)
	{
		dest[i] = src[j];
		i++;
		j++;
	}
	if (j < n)
		dest[i] = '\0';
	return (k);
}

/**
 **_strchr - locates a character in a string.
 *@p: the string parameter.
 *@c: the character parameter.
 *Return: a pointer.
 */
char *_strchr(char *p, char c)
{
	do {
		if (*p == c)
			return (p);
	} while (*p++ != '\0');

	return (NULL);
}
