#include <stdlib.h>
#include <string.h>
#include "graphs.h"

static vertex_t *find_vertex(graph_t *graph, const char *str)
{
	vertex_t *tmp;

	tmp = graph->vertices;
	while (tmp)
	{
		if (strcmp(tmp->content, str) == 0)
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

static int create_edge(vertex_t *src, vertex_t *dest)
{
	edge_t *new_edge;
	edge_t *tmp;

	new_edge = malloc(sizeof(edge_t));
	if (!new_edge)
		return (0);
	new_edge->dest = dest;
	new_edge->next = NULL;
	if (!src->edges)
		src->edges = new_edge;
	else
	{
		tmp = src->edges;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_edge;
	}
	src->nb_edges++;
	return (1);
}

static void remove_last_edge(vertex_t *src)
{
	edge_t *e;
	edge_t *prev;

	e = src->edges;
	prev = NULL;
	while (e->next)
	{
		prev = e;
		e = e->next;
	}
	if (prev)
		prev->next = NULL;
	else
		src->edges = NULL;
	src->nb_edges--;
	free(e);
}

/**
 * graph_add_edge - Adds an edge between two vertices in a graph
 * @graph: Pointer to the graph
 * @src: String identifying the source vertex
 * @dest: String identifying the destination vertex
 * @type: Type of edge (UNIDIRECTIONAL or BIDIRECTIONAL)
 *
 * Return: 1 on success, 0 on failure
 */
int graph_add_edge(graph_t *graph, const char *src,
		const char *dest, edge_type_t type)
{
	vertex_t *v_src;
	vertex_t *v_dest;

	if (!graph || !src || !dest)
		return (0);
	v_src = find_vertex(graph, src);
	v_dest = find_vertex(graph, dest);
	if (!v_src || !v_dest)
		return (0);
	if (!create_edge(v_src, v_dest))
		return (0);
	if (type == BIDIRECTIONAL)
	{
		if (!create_edge(v_dest, v_src))
		{
			remove_last_edge(v_src);
			return (0);
		}
	}
	return (1);
}
