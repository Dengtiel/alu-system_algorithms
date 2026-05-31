#include <stdlib.h>
#include "huffman.h"

/**
 * huffman_extract_and_insert - Extracts two nodes from priority queue
 * and inserts a new combined node
 *
 * @priority_queue: Pointer to the priority queue
 *
 * Return: 1 on success, 0 on failure
 */
int huffman_extract_and_insert(heap_t *priority_queue)
{
	binary_tree_node_t *left, *right, *parent;
	symbol_t *symbol_left, *symbol_right, *symbol_new;
	size_t combined_freq;

	if (priority_queue == NULL)
		return (0);

	/* Extract two least frequent nodes */
	left = (binary_tree_node_t *)heap_extract(priority_queue);
	if (left == NULL)
		return (0);

	right = (binary_tree_node_t *)heap_extract(priority_queue);
	if (right == NULL)
		return (0);

	/* Get their frequencies */
	symbol_left = (symbol_t *)left->data;
	symbol_right = (symbol_t *)right->data;
	combined_freq = symbol_left->freq + symbol_right->freq;

	/* Create new symbol with combined frequency */
	symbol_new = symbol_create(-1, combined_freq);
	if (symbol_new == NULL)
		return (0);

	/* Create new nested node as parent of left and right */
	parent = binary_tree_node(NULL, symbol_new);
	if (parent == NULL)
	{
		free(symbol_new);
		return (0);
	}

	/* Set left and right children */
	parent->left = left;
	parent->right = right;
	left->parent = parent;
	right->parent = parent;

	/* Insert new nested node back into priority queue */
	if (heap_insert(priority_queue, parent) == NULL)
	{
		free(symbol_new);
		free(parent);
		return (0);
	}

	return (1);
}
