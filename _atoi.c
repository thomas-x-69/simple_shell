#include "shell.h"

/**
 * interactive - returns true if shell is in interactive mode
 * @info: pointer to the info_t struct
 *
 * Return: 1 if interactive mode, 0 otherwise
 */
int interactive(info_t *info)
{
	/* Check if the standard input is a terminal and readfd is within valid range */
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * is_delim - checks if a character is a delimiter
 * @c: the character to check
 * @delim: the delimiter string
 *
 * Return: 1 if true, 0 if false
 */
int is_delim(char c, char *delim)
{
	/* Iterate through the delimiter string and check if the character is a delimiter */
	while (*delim)
		if (*delim++ == c)
			return (1);
	
	/* Return 0 if the character is not a delimiter */
	return (0);
}

/**
 *_isalpha - checks for alphabetic character
 *@c: The character to input
 *Return: 1 if c is alphabetic, 0 otherwise
 */
int _isalpha(int c)
{
	/* Check if the character is an alphabetic character */
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 *_atoi - converts a string to an integer
 *@s: the string to be converted
 *Return: 0 if no numbers in string, converted number otherwise
 */
int _atoi(char *s)
{
	int i, sign = 1, flag = 0, output;
	unsigned int result = 0;

	/* Iterate through the string and process the characters to obtain the integer */
	for (i = 0;  s[i] != '\0' && flag != 2; i++)
	{
		/* Check for the sign of the number */
		if (s[i] == '-')
			sign *= -1;

		/* Check if the character is a digit */
		if (s[i] >= '0' && s[i] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (s[i] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

	/* Apply the sign to the result to obtain the final output */
	if (sign == -1)
		output = -result;
	else
		output = result;

	return (output);
}
