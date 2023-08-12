#include "shell.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/**
 * list_len - Calculate the length of a linked list.
 *
 * This function iterates through the linked list starting
 * from the given head node and counts the number of nodes
 * in the list.
 *
 * @h: Pointer to the head node of the linked list.
 *
 * Return: The number of nodes in the linked list.
 */
size_t list_len(const list_t *h)
{
	size_t i;
	const list_t *start;

	start = h;

	i = 0;
	while (start != NULL)
	{
		i++;
		start = start->next;
	}
	return (i);
}
/**
 * add_node_end - Add a new node to the end of a linked list.
 *
 * This function creates a new node, initializes its values with the given
 * string and its length, and appends it to the end of the linked list.
 *
 * @head: Pointer to the pointer to the head node of the linked list.
 *              The function will update this pointer if the list is empty.
 * @str: Pointer to the string that will be stored in the new node.
 *
 * Return: Pointer to the newly created node
 * , or NULL if allocation fails.
 */
list_t *add_node_end(list_t **head, char *str)
{
	list_t *new_node, *trav;

	new_node = malloc(sizeof(list_t));

	if (new_node == NULL)
		return (NULL);

	new_node->arg = str;
	new_node->next = NULL;

	if (*head == NULL)
	{
		*head = new_node;
		return (*head);
	}

	trav = *head;
	while (trav->next != NULL)
	{
		trav = trav->next;
	}
	trav->next = new_node;

	return (*head);
}
/**
 * free_list - Frees the memory allocated for a linked list.
 *
 * This function iterates through the linked list
 * starting from the head node and frees the
 * memory for each node, including the head. It sets the `head`
 * pointer to NULL after freeing all the nodes.
 *
 * @head: Pointer to the head node of the linked list.
 */
void free_list(list_t *head)
{
	list_t *current, *nextNode;

	current = head;
	while (current != NULL)
	{
		nextNode = current->next;
		free(current);
		current = nextNode;
	}
}
