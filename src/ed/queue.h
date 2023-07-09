
#ifndef _QUEUE_H_
#define _QUEUE_H_

#include <stdbool.h>
#include "types.h"
#include "deque.h"

typedef struct Queue Queue;

Queue *queue_construct();
void queue_push(Queue *queue, void *data);
bool queue_empty(Queue *queue);
void *queue_pop(Queue *queue);
void queue_destroy(Queue *queue);

void queue_show(Queue *queue, void (*print_fn)(void *));

#endif