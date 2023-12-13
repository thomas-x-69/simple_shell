#include "shell.h"

/**
 * _strncpy - copies a string
 * @dest: the destination string to be copied to
 * @src: the source string
 * @n: the amount of characters to be copied
 *
 * Return: the concatenated string
 */
char *_strncpy(char *dest, char *src, int n)
{
    int i, j;
    char *s = dest;

    i = 0;

    /* Copy characters from src to dest until the specified limit (n) or the end of src */
    while (src[i] != '\0' && i < n - 1)
    {
        dest[i] = src[i];
        i++;
    }

    /* Fill the remaining space in dest with null characters if necessary */
    if (i < n)
    {
        j = i;
        while (j < n)
        {
            dest[j] = '\0';
            j++;
        }
    }

    return (s);
}

/**
 * _strncat - concatenates two strings
 * @dest: the first string
 * @src: the second string
 * @n: the amount of bytes to be maximally used
 *
 * Return: the concatenated string
 */
char *_strncat(char *dest, char *src, int n)
{
    int i, j;
    char *s = dest;

    i = 0;
    j = 0;

    /* Find the end of dest */
    while (dest[i] != '\0')
        i++;

    /* Concatenate characters from src to dest until the specified limit (n) or the end of src */
    while (src[j] != '\0' && j < n)
    {
        dest[i] = src[j];
        i++;
        j++;
    }

    /* Add a null character to the end of dest if necessary */
    if (j < n)
        dest[i] = '\0';

    return (s);
}

/**
 * _strchr - locates a character in a string
 * @s: the string to be parsed
 * @c: the character to look for
 *
 * Return: a pointer to the memory area in s where the character is found, or NULL if not found
 */
char *_strchr(char *s, char c)
{
    /* Iterate through the string until the character is found or the end of the string is reached */
    do
    {
        if (*s == c)
            return (s);
    } while (*s++ != '\0');

    return (NULL);
}
