#include <stdlib.h>
#include "heap.h"

/**
 * get_insert_parent - Finds parent node for next insertion spot
 *
 * @root: Root of the heap
 * @size: Current size of heap
 *
 * Return: Pointer to parent node
 */
static binary_tree_node_t *get_insert_parent(binary_tree_node_t *root,
	size_t size)
{
	size_t index;
	size_t mask;

	index = size + 1;
	mask = 1;
	while (mask <= index / 2)
		mask <<= 1;
	mask >>= 1;

	while (mask > 1)
	{
		if (index & mask)
			root = root->right;
		else
			root = root->left;
		mask >>= 1;
	}
	return (root);
}

/**
 * heapify_up - Bubbles node up to restore min-heap property
 *
 * @node: Newly inserted node
 * @heap: Pointer to the heap
 */
static void heapify_up(binary_tree_node_t *node, heap_t *heap)
{
	void *tmp;

	while (node->parent != NULL &&
		heap->data_cmp(node->data, node->parent->data) < 0)
	{
		tmp = node->data;
		node->data = node->parent->data;
		node->parent->data = tmp;
		node = node->parent;
	}
}

/**
 * heap_insert - Inserts a value in a Min Binary Heap
 *
 * @heap: Pointer to the heap
 * @data: Pointer to the data to store
 *
 * Return: Pointer to the created node, or NULL if it fails
 */
binary_tree_node_t *heap_insert(heap_t *heap, void *data)
{
	binary_tree_node_t *parent;
	binary_tree_node_t *node;

	if (heap == NULL || data == NULL)
		return (NULL);

	node = binary_tree_node(NULL, data);
	if (node == NULL)
		return (NULL);

	if (heap->root == NULL)
	{
		heap->root = node;
		heap->size++;
		return (node);
	}

	parent = get_insert_parent(heap->root, heap->size);

	node->parent = parent;
	if (parent->left == NULL)
		parent->left = node;
	else
		parent->right = node;

	heap->size++;
	heapify_up(node, heap);

	return (node);
}
