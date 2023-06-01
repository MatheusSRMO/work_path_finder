#include "deque_2D_dynamic.h"

struct deque_2D_dynamic {
    int front;
    int rear;
    int num_rows;
    int num_columns;
    Deque_1D_dynamic *rows;
};

Deque_2D_dynamic deque_2D_construct(int num_rows, int num_columns) {
    Deque_2D_dynamic deque = malloc(sizeof(struct deque_2D_dynamic));
    deque->front = 0;
    deque->rear = 0;
    deque->rows = num_rows;
    deque->num_columns = num_columns;
    deque->rows = malloc(sizeof(Deque_1D_dynamic) * num_rows);
    for (int i = 0; i < num_rows; i++) {
        deque->rows[i] = deque_1D_construct(num_columns);
    }
    return deque;
}

void deque_2D_push_back(Deque_2D_dynamic deque, NodePtr item) {
    deque_1D_push_back(deque->rows[deque->rear], item);
    deque->rear = (deque->rear + 1) % deque->num_rows;
}

void deque_2D_push_front(Deque_2D_dynamic deque, NodePtr item) {
    deque_1D_push_front(deque->rows[deque->front], item);
    deque->front = (deque->front - 1 + deque->num_rows) % deque->num_rows;
}

NodePtr deque_2D_pop_back(Deque_2D_dynamic deque) {
    NodePtr excluded = deque_1D_pop_back(deque->rows[deque->rear]);
    deque->rear = (deque->rear - 1 + deque->num_rows) % deque->num_rows;
    return excluded;
}

NodePtr deque_2D_pop_front(Deque_2D_dynamic deque) {
    NodePtr excluded = deque_1D_pop_front(deque->rows[deque->front]);
    deque->front = (deque->front + 1) % deque->num_rows;
    return excluded;
}

void deque_2D_show(Deque_2D_dynamic deque) {
    for (int i = 0; i < deque->num_rows; i++) {
        deque_1D_print(deque->rows[i]);
    }
}

void deque_2D_destruct(Deque_2D_dynamic deque) {
    for (int i = 0; i < deque->num_rows; i++) {
        deque_1D_destruct(deque->rows[i]);
    }
    free(deque->rows);
    free(deque);
}
