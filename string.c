#include "shell.h"

/**
 * _strlen - returns the length of a string
 * @s: the string whose length to check
 *
 * Return: integer length of the string
 */
int _strlen(char *s)
{
	int i = 0;

	// Check if the string is NULL
	if (!s)
		return (0);

	// Iterate through the string characters
	while (*s++)
		i++;

	return (i);
}

/**
 * _strcmp - performs lexicographic comparison of two strings.
 * @s1: the first string
 * @s2: the second string
 *
 * Return: negative if s1 < s2, positive if s1 > s2, zero if s1 == s2
 */
int _strcmp(char *s1, char *s2)
{
	// Iterate through the characters of both strings
	while (*s1 && *s2)
	{
		// Compare corresponding characters
		if (*s1 != *s2)
			return (*s1 - *s2);

		// Move to the next character
		s1++;
		s2++;
	}

	// Check if both strings are equal
	if (*s1 == *s2)
		return (0);
	else
		return (*s1 < *s2 ? -1 : 1);
}

/**
 * starts_with - checks if needle starts with haystack
 * @haystack: string to search
 * @needle: the substring to find
 *
 * Return: address of the next character of haystack or NULL
 */
char *starts_with(const char *haystack, const char *needle)
{
	// Iterate through the characters of both strings
	while (*needle)
		if (*needle++ != *haystack++)
			return (NULL);

	// Return the address of the next character of haystack
	return ((char *)haystack);
}

/**
 * _strcat - concatenates two strings
 * @dest: the destination buffer
 * @src: the source buffer
 *
 * Return: pointer to the destination buffer
 */
char *_strcat(char *dest, char *src)
{
	char *ret = dest;

	// Move to the end of the destination buffer
	while (*dest)
		dest++;

	// Copy characters from the source buffer to the destination buffer
	while (*src)
		*dest++ = *src++;

	// Add the null terminator to the destination buffer
	*dest = *src;

	// Return a pointer to the destination buffer
	return (ret);
}
