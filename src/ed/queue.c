
#include "queue.h"
#include <stdlib.h>
#include <stdio.h>

struct Queue {
    Deque *deque;
};

Queue *queue_construct() {
    Queue *queue = malloc(sizeof(Queue));
    queue->deque = deque_create();
    return queue;
}

void queue_push(Queue *queue, void *data) {
    deque_push_back(queue->deque, data);
}

bool queue_empty(Queue *queue) {
    return deque_size(queue->deque) == 0;
}

void *queue_pop(Queue *queue) {
    return deque_pop_front(queue->deque);
}

void queue_destroy(Queue *queue) {
    deque_destroy(queue->deque);
    free(queue);
}

void queue_show(Queue *queue, void (*print_fn)(void *)) {
    printf("[");
    for(int i = 0; i < deque_size(queue->deque); i++) {
        print_fn(deque_get(queue->deque, i));
        if(i != deque_size(queue->deque) - 1) {
            printf(", ");
        }
    }
    printf("]\n");
}
