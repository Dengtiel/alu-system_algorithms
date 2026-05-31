#include <stdlib.h>
#include "huffman.h"

/**
 * symbol_cmp - Compares two nested nodes by symbol frequency
 *
 * @p1: First pointer (binary_tree_node_t containing symbol_t)
 * @p2: Second pointer (binary_tree_node_t containing symbol_t)
 *
 * Return: Difference between the two frequencies
 */
static int symbol_cmp(void *p1, void *p2)
{
	binary_tree_node_t *n1, *n2;
	symbol_t *s1, *s2;

	n1 = (binary_tree_node_t *)p1;
	n2 = (binary_tree_node_t *)p2;
	s1 = (symbol_t *)n1->data;
	s2 = (symbol_t *)n2->data;

	return ((int)(s1->freq) - (int)(s2->freq));
}

/**
 * huffman_priority_queue - Creates a priority queue for Huffman coding
 *
 * @data: Array of characters
 * @freq: Array of associated frequencies
 * @size: Size of the arrays
 *
 * Return: Pointer to the created min heap, or NULL if it fails
 */
heap_t *huffman_priority_queue(char *data, size_t *freq, size_t size)
{
	heap_t *heap;
	symbol_t *symbol;
	binary_tree_node_t *nested;
	size_t i;

	heap = heap_create(symbol_cmp);
	if (heap == NULL)
		return (NULL);

	for (i = 0; i < size; i++)
	{
		symbol = symbol_create(data[i], freq[i]);
		if (symbol == NULL)
		{
			heap_delete(heap, free);
			return (NULL);
		}
		nested = binary_tree_node(NULL, symbol);
		if (nested == NULL)
		{
			free(symbol);
			heap_delete(heap, free);
			return (NULL);
		}
		if (heap_insert(heap, nested) == NULL)
		{
			free(symbol);
			free(nested);
			heap_delete(heap, free);
			return (NULL);
		}
	}
	return (heap);
}
