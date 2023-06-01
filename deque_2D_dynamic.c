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