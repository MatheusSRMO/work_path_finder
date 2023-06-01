#include "deque_1D_dynamic.h"


struct deque_1D_dynamic {
    NodePtr *items;
    int size;
    int capacity;
    int front;
    int rear;
};


Deque_1D_dynamic deque_1D_construct(int capacity) {
    Deque_1D_dynamic deque = malloc(sizeof(struct deque_1D_dynamic));
    deque->items = malloc(capacity * sizeof(NodePtr));
    deque->size = 0;
    deque->capacity = capacity;
    deque->front = 0;
    deque->rear = 0;
    return deque;
}

void deque_1D_push_back(Deque_1D_dynamic deque, NodePtr item) {
    if (deque->size == deque->capacity) {
        int new_capacity = deque->capacity * 2;
        NodePtr* new_items = malloc(new_capacity * sizeof(NodePtr));

        int i = deque->front;
        int j = 0;
        while (j < deque->size) {
            new_items[i] = deque->items[j];
            i = (i + 1) % deque->capacity;
            j++;
        }

        deque->front = 0;
        deque->rear = deque->size;

        free(deque->items);
        deque->items = new_items;
        deque->capacity = new_capacity;
    }

    deque->items[deque->rear] = item;
    deque->rear = (deque->rear + 1) % deque->capacity;
    deque->size++;
}


NodePtr deque_1D_pop_back(Deque_1D_dynamic deque) {
    if (deque->size > 0) {
        int last_index = (deque->rear - 1 + deque->capacity) % deque->capacity;

        NodePtr excluded = deque->items[last_index];

        deque->rear = last_index;
        deque->size--;
        return excluded;
    }
    return NULL;
}


void deque_1D_push_front(Deque_1D_dynamic deque, NodePtr item) {
    if (deque->size == deque->capacity) {
        int new_capacity = deque->capacity * 2;
        NodePtr* new_items = malloc(new_capacity * sizeof(NodePtr));

        int new_front = (deque->front - 1 + new_capacity) % new_capacity;

        int i = deque->front;
        int j = 0;
        while (j < deque->size) {
            new_items[(j + 1) % new_capacity] = deque->items[i];
            i = (i + 1) % deque->capacity;
            j++;
        }
        
        deque->front = new_front;
        deque->rear = (deque->rear + 1) % new_capacity;
        deque->capacity = new_capacity;

        free(deque->items);
        deque->items = new_items;
    }

    deque->front = (deque->front - 1 + deque->capacity) % deque->capacity;

    deque->items[deque->front] = item;
    deque->size++;
}


NodePtr deque_1D_pop_front(Deque_1D_dynamic deque) {
    if (deque->size > 0) {
        NodePtr excluded = deque->items[deque->front];

        deque->front = (deque->front + 1) % deque->capacity;
        deque->size--;
        return excluded;
    }
    return NULL;
}


void deque_1D_print(Deque_1D_dynamic deque) {
    int i = deque->front;
    int j = 0;
    while (j < deque->size) {
        node_show(deque->items[i]);
        printf("\n");
        i = (i + 1) % deque->capacity;
        j++;
    }
    printf("\n");
}


void deque_1D_destruct(Deque_1D_dynamic deque) {
    int i = deque->front;
    int j = 0;
    while (j < deque->size) {
        node_destroy(deque->items[i]);
        i = (i + 1) % deque->capacity;
        j++;
    }
    free(deque->items);
    free(deque);
}
