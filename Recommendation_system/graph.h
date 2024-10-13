#ifndef GRAPH_H
#define GRAPH_H

#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef struct vertex_s vertex_t;

/**
 * struct edge_t - edge connecting a node
 * @dest: pointer to the connected vertex
 * @next: pointer to next edge
 */
typedef struct edge_s
{
    vertex_t *dest;
    struct edge_s *next;
} edge_t;

/**
 * struct vertex_t - vertex in graph
 * @index: index of vertex in adjacency list
 * @name: connection name
 * @nb_edges: number of connections
 * @first: pointer to first connection
 * @next: pointer to the next vertex in adjacency list
 */
typedef struct vertex_s
{
    size_t index;
    char *name;
    size_t nb_edges;
    edge_t *first;
    struct vertex_t *next;
} vertex_t;

/**
 * struct graph_s - representation of a social network as a graph
 * @nb_vertices: number of vertices in social network
 * @head: first vertex in adjacency linked list
 */
typedef struct graph_s
{
    size_t *nb_vertices;
    vertex_t *head;
} graph_t;

#endif