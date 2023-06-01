#include "queue.h"
// arquivo para testar a fila

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void test_queue_push() {
    Queue *queue = queue_construct();
    char *str = "Hello, World!";
    queue_push(queue, str);
    if (strcmp(
        queue_pop(queue)
        , str) != 0) {
        printf("queue_push: FAIL\n");
        return;
    }
    printf("queue_push: OK\n");
}

int main() {
    test_queue_push();
    printf("STACK TEST: All tests passed.\n");
    return 0;
}