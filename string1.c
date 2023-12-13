#include "shell.h"

/**
 * _strcpy - copies a string
 * @dest: the destination
 * @src: the source
 *
 * Return: pointer to destination
 */
char *_strcpy(char *dest, char *src)
{
    int i = 0;

    // Check if source and destination are the same or if source is NULL
    if (dest == src || src == 0)
        return (dest);

    // Copy each character from source to destination
    while (src[i])
    {
        dest[i] = src[i];
        i++;
    }
    
    // Add null terminator to the destination string
    dest[i] = 0;

    return (dest);
}

/**
 * _strdup - duplicates a string
 * @str: the string to duplicate
 *
 * Return: pointer to the duplicated string
 */
char *_strdup(const char *str)
{
    int length = 0;
    char *ret;

    // Check if the input string is NULL
    if (str == NULL)
        return (NULL);

    // Calculate the length of the input string
    while (*str++)
        length++;

    // Allocate memory for the duplicated string
    ret = malloc(sizeof(char) * (length + 1));

    // Check if memory allocation is successful
    if (!ret)
        return (NULL);

    // Copy characters from the input string to the duplicated string
    for (length++; length--;)
        ret[length] = *--str;

    return (ret);
}

/**
 *_puts - prints an input string
 *@str: the string to be printed
 *
 * Return: Nothing
 */
void _puts(char *str)
{
    int i = 0;

    // Check if the input string is NULL
    if (!str)
        return;

    // Loop through the string and print each character
    while (str[i] != '\0')
    {
        _putchar(str[i]);
        i++;
    }
}

/**
 * _putchar - writes the character c to stdout
 * @c: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putchar(char c)
{
    static int i;
    static char buf[WRITE_BUF_SIZE];

    // Check if buffer is full or if BUF_FLUSH character is encountered
    if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
    {
        // Write the buffer to stdout and reset the index
        write(1, buf, i);
        i = 0;
    }

    // Check if character is not BUF_FLUSH, then add it to the buffer
    if (c != BUF_FLUSH)
        buf[i++] = c;

    return (1);
}
