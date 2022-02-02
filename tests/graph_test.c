#include "../graph.h"

#include <assert.h>
#include <stdio.h>

void find_node_test();
void add_node_test();
void remove_node_test();
void add_edge_test();
void remove_edge_test();
void print_graph();

int main(int argc, char* argv[])
{
    find_node_test();
    add_node_test();
    remove_node_test();
    add_edge_test();
    remove_edge_test();
    return 0;
}

void print_graph(graph* g)
{
    struct node* v = g->head;
    struct linked_list* neighbours;
    struct node* u;
    while (v) {
        neighbours = v->val;
        u = neighbours->head;
        printf("%p: ", u->val);
        u = u->next;
        while (u) {
            printf("%p, ", u->val);
            u = u->next;
        }
        printf("\n");
        v = v->next;
    }
}

void find_node_test()
{
    printf("%s: ", __FUNCTION__);
    graph g = {NULL};
    add_node(&g, (void*)1);
    add_node(&g, (void*)2);
    add_node(&g, (void*)3);
    add_node(&g, (void*)4);
    assert(find_node(&g, (void*)1)->head->val == (void*)1);
    assert(find_node(&g, (void*)2)->head->val == (void*)2);
    assert(find_node(&g, (void*)3)->head->val == (void*)3);
    assert(find_node(&g, (void*)4)->head->val == (void*)4);
    assert(!find_node(&g, (void*)5));
    printf("PASSED\n");
}

void add_node_test()
{
    printf("%s: ", __FUNCTION__);
    graph g = {NULL};
    add_node(&g, (void*)1);
    add_node(&g, (void*)2);
    add_node(&g, (void*)3);
    add_node(&g, (void*)4);
    assert(find_node(&g, (void*)1)->head->val == (void*)1);
    assert(find_node(&g, (void*)2)->head->val == (void*)2);
    assert(find_node(&g, (void*)3)->head->val == (void*)3);
    assert(find_node(&g, (void*)4)->head->val == (void*)4);
    assert(!find_node(&g, (void*)5));
    print_graph(&g);
    printf("PASSED\n");
}

void remove_node_test()
{
    printf("%s: ", __FUNCTION__);
    graph g = {NULL};
    add_node(&g, (void*)1);
    add_node(&g, (void*)2);
    add_node(&g, (void*)3);
    add_node(&g, (void*)4);
    add_node(&g, (void*)5);
    remove_node(&g, (void*)1);
    assert(!find_node(&g, (void*)1));
    assert(find_node(&g, (void*)2)->head->val == (void*)2);
    assert(find_node(&g, (void*)3)->head->val == (void*)3);
    assert(find_node(&g, (void*)4)->head->val == (void*)4);
    assert(find_node(&g, (void*)5)->head->val == (void*)5);
    remove_node(&g, (void*)5);
    assert(!find_node(&g, (void*)1));
    assert(find_node(&g, (void*)2)->head->val == (void*)2);
    assert(find_node(&g, (void*)3)->head->val == (void*)3);
    assert(find_node(&g, (void*)4)->head->val == (void*)4);
    assert(!find_node(&g, (void*)5));
    remove_node(&g, (void*)3);
    assert(!find_node(&g, (void*)1));
    assert(find_node(&g, (void*)2)->head->val == (void*)2);
    assert(!find_node(&g, (void*)3));
    assert(find_node(&g, (void*)4)->head->val == (void*)4);
    assert(!find_node(&g, (void*)5));
    printf("PASSED\n");
}

void add_edge_test()
{
    printf("%s: ", __FUNCTION__);
    graph g = {NULL};
    add_node(&g, (void*)1);
    add_node(&g, (void*)2);
    add_node(&g, (void*)3);
    add_node(&g, (void*)4);
    add_edge(&g, (void*)1, (void*)4);
    assert(find_node(&g, (void*)1)->head->next->val == (void*)4);
    add_edge(&g, (void*)1, (void*)3);
    assert(find_node(&g, (void*)1)->head->next->val == (void*)4);
    assert(find_node(&g, (void*)1)->head->next->next->val == (void*)3);
    add_edge(&g, (void*)2, (void*)6); // dest node does not exist
    add_edge(&g, (void*)5, (void*)6); // nodes do not exist
    print_graph(&g);
    printf("PASSED\n");
}

void remove_edge_test()
{
    printf("%s: ", __FUNCTION__);
    graph g = {NULL};
    add_node(&g, (void*)1);
    add_node(&g, (void*)2);
    add_node(&g, (void*)3);
    add_node(&g, (void*)4);
    add_edge(&g, (void*)1, (void*)4);
    add_edge(&g, (void*)1, (void*)3);
    add_edge(&g, (void*)2, (void*)1);
    add_edge(&g, (void*)3, (void*)2);
    remove_edge(&g, (void*)1, (void*)4);
    assert(find_node(&g, (void*)1)->head->next->val == (void*)3);
    remove_edge(&g, (void*)2, (void*)1);
    assert(!find_node(&g, (void*)2)->head->next);
    remove_edge(&g, (void*)4, (void*)3); // edge does not exist
    print_graph(&g);
    printf("PASSED\n");
}
