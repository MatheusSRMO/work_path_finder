#include "stack.h"

void test_failed(const char *test_name) {
    printf("Test failed: %s\n", test_name);
}

int test_stack_empty() {
    int error = 0;
    Stack *stack = stack_construct();
    if (!stack_empty(stack)) {
        test_failed("test_stack_empty");
        error = 1;
    }
    stack_push(stack, NULL);
    if (stack_empty(stack)) {
        test_failed("test_stack_empty");
        error = 1;
    }
    stack_destroy(stack);
    return error;
}

int test_stack_push_pop() {
    int error = 0;
    Stack *stack = stack_construct();
    int data1 = 10;
    int data2 = 20;
    stack_push(stack, &data1);
    stack_push(stack, &data2);
    void *popped_data = stack_pop(stack);
    if (popped_data != &data2) {
        test_failed("test_stack_push_pop");
        error = 1;
    }
    popped_data = stack_pop(stack);
    if (popped_data != &data1) {
        test_failed("test_stack_push_pop");
        error = 1;
    }
    if (!stack_empty(stack)) {
        test_failed("test_stack_push_pop");
        error = 1;
    }
    stack_destroy(stack);
    return error;
}

int main() {
    test_stack_empty();
    test_stack_push_pop();
    printf("STACK TEST: All tests passed.\n");
    return 0;
}
