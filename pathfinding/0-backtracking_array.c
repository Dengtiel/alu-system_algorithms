#include <stdlib.h>
#include <stdio.h>
#include "pathfinding.h"

/**
 * backtrack - Recursively searches for a path using backtracking
 *
 * @map: 2D array map
 * @visited: 2D array tracking visited cells
 * @rows: Number of rows
 * @cols: Number of columns
 * @x: Current x coordinate
 * @y: Current y coordinate
 * @target: Target point
 * @path: Queue to store the path
 *
 * Return: 1 if path found, 0 otherwise
 */
static int backtrack(char **map, int **visited, int rows, int cols,
	int x, int y, point_t const *target, queue_t *path)
{
	point_t *point;

	if (x < 0 || x >= cols || y < 0 || y >= rows)
		return (0);
	if (map[y][x] == '1' || visited[y][x])
		return (0);
	printf("Checking coordinates [%d, %d]\n", x, y);
	visited[y][x] = 1;
	if (x == target->x && y == target->y)
	{
		point = malloc(sizeof(point_t));
		if (!point)
			return (0);
		point->x = x;
		point->y = y;
		queue_push_front(path, point);
		return (1);
	}
	if (backtrack(map, visited, rows, cols, x + 1, y, target, path) ||
		backtrack(map, visited, rows, cols, x, y + 1, target, path) ||
		backtrack(map, visited, rows, cols, x - 1, y, target, path) ||
		backtrack(map, visited, rows, cols, x, y - 1, target, path))
	{
		point = malloc(sizeof(point_t));
		if (!point)
			return (0);
		point->x = x;
		point->y = y;
		queue_push_front(path, point);
		return (1);
	}
	return (0);
}

/**
 * init_visited - Allocates and initializes visited array
 *
 * @rows: Number of rows
 * @cols: Number of columns
 *
 * Return: Pointer to visited array, or NULL on failure
 */
static int **init_visited(int rows, int cols)
{
	int **visited;
	int i, j;

	visited = malloc(sizeof(int *) * rows);
	if (!visited)
		return (NULL);
	for (i = 0; i < rows; i++)
	{
		visited[i] = malloc(sizeof(int) * cols);
		if (!visited[i])
		{
			for (j = 0; j < i; j++)
				free(visited[j]);
			free(visited);
			return (NULL);
		}
		for (j = 0; j < cols; j++)
			visited[i][j] = 0;
	}
	return (visited);
}

/**
 * backtracking_array - Searches for first path in a 2D array
 *
 * @map: Read-only 2D array (0=walkable, 1=blocked)
 * @rows: Number of rows
 * @cols: Number of columns
 * @start: Starting point
 * @target: Target point
 *
 * Return: Queue containing path points, or NULL if no path found
 */
queue_t *backtracking_array(char **map, int rows, int cols,
	point_t const *start, point_t const *target)
{
	queue_t *path;
	int **visited;
	int i;

	visited = init_visited(rows, cols);
	if (!visited)
		return (NULL);
	path = queue_create();
	if (!path)
	{
		for (i = 0; i < rows; i++)
			free(visited[i]);
		free(visited);
		return (NULL);
	}
	if (!backtrack(map, visited, rows, cols,
		start->x, start->y, target, path))
	{
		queue_delete(path);
		path = NULL;
	}
	for (i = 0; i < rows; i++)
		free(visited[i]);
	free(visited);
	return (path);
}
