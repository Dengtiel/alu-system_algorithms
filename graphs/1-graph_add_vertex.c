#include <stdlib.h>
#include <string.h>
#include "graphs.h"

/**
 * vertex_exists - Checks if a vertex with the given string exists
 * @graph: Pointer to the graph
 * @str: The string to search for
 *
 * Return: The number of vertices (index for new one), or -1 if exists
 */
static int vertex_exists(graph_t *graph, const char *str)
{
	vertex_t *tmp;
	int       index;

	tmp = graph->vertices;
	index = 0;
	while (tmp)
	{
		if (strcmp(tmp->content, str) == 0)
			return (-1);
		index++;
		tmp = tmp->next;
	}
	return (index);
}

/**
 * graph_add_vertex - Adds a vertex to an existing graph
 * @graph: Pointer to the graph to add the vertex to
 * @str: The string to store in the new vertex
 *
 * Return: Pointer to the created vertex, or NULL on failure
 */
vertex_t *graph_add_vertex(graph_t *graph, const char *str)
{
	vertex_t *new_vertex;
	vertex_t *tmp;
	int       index;

	if (!graph || !str)
		return (NULL);

	index = vertex_exists(graph, str);
	if (index == -1)
		return (NULL);

	new_vertex = malloc(sizeof(vertex_t));
	if (!new_vertex)
		return (NULL);

	new_vertex->content = strdup(str);
	if (!new_vertex->content)
	{
		free(new_vertex);
		return (NULL);
	}

	new_vertex->index    = index;
	new_vertex->nb_edges = 0;
	new_vertex->edges    = NULL;
	new_vertex->next     = NULL;

	if (!graph->vertices)
		graph->vertices = new_vertex;
	else
	{
		tmp = graph->vertices;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_vertex;
	}

	graph->nb_vertices++;
	return (new_vertex);
}
