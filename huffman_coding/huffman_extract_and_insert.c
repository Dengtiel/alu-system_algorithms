#include <stdlib.h>
#include "huffman.h"

/**
 * create_combined - Creates a combined parent node from two extracted nodes
 *
 * @left: Left child node
 * @right: Right child node
 *
 * Return: New parent binary_tree_node_t, or NULL on failure
 */
static binary_tree_node_t *create_combined(binary_tree_node_t *left,
	binary_tree_node_t *right)
{
	symbol_t *symbol_left, *symbol_right, *symbol_new;
	binary_tree_node_t *parent;
	size_t combined_freq;

	symbol_left = (symbol_t *)left->data;
	symbol_right = (symbol_t *)right->data;
	combined_freq = symbol_left->freq + symbol_right->freq;

	symbol_new = symbol_create(-1, combined_freq);
	if (symbol_new == NULL)
		return (NULL);

	parent = binary_tree_node(NULL, symbol_new);
	if (parent == NULL)
	{
		free(symbol_new);
		return (NULL);
	}

	parent->left = left;
	parent->right = right;
	left->parent = parent;
	right->parent = parent;

	return (parent);
}

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

	if (priority_queue == NULL)
		return (0);

	left = (binary_tree_node_t *)heap_extract(priority_queue);
	if (left == NULL)
		return (0);

	right = (binary_tree_node_t *)heap_extract(priority_queue);
	if (right == NULL)
		return (0);

	parent = create_combined(left, right);
	if (parent == NULL)
		return (0);

	if (heap_insert(priority_queue, parent) == NULL)
	{
		free(parent->data);
		free(parent);
		return (0);
	}

	return (1);
}
