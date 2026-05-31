#include <stdlib.h>
#include "heap.h"

/**
 * get_last_node - Gets the last node in level-order
 *
 * @root: Root of the heap
 * @size: Current size of the heap
 *
 * Return: Pointer to the last node
 */
static binary_tree_node_t *get_last_node(binary_tree_node_t *root,
	size_t size)
{
	size_t mask;

	mask = 1;
	while (mask <= size / 2)
		mask <<= 1;
	mask >>= 1;

	while (mask > 1)
	{
		if (size & mask)
			root = root->right;
		else
			root = root->left;
		mask >>= 1;
	}
	if (size & 1)
		return (root->right ? root->right : root->left);
	return (root->left);
}

/**
 * heapify_down - Restores min-heap by pushing node down
 *
 * @node: Node to push down
 * @heap: Pointer to the heap
 */
static void heapify_down(binary_tree_node_t *node, heap_t *heap)
{
	binary_tree_node_t *smallest;
	void *tmp;

	while (node->left != NULL)
	{
		smallest = node->left;
		if (node->right != NULL &&
			heap->data_cmp(node->right->data, smallest->data) < 0)
			smallest = node->right;

		if (heap->data_cmp(node->data, smallest->data) <= 0)
			break;

		tmp = node->data;
		node->data = smallest->data;
		smallest->data = tmp;
		node = smallest;
	}
}

/**
 * heap_extract - Extracts the root value of a Min Binary Heap
 *
 * @heap: Pointer to the heap
 *
 * Return: Pointer to the data stored in root node, or NULL if fails
 */
void *heap_extract(heap_t *heap)
{
	binary_tree_node_t *last;
	void *data;

	if (heap == NULL || heap->root == NULL)
		return (NULL);

	data = heap->root->data;

	if (heap->size == 1)
	{
		free(heap->root);
		heap->root = NULL;
		heap->size = 0;
		return (data);
	}

	last = get_last_node(heap->root, heap->size);

	heap->root->data = last->data;

	if (last->parent->right == last)
		last->parent->right = NULL;
	else
		last->parent->left = NULL;

	free(last);
	heap->size--;

	heapify_down(heap->root, heap);

	return (data);
}
