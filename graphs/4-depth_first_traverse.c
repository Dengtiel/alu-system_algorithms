#include <stdlib.h>
#include <string.h>
#include "graphs.h"

/**
 * dfs - Recursive depth-first traversal helper
 * @v: Pointer to the current vertex
 * @visited: Array tracking visited vertex indices
 * @depth: Current depth from starting vertex
 * @max_depth: Pointer to the maximum depth reached
 * @action: Function to call on each visited vertex
 */
static void dfs(const vertex_t *v, int *visited, size_t depth,
		size_t *max_depth, void (*action)(const vertex_t *, size_t))
{
	edge_t *e;

	if (visited[v->index])
		return;
	visited[v->index] = 1;
	action(v, depth);
	if (depth > *max_depth)
		*max_depth = depth;
	e = v->edges;
	while (e)
	{
		dfs(e->dest, visited, depth + 1, max_depth, action);
		e = e->next;
	}
}

/**
 * depth_first_traverse - Traverses a graph using depth-first algorithm
 * @graph: Pointer to the graph to traverse
 * @action: Function to call for each visited vertex
 *
 * Return: The biggest vertex depth, or 0 on failure
 */
size_t depth_first_traverse(const graph_t *graph,
		void (*action)(const vertex_t *v, size_t depth))
{
	int    *visited;
	size_t  max_depth;

	if (!graph || !action || !graph->vertices)
		return (0);
	visited = calloc(graph->nb_vertices, sizeof(int));
	if (!visited)
		return (0);
	max_depth = 0;
	dfs(graph->vertices, visited, 0, &max_depth, action);
	free(visited);
	return (max_depth);
}
