#include "deque.h"
#include <stdlib.h>
#include <stdio.h>
#define INITIAL_SIZE_MAP 5
#define INITIAL_SIZE_CHUNCK 5


struct Deque {
    void*** data;
    int size;
    int map_size;
    int front_idx;
    int back_idx;
    int front_map_idx;
    int back_map_idx;
};


Deque *deque_create(void) {
    Deque* d = malloc(sizeof(Deque));
    d->data = malloc(sizeof(void**) * INITIAL_SIZE_MAP);
    d->size = 0;
    d->map_size = INITIAL_SIZE_MAP;
    d->front_idx = 0;
    d->back_idx = 0;
    int initial_idx = INITIAL_SIZE_MAP / 2 + 1;
    d->front_map_idx = initial_idx;
    d->back_map_idx = initial_idx;
    for (int i = 0; i < INITIAL_SIZE_MAP; i++) {
        d->data[i] = NULL;
    }
    d->data[initial_idx] = malloc(sizeof(void*) * INITIAL_SIZE_CHUNCK);
    return d;
}

void deque_push_back(Deque *d, void *val) {
    if (d->back_idx == INITIAL_SIZE_CHUNCK) {
        d->back_idx = 0;
        d->back_map_idx++;
        if (d->back_map_idx == d->map_size) {
            int new_map_size = d->map_size * 2;
            void*** new_data = malloc(sizeof(void**) * new_map_size);
            for (int i = 0; i < new_map_size; i++) {
                new_data[i] = NULL;
            }
            int initial_idx = new_map_size / 4;
            for (int i = 0, j = d->front_map_idx; i < d->map_size; i++, j++) {
                new_data[initial_idx + i] = d->data[j];
            }
            d->front_map_idx = initial_idx;
            d->back_map_idx = initial_idx + d->map_size;
            d->map_size = new_map_size;
            free(d->data);
            d->data = new_data;
        }
        d->data[d->back_map_idx] = malloc(sizeof(void*) * INITIAL_SIZE_CHUNCK);
    }
    d->data[d->back_map_idx][d->back_idx] = val;
    d->back_idx++;
    d->size++;
}

void deque_push_front(Deque *d, void *val) {
    if (d->front_idx == 0) {
        d->front_idx = INITIAL_SIZE_CHUNCK;
        d->front_map_idx--;
        if (d->front_map_idx == -1) {
            int new_map_size = d->map_size * 2;
            void*** new_data = malloc(sizeof(void**) * new_map_size);
            for (int i = 0; i < new_map_size; i++) {
                new_data[i] = NULL;
            }
            int initial_idx = new_map_size / 4;
            for (int i = 0, j = d->front_map_idx; i < d->map_size; i++, j++) {
                new_data[initial_idx + i] = d->data[j];
            }
            d->front_map_idx = initial_idx;
            d->back_map_idx = initial_idx + d->map_size;
            d->map_size = new_map_size;
            free(d->data);
            d->data = new_data;
        }
        d->data[d->front_map_idx] = malloc(sizeof(void*) * INITIAL_SIZE_CHUNCK);
    }
    d->front_idx--;
    d->data[d->front_map_idx][d->front_idx] = val;
    d->size++;
}

void* deque_pop_back(Deque *d) {
    if (d->back_idx == 0) {
        d->back_map_idx--;
        d->back_idx = INITIAL_SIZE_CHUNCK;
    }
    d->back_idx--;
    void* val = d->data[d->back_map_idx][d->back_idx];
    d->data[d->back_map_idx][d->back_idx] = NULL;
    d->size--;
    return val;
}

void *deque_pop_front(Deque *d) {
    void* val = d->data[d->front_map_idx][d->front_idx];
    d->data[d->front_map_idx][d->front_idx] = NULL;
    d->front_idx++;
    if (d->front_idx == INITIAL_SIZE_CHUNCK) {
        d->front_idx = 0;
        d->front_map_idx++;
    }
    d->size--;
    return val;
}

int deque_size(Deque *d) {
    return d->size;
}

void *deque_get(Deque *d, int idx) {
    int map_idx = d->front_map_idx + idx / INITIAL_SIZE_CHUNCK;
    int chunck_idx = idx % INITIAL_SIZE_CHUNCK;
    return d->data[map_idx][chunck_idx];
}

void deque_destroy(Deque *d) {
    for (int i = 0; i < d->map_size; i++) {
        if (d->data[i] != NULL) {
            free(d->data[i]);
        }
    }
    free(d->data);
    free(d);
}

void print_deque(Deque* deque, void (*print)(void*)) {
    printf("[");

    for (int i = 0; i < deque->map_size; i++) {
        if (deque->data[i] != NULL) {
            for (int j = 0; j < INITIAL_SIZE_CHUNCK; j++) {
                if (deque->data[i][j] != NULL) {
                    print(deque->data[i][j]);
                    printf(", ");
                }
            }
        }
    }
    printf("]\n");
}
