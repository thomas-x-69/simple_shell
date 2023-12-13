#include "shell.h"

/**
 * add_node - adds a node to the start of the list
 * @head: address of pointer to head node
 * @str: str field of node
 * @num: node index used by history
 *
 * Return: size of list
 */
list_t *add_node(list_t **head, const char *str, int num)
{
	list_t *new_head;

	// Check if head is NULL
	if (!head)
		return (NULL);

	// Allocate memory for the new node
	new_head = malloc(sizeof(list_t));
	if (!new_head)
		return (NULL);

	// Initialize the new node
	_memset((void *)new_head, 0, sizeof(list_t));
	new_head->num = num;

	// Duplicate the string if not NULL
	if (str)
	{
		new_head->str = _strdup(str);
		if (!new_head->str)
		{
			free(new_head);
			return (NULL);
		}
	}

	// Update the next pointer of the new node to point to the current head
	new_head->next = *head;

	// Update the head pointer to the new node
	*head = new_head;

	return (new_head);
}

/**
 * add_node_end - adds a node to the end of the list
 * @head: address of pointer to head node
 * @str: str field of node
 * @num: node index used by history
 *
 * Return: size of list
 */
list_t *add_node_end(list_t **head, const char *str, int num)
{
	list_t *new_node, *node;

	// Check if head is NULL
	if (!head)
		return (NULL);

	// Get a reference to the head node
	node = *head;

	// Allocate memory for the new node
	new_node = malloc(sizeof(list_t));
	if (!new_node)
		return (NULL);

	// Initialize the new node
	_memset((void *)new_node, 0, sizeof(list_t));
	new_node->num = num;

	// Duplicate the string if not NULL
	if (str)
	{
		new_node->str = _strdup(str);
		if (!new_node->str)
		{
			free(new_node);
			return (NULL);
		}
	}

	// If the list is not empty, iterate to the end and append the new node
	if (node)
	{
		while (node->next)
			node = node->next;
		node->next = new_node;
	}
	// If the list is empty, update the head pointer to the new node
	else
		*head = new_node;

	return (new_node);
}

/**
 * print_list_str - prints only the str element of a list_t linked list
 * @h: pointer to first node
 *
 * Return: size of list
 */
size_t print_list_str(const list_t *h)
{
	size_t i = 0;

	// Iterate through the list and print the str element of each node
	while (h)
	{
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next;
		i++;
	}

	return (i);
}

/**
 * delete_node_at_index - deletes node at given index
 * @head: address of pointer to first node
 * @index: index of node to delete
 *
 * Return: 1 on success, 0 on failure
 */
int delete_node_at_index(list_t **head, unsigned int index)
{
	list_t *node, *prev_node;
	unsigned int i = 0;

	// Check if head is NULL or if the list is empty
	if (!head || !*head)
		return (0);

	// If the index is 0, delete the first node
	if (!index)
	{
		node = *head;
		*head = (*head)->next;
		free(node->str);
		free(node);
		return (1);
	}

	// Iterate through the list to find the node at the specified index
	node = *head;
	while (node)
	{
		if (i == index)
		{
			// Update the previous node's next pointer to skip the current node
			prev_node->next = node->next;
			free(node->str);
			free(node);
			return (1);
		}
		i++;
		prev_node = node;
		node = node->next;
	}

	return (0);
}

/**
 * free_list - frees all nodes of a list
 * @head_ptr: address of pointer to head node
 *
 * Return: void
 */
void free_list(list_t **head_ptr)
{
	list_t *node, *next_node, *head;

	// Check if head_ptr is NULL or if the list is empty
	if (!head_ptr || !*head_ptr)
		return;

	// Get a reference to the head node
	head = *head_ptr;
	node = head;

	// Iterate through the list and free each node
	while (node)
	{
		next_node = node->next;
		free(node->str);
		free(node);
		node = next_node;
	}

	// Set the head pointer to NULL after freeing all nodes
	*head_ptr = NULL;
}
