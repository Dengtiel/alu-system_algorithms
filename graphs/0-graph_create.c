#include <stdlib.h>
#include "graphs.h"

/**
 * graph_create - Allocates and initializes a graph_t structure
 *
 * Return: Pointer to the newly allocated graph, or NULL on failure
 */
graph_t *graph_create(void)
{
	graph_t *graph;

	graph = malloc(sizeof(graph_t));
	if (!graph)
		return (NULL);

	graph->nb_vertices = 0;
	graph->vertices = NULL;

	return (graph);
}
