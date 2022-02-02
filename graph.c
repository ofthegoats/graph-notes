#include "graph.h"

#include <stdlib.h>

struct linked_list* find_node(graph* g, void* id)
{
    struct node* current = g->head;
    while (current && ((struct linked_list*)(current->val))->head->val != id) {
        current = current->next;
    }
    return current ? (struct linked_list*)current->val : NULL;
}

void add_node(graph* g, void* id)
{
    struct linked_list* ll;
    struct node* v;
    // node cannot already be present
    if (!find_node(g, id)) {
        ll = (struct linked_list*)malloc(sizeof(struct linked_list));
        v = (struct node*)malloc(sizeof(struct node));
        ll->head = v;
        v->val = id;
        v->next = NULL;
        append(g, ll);
    }
}

void remove_node(graph* g, void* id)
{
    struct linked_list* neighbours;
    struct node* v;
    struct node* tmp;
    neighbours = find_node(g, id);
    v = neighbours->head;
    while (v) {
        tmp = v->next;
        free(v);
        v = tmp;
    }
    // once all neighbours freed
    pop(g, id);
}

void add_edge(graph* g, void* from, void* to)
{
    struct linked_list* neighbours;
    neighbours = find_node(g, from);
    // only add edge if both nodes exist
    if (neighbours && find_node(g, to)) append(neighbours, to);
}

void remove_edge(graph* g, void* from, void* to)
{
    struct linked_list* neighbours;
    neighbours = find_node(g, from);
    // can only remove if source exists
    if (neighbours) pop(neighbours, to);
}
