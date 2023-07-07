
#include "queue.h"
#include <stdlib.h>
#include <stdio.h>

struct Queue {
    void **data;
    int size;
    int capacity;
    int front;
    int rear;
};

Queue *queue_construct() {
    Queue *queue = malloc(sizeof(Queue));
    queue->data = malloc(sizeof(void *) * 10);
    queue->size = 0;
    queue->capacity = 10;
    queue->front = 0;
    queue->rear = 0;
    return queue;
}

void queue_push(Queue *queue, void *data) {
    if (queue->size == queue->capacity) {
        queue->data = realloc(queue->data, sizeof(void *) * queue->capacity * 2);
        queue->capacity *= 2;
    }
    queue->data[queue->rear] = data;
    queue->rear = (queue->rear + 1) % queue->capacity;
    queue->size++;
}

bool queue_empty(Queue *queue) {
    return queue->size == 0;
}

void *queue_pop(Queue *queue) {
    void *data = queue->data[queue->front];
    queue->front = (queue->front + 1) % queue->capacity;
    queue->size--;
    return data;
}

void queue_destroy(Queue *queue) {
    free(queue->data);
    free(queue);
}

void queue_show(Queue *queue, void (*print_fn)(void *)) {
    printf("[");
    for(int i = 0; i < queue->size; i++) {
        print_fn(queue->data[(queue->front + i) % queue->capacity]);
        if (i < queue->size - 1)
            printf(", ");
    }
    printf("]\n");
}
