#include "linked_list.h"

#include <stdlib.h>

struct node* append(struct linked_list* ll, void* val)
{
    // allocate memory for the new element in the list
    struct node* n;
    n = (struct node*)malloc(sizeof(struct node));
    n->val = val;
    // append at head
    n->next = ll->head;
    ll->head = n;
    return n;
}

void pop(struct linked_list* ll, void* val)
{
    struct node* from;
    struct node* current;
    if (ll->head == NULL) {
        // ll is empty, do nothing
    } else if (ll->head->val == val) { // removing head
        current = ll->head->next;
        free(ll->head);
        ll->head = current;
    } else { // list has at least one element, not removing head
        from = ll->head;
        current = ll->head->next;
        // move pointers until element is found, or end of list is reached
        while (current != NULL && current->val != val) {
            from = from->next;
            current = current->next;
        }
        if (current != NULL) {
            from->next = current->next;
            free(current);
        }
    }
}

struct node* search(struct linked_list* ll, void* val)
{
    struct node* current = ll->head;
    while (current) {
        if (current->val == val) return current;
        current = current->next;
    }
    return NULL;
}
