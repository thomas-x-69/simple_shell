#include "shell.h"

/**
 * _eputs - prints an input string to stderr
 * @str: the string to be printed
 *
 * Return: Nothing
 */
void _eputs(char *str)
{
    int i = 0;

    /* Check if the string is not NULL */
    if (!str)
        return;

    /* Iterate through the string and write each character to stderr */
    while (str[i] != '\0')
    {
        _eputchar(str[i]);
        i++;
    }
}

/**
 * _eputchar - writes the character c to stderr
 * @c: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _eputchar(char c)
{
    static int i;
    static char buf[WRITE_BUF_SIZE];

    /* Check if it's time to flush the buffer or if the buffer is full */
    if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
    {
        write(2, buf, i);
        i = 0;
    }

    /* Check if c is not BUF_FLUSH and add it to the buffer */
    if (c != BUF_FLUSH)
        buf[i++] = c;

    return (1);
}

/**
 * _putfd - writes the character c to the given file descriptor
 * @c: The character to print
 * @fd: The file descriptor to write to
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putfd(char c, int fd)
{
    static int i;
    static char buf[WRITE_BUF_SIZE];

    /* Check if it's time to flush the buffer or if the buffer is full */
    if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
    {
        write(fd, buf, i);
        i = 0;
    }

    /* Check if c is not BUF_FLUSH and add it to the buffer */
    if (c != BUF_FLUSH)
        buf[i++] = c;

    return (1);
}

/**
 * _putsfd - prints an input string to the given file descriptor
 * @str: the string to be printed
 * @fd: the file descriptor to write to
 *
 * Return: the number of characters written
 */
int _putsfd(char *str, int fd)
{
    int i = 0;

    /* Check if the string is not NULL */
    if (!str)
        return (0);

    /* Iterate through the string and write each character to the given file descriptor */
    while (*str)
    {
        i += _putfd(*str++, fd);
    }

    return (i);
}
