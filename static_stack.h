#ifndef STATIC_STACK_H_
#define STATIC_STACK_H_

#ifndef STATIC_STACK_SIZE
#define STATIC_STACK_SIZE 20
#endif

struct s_stack {
    unsigned int top;
    unsigned int current;
    void* stack[STATIC_STACK_SIZE];
};

void push(struct s_stack*, void*);
void* pop(struct s_stack*);

#endif // STATIC_STACK_H_
