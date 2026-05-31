#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "huffman.h"

/**
 * is_leaf - Checks if a node is a leaf node
 *
 * @node: Pointer to the node to check
 *
 * Return: 1 if leaf, 0 otherwise
 */
static int is_leaf(binary_tree_node_t *node)
{
	return (node->left == NULL && node->right == NULL);
}

/**
 * traverse - Traverses the Huffman tree and prints codes
 *
 * @node: Pointer to current node
 * @code: Current code string
 * @depth: Current depth in tree
 *
 * Return: 1 on success, 0 on failure
 */
static int traverse(binary_tree_node_t *node, char *code, size_t depth)
{
	symbol_t *symbol;

	if (node == NULL)
		return (1);

	if (is_leaf(node))
	{
		symbol = (symbol_t *)node->data;
		code[depth] = '\0';
		printf("%c: %s\n", symbol->data, code);
		return (1);
	}

	code[depth] = '0';
	if (!traverse(node->left, code, depth + 1))
		return (0);

	code[depth] = '1';
	if (!traverse(node->right, code, depth + 1))
		return (0);

	return (1);
}

/**
 * free_tree - Frees the entire Huffman tree
 *
 * @node: Pointer to the root node
 */
static void free_tree(binary_tree_node_t *node)
{
	if (node == NULL)
		return;
	free_tree(node->left);
	free_tree(node->right);
	free(node->data);
	free(node);
}

/**
 * huffman_codes - Builds Huffman tree and prints codes for each symbol
 *
 * @data: Array of characters
 * @freq: Array of associated frequencies
 * @size: Size of the arrays
 *
 * Return: 1 on success, 0 on failure
 */
int huffman_codes(char *data, size_t *freq, size_t size)
{
	binary_tree_node_t *root;
	char *code;
	int result;

	if (data == NULL || freq == NULL || size == 0)
		return (0);

	root = huffman_tree(data, freq, size);
	if (root == NULL)
		return (0);

	code = malloc(sizeof(char) * (size + 1));
	if (code == NULL)
	{
		free_tree(root);
		return (0);
	}

	result = traverse(root, code, 0);

	free(code);
	free_tree(root);

	return (result);
}
