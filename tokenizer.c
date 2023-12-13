#include "shell.h"

/**
 * **strtow - splits a string into words. Repeat delimiters are ignored
 * @str: the input string
 * @d: the delimiter string
 * Return: a pointer to an array of strings, or NULL on failure
 */
char **strtow(char *str, char *d)
{
	int i, j, k, m, numwords = 0;
	char **s;

	// Check if the input string is NULL or empty
	if (str == NULL || str[0] == 0)
		return (NULL);

	// If delimiter is not provided, use space as the default delimiter
	if (!d)
		d = " ";

	// Count the number of words in the string
	for (i = 0; str[i] != '\0'; i++)
		if (!is_delim(str[i], d) && (is_delim(str[i + 1], d) || !str[i + 1]))
			numwords++;

	// If no words found, return NULL
	if (numwords == 0)
		return (NULL);

	// Allocate memory for the array of strings
	s = malloc((1 + numwords) * sizeof(char *));
	if (!s)
		return (NULL);

	// Populate the array of strings
	for (i = 0, j = 0; j < numwords; j++)
	{
		while (is_delim(str[i], d))
			i++;

		k = 0;
		while (!is_delim(str[i + k], d) && str[i + k])
			k++;

		// Allocate memory for each word
		s[j] = malloc((k + 1) * sizeof(char));
		if (!s[j])
		{
			// Free previously allocated memory in case of failure
			for (k = 0; k < j; k++)
				free(s[k]);
			free(s);
			return (NULL);
		}

		// Copy characters to the allocated memory
		for (m = 0; m < k; m++)
			s[j][m] = str[i++];
		s[j][m] = 0;
	}

	// Set the last element of the array to NULL
	s[j] = NULL;

	return (s);
}

/**
 * **strtow2 - splits a string into words
 * @str: the input string
 * @d: the delimiter
 * Return: a pointer to an array of strings, or NULL on failure
 */
char **strtow2(char *str, char d)
{
	int i, j, k, m, numwords = 0;
	char **s;

	// Check if the input string is NULL or empty
	if (str == NULL || str[0] == 0)
		return (NULL);

	// Count the number of words in the string
	for (i = 0; str[i] != '\0'; i++)
		if ((str[i] != d && str[i + 1] == d) ||
		    (str[i] != d && !str[i + 1]) || str[i + 1] == d)
			numwords++;

	// If no words found, return NULL
	if (numwords == 0)
		return (NULL);

	// Allocate memory for the array of strings
	s = malloc((1 + numwords) * sizeof(char *));
	if (!s)
		return (NULL);

	// Populate the array of strings
	for (i = 0, j = 0; j < numwords; j++)
	{
		while (str[i] == d && str[i] != d)
			i++;

		k = 0;
		while (str[i + k] != d && str[i + k] && str[i + k] != d)
			k++;

		// Allocate memory for each word
		s[j] = malloc((k + 1) * sizeof(char));
		if (!s[j])
		{
			// Free previously allocated memory in case of failure
			for (k = 0; k < j; k++)
				free(s[k]);
			free(s);
			return (NULL);
		}

		// Copy characters to the allocated memory
		for (m = 0; m < k; m++)
			s[j][m] = str[i++];
		s[j][m] = 0;
	}

	// Set the last element of the array to NULL
	s[j] = NULL;

	return (s);
}
