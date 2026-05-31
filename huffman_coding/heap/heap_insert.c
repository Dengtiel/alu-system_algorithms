#include <stdlib.h>
#include "heap.h"

/**
 * get_insert_parent - Finds the parent node where new node should be inserted
 *
 * @root: Root of the heap
 * @size: Current size of the heap
 *
 * Return: Pointer to the parent node
 */
static binary_tree_node_t *get_insert_parent(binary_tree_node_t *root,
	size_t size)
{
	size_t path;
	int bits;

	/* Find path from root to insertion point using binary representation */
	size = size + 1;
	bits = 0;
	path = size;
	while (path > 1)
	{
		path >>= 1;
		bits++;
	}

	/* Traverse from root following the bits (excluding the leading 1) */
	path = size;
	bits--;
	while (bits > 1)
	{
		if (path & (1 << bits))
			root = root->right;
		else
			root = root->left;
		bits--;
	}
	return (root);
}

/**
 * swap_data - Swaps the data between two nodes
 *
 * @a: First node
 * @b: Second node
 */
static void swap_data(binary_tree_node_t *a, binary_tree_node_t *b)
{
	void *tmp;

	tmp = a->data;
	a->data = b->data;
	b->data = tmp;
}

/**
 * heapify_up - Restores min-heap property by bubbling node up
 *
 * @node: Newly inserted node
 * @data_cmp: Comparison function
 */
static void heapify_up(binary_tree_node_t *node,
	int (*data_cmp)(void *, void *))
{
	while (node->parent != NULL &&
		data_cmp(node->data, node->parent->data) < 0)
	{
		swap_data(node, node->parent);
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

	/* If heap is empty, new node becomes root */
	if (heap->root == NULL)
	{
		heap->root = node;
		heap->size++;
		return (node);
	}

	/* Find the parent of the insertion point */
	parent = get_insert_parent(heap->root, heap->size);

	/* Attach new node to parent */
	node->parent = parent;
	if (parent->left == NULL)
		parent->left = node;
	else
		parent->right = node;

	heap->size++;

	/* Restore min-heap property */
	heapify_up(node, heap->data_cmp);

	return (node);
}
