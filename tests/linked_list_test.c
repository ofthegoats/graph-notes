#include "../linked_list.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

void traverse(struct linked_list* ll);

void traverse_test();
void append_test();
void pop_test();
void search_test();

int main(int argc, char* argv[])
{
    append_test();
    search_test();
    traverse_test();
    pop_test();
    return 0;
}

void traverse(struct linked_list* ll)
{
    struct node* current = ll->head;
    while (current) {
        printf("%p : %p\n", current, current->val);
        current = current->next;
    }
}

void traverse_test()
{
    struct linked_list ll = {NULL};
    append(&ll, (void*)1);
    append(&ll, (void*)2);
    append(&ll, (void*)3);
    append(&ll, (void*)4);
    traverse(&ll);
}

void append_test()
{
    printf("%s: ", __FUNCTION__);
    struct linked_list ll = {NULL};
    append(&ll, (void*)1);
    append(&ll, (void*)2);
    append(&ll, (void*)3);
    append(&ll, (void*)4);
    assert(ll.head->val == (void*)1);
    assert(ll.head->next->val == (void*)2);
    assert(ll.head->next->next->val == (void*)3);
    assert(ll.head->next->next->next->val == (void*)4);
    printf("PASSED\n");
}

void search_test()
{
    printf("%s: ", __FUNCTION__);
    struct linked_list ll = {NULL};
    struct node* one = append(&ll, (void*)1);
    struct node* two = append(&ll, (void*)2);
    struct node* three = append(&ll, (void*)3);
    struct node* four = append(&ll, (void*)4);
    assert(search(&ll, (void*)1) == one);
    assert(search(&ll, (void*)2) == two);
    assert(search(&ll, (void*)3) == three);
    assert(search(&ll, (void*)4) == four);
    assert(search(&ll, (void*)5) == NULL);
    printf("PASSED\n");
}

void pop_test()
{
    printf("%s: ", __FUNCTION__);
    struct linked_list ll = {NULL};
    struct node* one = append(&ll, (void*)1);
    struct node* two = append(&ll, (void*)2);
    struct node* three = append(&ll, (void*)3);
    struct node* four = append(&ll, (void*)4);
    struct node* five = append(&ll, (void*)5);
    struct node* six = append(&ll, (void*)6);
    pop(&ll, (void*)1); // remove from head
    assert(ll.head->val == (void*)2);
    assert(ll.head->next->val == (void*)3);
    assert(ll.head->next->next->val == (void*)4);
    assert(ll.head->next->next->next->val == (void*)5);
    assert(ll.head->next->next->next->next->val == (void*)6);
    pop(&ll, (void*)6); // remove from end
    assert(ll.head->val == (void*)2);
    assert(ll.head->next->val == (void*)3);
    assert(ll.head->next->next->val == (void*)4);
    assert(ll.head->next->next->next->val == (void*)5);
    assert(!ll.head->next->next->next->next);
    pop(&ll, (void*)3); // remove from middle
    assert(ll.head->val == (void*)2);
    assert(ll.head->next->val == (void*)4);
    assert(ll.head->next->next->val == (void*)5);
    pop(&ll, (void*)11); // remove non-existent
    assert(ll.head->val == (void*)2);
    assert(ll.head->next->val == (void*)4);
    assert(ll.head->next->next->val == (void*)5);
    printf("PASSED\n");
}
