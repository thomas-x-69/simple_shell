#include "shell.h"

/**
 * _erratoi - converts a string to an integer
 * @s: the string to be converted
 *
 * Return: 0 if no numbers in the string, the converted number otherwise
 *         -1 on error (overflow or invalid characters)
 */
int _erratoi(char *s)
{
    int i = 0;
    unsigned long int result = 0;

    /* Handle the optional sign character */
    if (*s == '+')
        s++; /* Skip the '+' sign */

    /* Iterate through the string and convert to integer */
    for (i = 0; s[i] != '\0'; i++)
    {
        if (s[i] >= '0' && s[i] <= '9')
        {
            result *= 10;
            result += (s[i] - '0');

            /* Check for overflow */
            if (result > INT_MAX)
                return (-1);
        }
        else
        {
            /* Invalid character encountered */
            return (-1);
        }
    }

    return (result);
}

/**
 * print_error - prints an error message to stderr
 * @info: the parameter & return info struct
 * @estr: string containing the specified error type
 */
void print_error(info_t *info, char *estr)
{
    _eputs(info->fname);
    _eputs(": ");
    print_d(info->line_count, STDERR_FILENO);
    _eputs(": ");
    _eputs(info->argv[0]);
    _eputs(": ");
    _eputs(estr);
}

/**
 * print_d - function prints a decimal (integer) number (base 10)
 * @input: the input
 * @fd: the file descriptor to write to
 *
 * Return: number of characters printed
 */
int print_d(int input, int fd)
{
    int (*__putchar)(char) = _putchar;
    int i, count = 0;
    unsigned int _abs_, current;

    if (fd == STDERR_FILENO)
        __putchar = _eputchar;

    /* Handle the sign and convert to unsigned for absolute value */
    if (input < 0)
    {
        _abs_ = -input;
        __putchar('-');
        count++;
    }
    else
    {
        _abs_ = input;
    }

    current = _abs_;
    for (i = 1000000000; i > 1; i /= 10)
    {
        if (_abs_ / i)
        {
            __putchar('0' + current / i);
            count++;
        }
        current %= i;
    }

    __putchar('0' + current);
    count++;

    return (count);
}

/**
 * convert_number - converter function, a clone of itoa
 * @num: number
 * @base: base
 * @flags: argument flags
 *
 * Return: string
 */
char *convert_number(long int num, int base, int flags)
{
    static char *array;
    static char buffer[50];
    char sign = 0;
    char *ptr;
    unsigned long n = num;

    /* Handle the sign for non-unsigned conversions */
    if (!(flags & CONVERT_UNSIGNED) && num < 0)
    {
        n = -num;
        sign = '-';
    }

    /* Select the character array based on lowercase or uppercase */
    array = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";

    ptr = &buffer[49];
    *ptr = '\0';

    /* Convert the number to the specified base */
    do
    {
        *--ptr = array[n % base];
        n /= base;
    } while (n != 0);

    /* Add the sign character if present */
    if (sign)
        *--ptr = sign;

    return (ptr);
}

/**
 * remove_comments - function replaces the first instance of '#' with '\0'
 * @buf: address of the string to modify
 *
 * Return: Always 0;
 */
void remove_comments(char *buf)
{
    int i;

    /* Iterate through the string and replace the first '#' with '\0' */
    for (i = 0; buf[i] != '\0'; i++)
        if (buf[i] == '#' && (!i || buf[i - 1] == ' '))
        {
            buf[i] = '\0';
            break;
        }
}
