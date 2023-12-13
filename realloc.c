#include "shell.h"

/**
 **_memset - fills memory with a constant byte
 *@s: the pointer to the memory area
 *@b: the byte to fill *s with
 *@n: the amount of bytes to be filled
 *Return: (s) a pointer to the memory area s
 */
char *_memset(char *s, char b, unsigned int n)
{
	unsigned int i;

	// Iterate through the memory area and fill with the constant byte
	for (i = 0; i < n; i++)
		s[i] = b;
	return (s); // Return a pointer to the memory area s
}

/**
 * ffree - frees a string of strings
 * @pp: string of strings
 */
void ffree(char **pp)
{
	char **a = pp;

	if (!pp)
		return;

	// Free each string in the string of strings
	while (*pp)
		free(*pp++);
	free(a); // Free the string of strings itself
}

/**
 * _realloc - reallocates a block of memory
 * @ptr: pointer to previous malloc'ated block
 * @old_size: byte size of previous block
 * @new_size: byte size of new block
 *
 * Return: pointer to da ol'block nameen.
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *p;

	if (!ptr)
		return (malloc(new_size)); // Allocate new memory block if ptr is NULL
	if (!new_size)
		return (free(ptr), NULL); // Free and return NULL if new_size is 0
	if (new_size == old_size)
		return (ptr); // Return the original pointer if sizes are the same

	// Allocate a new memory block of the specified size
	p = malloc(new_size);
	if (!p)
		return (NULL); // Return NULL if malloc fails

	// Copy the content from the old block to the new block
	old_size = old_size < new_size ? old_size : new_size;
	while (old_size--)
		p[old_size] = ((char *)ptr)[old_size];

	free(ptr); // Free the old memory block
	return (p); // Return the pointer to the new memory block
}
