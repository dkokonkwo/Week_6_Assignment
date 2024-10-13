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

/**
 * create_connection - adds edges between two members
 * @network: network to create connection in
 * @src: name of source member
 * @dest: name of destination member
 * Return: 1 on success, 0 on error
 */
int create_connection(graph_t *network, char *src, char *dest)
{
    vertex_t *curr, *src_v, *dest_v;
    edge_t *src_e, *dest_e, *curr_edge;
    if (!network || !src || !dest)
        return 0;
    for (curr = network->head; curr; curr = curr->next)
    {
        if (strcasecmp(curr->name, src) == 0)
            src_v = curr;
        if (strcasecmp(curr->name, dest) == 0)
            dest_v = curr;
        if (src_v && dest_v)
            break;
    }
    if (!(src_v && dest_v))
        return 0;
    src_e = (edge_t *)malloc(sizeof(edge_t));
    if (!src_e)
        return 0;
    src_e->dest = dest_v, src_e->next = NULL;
    if (!src_v->first)
        src_v->first = src_e;
    else
    {
        for (curr_edge = src_v->first; curr_edge->next; curr_edge = curr_edge->next)
        {
            ;
        }
        curr_edge->next = src_e;
    }
    src_v->nb_edges++;
    dest_e = (edge_t *)malloc(sizeof(edge_t));
    if (!dest_e)
        return 0;
    dest_e->dest = src_v, dest_e->next = NULL;
    if (!dest_v->first)
        dest_v->first = dest_e;
    else
    {
        for (curr_edge = dest_v->first; curr_edge->next; curr_edge = curr_edge->next)
        {
            ;
        }
        curr_edge->next = dest_e;
    }
    dest_v->nb_edges++;
    return 1;
}