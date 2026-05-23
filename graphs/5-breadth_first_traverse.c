#include <stdlib.h>
#include "graphs.h"

/**
 * struct queue_node_s - Node in a queue
 * @v: Pointer to the vertex
 * @depth: Depth of the vertex from the starting vertex
 * @next: Pointer to the next node in the queue
 */
typedef struct queue_node_s
{
	const vertex_t    *v;
	size_t             depth;
	struct queue_node_s *next;
} queue_node_t;

/**
 * enqueue - Adds a node to the end of the queue
 * @head: Pointer to the head of the queue
 * @tail: Pointer to the tail of the queue
 * @v: Vertex to enqueue
 * @depth: Depth of the vertex
 *
 * Return: 1 on success, 0 on failure
 */
static int enqueue(queue_node_t **head, queue_node_t **tail,
		const vertex_t *v, size_t depth)
{
	queue_node_t *node;

	node = malloc(sizeof(queue_node_t));
	if (!node)
		return (0);
	node->v = v;
	node->depth = depth;
	node->next = NULL;
	if (!*head)
		*head = *tail = node;
	else
	{
		(*tail)->next = node;
		*tail = node;
	}
	return (1);
}

/**
 * dequeue - Removes and returns the front node of the queue
 * @head: Pointer to the head of the queue
 *
 * Return: Pointer to the removed node
 */
static queue_node_t *dequeue(queue_node_t **head)
{
	queue_node_t *node;

	node = *head;
	*head = (*head)->next;
	return (node);
}

/**
 * breadth_first_traverse - Traverses a graph using breadth-first algorithm
 * @graph: Pointer to the graph to traverse
 * @action: Function to call for each visited vertex
 *
 * Return: The biggest vertex depth, or 0 on failure
 */
size_t breadth_first_traverse(const graph_t *graph,
		void (*action)(const vertex_t *v, size_t depth))
{
	queue_node_t *head, *tail, *node;
	int          *visited;
	size_t        max_depth;
	edge_t       *e;

	if (!graph || !action || !graph->vertices)
		return (0);
	visited = calloc(graph->nb_vertices, sizeof(int));
	if (!visited)
		return (0);
	head = tail = NULL;
	max_depth = 0;
	enqueue(&head, &tail, graph->vertices, 0);
	visited[graph->vertices->index] = 1;
	while (head)
	{
		node = dequeue(&head);
		action(node->v, node->depth);
		if (node->depth > max_depth)
			max_depth = node->depth;
		e = node->v->edges;
		while (e)
		{
			if (!visited[e->dest->index])
			{
				visited[e->dest->index] = 1;
				enqueue(&head, &tail, e->dest, node->depth + 1);
			}
			e = e->next;
		}
		free(node);
	}
	free(visited);
	return (max_depth);
}
