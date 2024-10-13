#include "graph.h"

// create graph, add vertex, create connections, find potential connections and recommend to users,
//  remove edges, free vertex and free graph
/**
 * create_network - create a new network as graph
 * Return: pointer to new network on success else NULL
 */
graph_t *create_network(void)
{
    graph_t *new_network = (graph_t *)malloc(sizeof(graph_t));
    if (!new_network)
        return NULL;
    new_network->head = NULL;
    new_network->nb_vertices = 0;
    return new_network;
}

/**
 * add_member - add a new member to network
 * @network: graph to add member to
 * @name: member name
 * Return: new member on success else NULL
 */
vertex_t *add_member(graph_t *network, char *name)
{
    if (!network || !name)
        return NULL;
    vertex_t *new_member = (vertex_t *)malloc(sizeof(vertex_t));
    if (!new_member)
        return NULL;
    new_member->name = strdup(name);
    if (!new_member->name)
    {
        free(new_member);
        return NULL;
    }
    new_member->first = NULL;
    new_member->nb_edges = 0;
    new_member->next = NULL;
    new_member->index = network->nb_vertices++;
    if (!network->head)
        network->head = new_member;
    else
    {
        vertex_t *current;
        for (current = network->head; current->next; current = current->next)
            ;
        current->next = new_member;
    }
    return new_member;
}