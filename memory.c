#include "shell.h"

/**
 * bfree - frees a pointer and NULLs the address
 * @ptr: address of the pointer to free
 *
 * Return: 1 if freed, otherwise 0.
 */
int bfree(void **ptr)
{
	// Check if the pointer and the content it points to exist
	if (ptr && *ptr)
	{
		free(*ptr); // Free the memory allocated for the content
		*ptr = NULL; // Set the pointer to NULL to avoid using a dangling pointer
		return (1); // Return 1 to indicate successful freeing
	}
	return (0); // Return 0 to indicate failure or if the pointer is already NULL
}
