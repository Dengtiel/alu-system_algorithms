#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "pathfinding.h"

/**
 * backtrack_graph - Recursively searches for path in graph
 *
 * @current: Current vertex
 * @target: Target vertex
 * @visited: Array of visited vertex names
 * @visited_count: Pointer to number of visited vertices
 * @path: Queue to store the path
 *
 * Return: 1 if path found, 0 otherwise
 */
static int backtrack_graph(vertex_t const *current, vertex_t const *target,
	char **visited, size_t *visited_count, queue_t *path)
{
	edge_t *edge;
	char *city;
	size_t i;

	printf("Checking %s\n", current->content);
	visited[(*visited_count)++] = current->content;

	if (strcmp(current->content, target->content) == 0)
	{
		city = strdup(current->content);
		if (!city)
			return (0);
		queue_push_front(path, city);
		return (1);
	}

	edge = current->edges;
	while (edge)
	{
		for (i = 0; i < *visited_count; i++)
			if (strcmp(visited[i], edge->dest->content) == 0)
				break;
		if (i == *visited_count)
		{
			if (backtrack_graph(edge->dest, target,
				visited, visited_count, path))
			{
				city = strdup(current->content);
				if (!city)
					return (0);
				queue_push_front(path, city);
				return (1);
			}
		}
		edge = edge->next;
	}
	return (0);
}

/**
 * backtracking_graph - Searches for first path in a graph
 *
 * @graph: Pointer to the graph
 * @start: Starting vertex
 * @target: Target vertex
 *
 * Return: Queue containing path, or NULL if no path found
 */
queue_t *backtracking_graph(graph_t *graph, vertex_t const *start,
	vertex_t const *target)
{
	queue_t *path;
	char **visited;
	size_t visited_count;

	if (!graph || !start || !target)
		return (NULL);

	visited = malloc(sizeof(char *) * graph->nb_vertices);
	if (!visited)
		return (NULL);

	path = queue_create();
	if (!path)
	{
		free(visited);
		return (NULL);
	}

	visited_count = 0;
	if (!backtrack_graph(start, target, visited, &visited_count, path))
	{
		queue_delete(path);
		path = NULL;
	}

	free(visited);
	return (path);
}
