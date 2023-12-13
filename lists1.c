#include "shell.h"

/**
 * list_len - determines the length of a linked list
 * @h: pointer to the first node
 *
 * Return: size of the list
 */
size_t list_len(const list_t *h)
{
	size_t i = 0;

	// Iterate through the list and count the nodes
	while (h)
	{
		h = h->next;
		i++;
	}
	return (i);
}

/**
 * list_to_strings - returns an array of strings from the list->str
 * @head: pointer to the first node
 *
 * Return: array of strings
 */
char **list_to_strings(list_t *head)
{
	list_t *node = head;
	size_t i = list_len(head), j;
	char **strs;
	char *str;

	// Check if the list is empty
	if (!head || !i)
		return (NULL);

	// Allocate memory for the array of strings
	strs = malloc(sizeof(char *) * (i + 1));
	if (!strs)
		return (NULL);

	// Iterate through the list and copy each node's string to the array
	for (i = 0; node; node = node->next, i++)
	{
		str = malloc(_strlen(node->str) + 1);
		if (!str)
		{
			// Free the allocated memory if an error occurs
			for (j = 0; j < i; j++)
				free(strs[j]);
			free(strs);
			return (NULL);
		}

		// Copy the node's string to the array
		str = _strcpy(str, node->str);
		strs[i] = str;
	}
	// Set the last element of the array to NULL
	strs[i] = NULL;

	return (strs);
}

/**
 * print_list - prints all elements of a list_t linked list
 * @h: pointer to the first node
 *
 * Return: size of the list
 */
size_t print_list(const list_t *h)
{
	size_t i = 0;

	// Iterate through the list and print each node's number and string
	while (h)
	{
		_puts(convert_number(h->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next;
		i++;
	}
	return (i);
}

/**
 * node_starts_with - returns the node whose string starts with a prefix
 * @node: pointer to the list head
 * @prefix: string to match
 * @c: the next character after prefix to match
 *
 * Return: matching node or NULL
 */
list_t *node_starts_with(list_t *node, char *prefix, char c)
{
	char *p = NULL;

	// Iterate through the list and find the node with a string starting with the prefix
	while (node)
	{
		p = starts_with(node->str, prefix);
		if (p && ((c == -1) || (*p == c)))
			return (node);
		node = node->next;
	}
	return (NULL);
}

/**
 * get_node_index - gets the index of a node in the list
 * @head: pointer to the list head
 * @node: pointer to the node
 *
 * Return: index of the node or -1 if not found
 */
ssize_t get_node_index(list_t *head, list_t *node)
{
	size_t i = 0;

	// Iterate through the list and find the index of the specified node
	while (head)
	{
		if (head == node)
			return (i);
		head = head->next;
		i++;
	}
	// Return -1 if the node is not found in the list
	return (-1);
}
