#ifndef GRAPH_H_
#define GRAPH_H_

#include "./linked_list.h"

/* An adjacency list is just a linked list where
 * each value is a pointer to another linked list */
typedef struct linked_list graph;

void add_node(graph*, void*);
void remove_node(graph*, void*);
void add_edge(graph*, void*, void*);
void remove_edge(graph*, void*, void*);

struct linked_list* find_node(graph*, void*);

#endif // GRAPH_H_
