#include <stdlib.h>
#include "graphs.h"

/**
 * graph_delete - Completely deletes a graph
 * @graph: Pointer to the graph to delete
 *
 * Return: void
 */
void graph_delete(graph_t *graph)
{
	vertex_t *v;
	vertex_t *v_next;
	edge_t   *e;
	edge_t   *e_next;

	if (!graph)
		return;
	v = graph->vertices;
	while (v)
	{
		e = v->edges;
		while (e)
		{
			e_next = e->next;
			free(e);
			e = e_next;
		}
		v_next = v->next;
		free(v->content);
		free(v);
		v = v_next;
	}
	free(graph);
}
