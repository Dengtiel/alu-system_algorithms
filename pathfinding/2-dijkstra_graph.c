#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "pathfinding.h"

#define INF ((size_t)-1)

/**
 * get_min_vertex - Gets unvisited vertex with minimum distance
 *
 * @graph: Pointer to the graph
 * @dist: Array of distances
 * @visited: Array of visited flags
 * @n: Number of vertices
 *
 * Return: Pointer to the vertex, or NULL if none found
 */
static vertex_t *get_min_vertex(graph_t *graph, size_t *dist,
	int *visited, size_t n)
{
	vertex_t *v, *min_v;
	size_t i, min_i;

	min_v = NULL;
	min_i = 0;
	v = graph->vertices;
	for (i = 0; i < n && v; i++, v = v->next)
	{
		if (!visited[i] && (min_v == NULL || dist[i] < dist[min_i]))
		{
			min_v = v;
			min_i = i;
		}
	}
	return (min_v);
}


/**
 * build_path - Builds the path queue from predecessor array
 *
 * @graph: Pointer to the graph
 * @prev: Array of predecessor indices
 * @target_idx: Index of target vertex
 * @n: Number of vertices
 *
 * Return: Queue containing path, or NULL on failure
 */
static queue_t *build_path(graph_t *graph, size_t *prev,
	size_t target_idx, size_t n)
{
	queue_t *path;
	vertex_t *v;
	char *city;
	size_t *stack, count, idx, i, j;

	path = queue_create();
	if (!path)
		return (NULL);
	stack = malloc(sizeof(size_t) * n);
	if (!stack)
	{
		queue_delete(path);
		return (NULL);
	}
	count = 0;
	idx = target_idx;
	while (idx != INF)
	{
		stack[count++] = idx;
		idx = prev[idx];
	}
	for (i = count; i > 0; i--)
	{
		v = graph->vertices;
		for (j = 0; v && j < stack[i - 1]; j++)
			v = v->next;
		if (!v)
			break;
		city = strdup(v->content);
		if (!city)
		{
			free(stack);
			queue_delete(path);
			return (NULL);
		}
		queue_push_back(path, city);
	}
	free(stack);
	return (path);
}

/**
 * relax_edges - Relaxes edges from current vertex
 *
 * @u: Current vertex
 * @dist: Distance array
 * @prev: Predecessor array
 * @visited: Visited array
 */
static void relax_edges(vertex_t *u, size_t *dist,
	size_t *prev, int *visited)
{
	edge_t *e;
	size_t i;

	for (e = u->edges; e; e = e->next)
	{
		i = e->dest->index;
		if (!visited[i] && dist[u->index] + e->weight < dist[i])
		{
			dist[i] = dist[u->index] + e->weight;
			prev[i] = u->index;
		}
	}
}
/**
 * alloc_init - Allocates and initializes arrays for Dijkstra
 *
 * @n: Number of vertices
 * @dist: Distance array
 * @prev: Predecessor array
 * @visited: Visited array
 * @start_idx: Start vertex index
 *
 * Return: 1 on success, 0 on failure
 */
static int alloc_init(size_t n, size_t **dist, size_t **prev,
	int **visited, size_t start_idx)
{
	*dist = malloc(sizeof(size_t) * n);
	*prev = malloc(sizeof(size_t) * n);
	*visited = malloc(sizeof(int) * n);
	if (!*dist || !*prev || !*visited)
	{
		free(*dist);
		free(*prev);
		free(*visited);
		return (0);
	}
	memset(*dist, -1, sizeof(size_t) * n);
	memset(*prev, -1, sizeof(size_t) * n);
	memset(*visited, 0, sizeof(int) * n);
	(*dist)[start_idx] = 0;
	return (1);
}
/**
 * dijkstra_graph - Finds shortest path using Dijkstra algorithm
 *
 * @graph: Pointer to the graph
 * @start: Starting vertex
 * @target: Target vertex
 *
 * Return: Queue containing shortest path, or NULL if no path found
 */

queue_t *dijkstra_graph(graph_t *graph, vertex_t const *start,
	vertex_t const *target)
{
	size_t *dist, *prev, n, u_idx;
	int *visited;
	vertex_t *u;
	queue_t *path;

	if (!graph || !start || !target)
		return (NULL);
	n = graph->nb_vertices;
	if (!alloc_init(n, &dist, &prev, &visited, start->index))
	memset(visited, 0, sizeof(int) * n);
	while ((u = get_min_vertex(graph, dist, visited, n)) != NULL)
	{
		u_idx = u->index;
		if (dist[u_idx] == INF)
			break;
		visited[u_idx] = 1;
		printf("Checking %s, distance from %s is %lu\n",
			u->content, start->content, dist[u_idx]);
		if (u_idx == target->index)
			break;
		relax_edges(u, dist, prev, visited);
	}
	path = NULL;
	if (dist[target->index] != INF)
		path = build_path(graph, prev, target->index, n);
	free(dist);
	free(prev);
	free(visited);
	return (path);
}
