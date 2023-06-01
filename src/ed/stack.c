#include "stack.h"

struct Stack {
    int top;
    int capacity;
    void ** array;
};

Stack *stack_construct() {
    Stack *stack = malloc(sizeof(Stack));
    stack->capacity = 1;
    stack->top = -1;
    stack->array = malloc(stack->capacity * sizeof(void *));
    return stack;
}

void stack_push(Stack *stack, void *data) {
    if (stack->top == stack->capacity - 1) {
        stack->capacity *= 2;
        stack->array = realloc(stack->array, stack->capacity * sizeof(void *));
    }
    stack->array[++stack->top] = data;
}

bool stack_empty(Stack *stack) {
    return stack->top == -1;
}

void *stack_pop(Stack *stack) {
    if (stack_empty(stack)) {
        return NULL;
    }
    return stack->array[stack->top--];
}

void stack_destroy(Stack *stack) {
    free(stack->array);
    free(stack);
}
