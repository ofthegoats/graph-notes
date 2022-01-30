#ifndef LINKED_LIST_H_
#define LINKED_LIST_H_

struct linked_list {
    struct node* head;
};

struct node {
    void* val;
    struct node* next;
};

void append(struct linked_list*, void*);
void remove(struct linked_list*, void*);
struct node* search(struct linked_list*, void*);

#endif // LINKED_LIST_H_
