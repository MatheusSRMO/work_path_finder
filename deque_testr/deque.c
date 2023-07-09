#include "deque.h"
#include <stdio.h>
#include <stdlib.h>

#define INITIAL_MAP_SIZE 5
#define BUFFER_SIZE 5

typedef void* data_type;

struct Deque {
    data_type** buffer;
    int front_idx;
    int back_idx;
    int front_map_idx;
    int back_map_idx;
    int map_size;
};

Deque* deque_create(void) {
    Deque* deque = malloc(sizeof(Deque));
    deque->buffer = malloc(sizeof(data_type*) * INITIAL_MAP_SIZE);
    for (int i = 0; i < INITIAL_MAP_SIZE; i++) {
        deque->buffer[i] = NULL;
    }
    deque->front_idx = 0;
    deque->back_idx = 0;
    deque->map_size = INITIAL_MAP_SIZE;
    deque->front_map_idx = INITIAL_MAP_SIZE / 2;
    deque->back_map_idx = INITIAL_MAP_SIZE / 2;
    return deque;
}

void deque_push_back(Deque* d, void* val) {
    if (d->buffer[d->back_map_idx] == NULL) {
        d->buffer[d->back_map_idx] = __deque_alloc_bucket();
    }

    d->buffer[d->back_map_idx][d->back_idx] = val;
    d->back_idx++;

    if (d->back_idx == BUFFER_SIZE) {
        d->back_idx = 0;
        d->back_map_idx++;

        if (d->back_map_idx == d->map_size) {
            // realocar buffer
            __deque_realoc_map(d, d->map_size * 2);
        }
    }
}

void deque_push_front(Deque* d, void* val) {
    d->front_idx--;

    if (d->front_idx < 0) {
        d->front_idx = BUFFER_SIZE - 1;
        d->front_map_idx--;

        if (d->front_map_idx < 0) {
            __deque_realoc_map(d, d->map_size * 2);
        }
    }
    if (d->buffer[d->front_map_idx] == NULL) {
        d->buffer[d->front_map_idx] = __deque_alloc_bucket();
    }
    d->buffer[d->front_map_idx][d->front_idx] = val;
}

int deque_size(Deque* d) {
    return (d->back_map_idx - d->front_map_idx) * BUFFER_SIZE + d->back_idx - d->front_idx;
}

void* deque_get(Deque* d, int idx) {
    int map_idx = idx / BUFFER_SIZE + d->front_map_idx;
    int buffer_idx = idx % BUFFER_SIZE + d->front_idx;
    return d->buffer[map_idx][buffer_idx];
}

void print_infos_deque(Deque* d) {
    printf("front_idx: %d\n", d->front_idx);
    printf("front_map_idx: %d\n", d->front_map_idx);
    printf("back_idx: %d\n", d->back_idx);
    printf("back_map_idx: %d\n", d->back_map_idx);
    printf("map_size: %d\n", d->map_size);
    printf("size: %d\n", deque_size(d));
    printf("\n");
}

void* deque_pop_back(Deque* d) {
    d->back_idx--;
    if (d->back_idx < 0) {
        d->back_map_idx--;
        d->back_idx = BUFFER_SIZE - 1;
    }
    void* val = d->buffer[d->back_map_idx][d->back_idx];
    d->buffer[d->back_map_idx][d->back_idx] = NULL;
    return val;
}

void* deque_pop_front(Deque* d) {
    void* val = d->buffer[d->front_map_idx][d->front_idx];
    d->buffer[d->front_map_idx][d->front_idx] = NULL;
    d->front_idx++;
    if (d->front_idx == BUFFER_SIZE) {
        d->front_map_idx++;
        d->front_idx = 0;
    }
    return val;
}

void print_deque(Deque* deque, void (*print)(void*)) {
    printf("[\n");
    for (int i = 0; i < deque->map_size; i++) {
        printf("\t%2d [", i);
        for (int j = 0; j < BUFFER_SIZE; j++) {
            if (deque->buffer[i] != NULL && deque->buffer[i][j] != NULL) {
                print(deque->buffer[i][j]);
            } else {
                printf("NULL");
            }
            if (j != BUFFER_SIZE - 1)
                printf(", ");
        }
        printf("]\n");
    }
    printf("]\n");
}

void deque_destroy(Deque* d) {
    for (int i = 0; i < d->map_size; i++)
        if (d->buffer[i] != NULL)
            free(d->buffer[i]);

    free(d->buffer);
    free(d);
}

int f(int tam, int front_map_idx, int back_map_idx) {
    int delta = (tam - abs(front_map_idx - back_map_idx)) / 2;
    return delta;
}

// Centraliza os elementos do deque no meio do buffer
// Centralizes the elements of the deque in the middle of the buffer
void __deque_centralize_map(Deque* d) {
    int tam = d->map_size;
    int front_map_idx = d->front_map_idx;
    int back_map_idx = d->back_map_idx;

    int delta = f(tam, front_map_idx, back_map_idx);
    
    data_type** new_buffer = calloc(tam, sizeof(data_type*));

    int new_front_map_idx = delta;

    for (int i = front_map_idx; i < back_map_idx; i++) {
        new_buffer[new_front_map_idx] = d->buffer[i];
        d->buffer[i] = NULL;
        new_front_map_idx++;
    }
    for(int i = 0; i < front_map_idx; i++) {
        if(d->buffer[i] != NULL)
        __deque_free_bucket(d->buffer[i]);
    }

    free(d->buffer);
    d->buffer = new_buffer;
    d->map_size = tam;
    d->front_map_idx = delta;
    d->back_map_idx = new_front_map_idx;    
}

void __deque_realoc_map(Deque* d, int new_map_size) {
    // Check if it is necessary to increase the size of the buffer (if the deque is 75% full)
    if (deque_size(d) >= (d->map_size * BUFFER_SIZE) * 0.75) {
        // Increase the size of the buffer
        data_type** new_buffer = realloc(d->buffer, sizeof(data_type*) * new_map_size);

        // If the reallocation fails, handle the error
        if (new_buffer == NULL) {
            fprintf(stderr, "Failed to reallocate buffer\n");
            return;
        }

        // Update the deque's buffer and map size
        d->buffer = new_buffer;
        d->map_size = new_map_size;

        // Centralize the elements
        __deque_centralize_map(d);
    } else {
        // Case it's not necessary, just centralize the elements
        __deque_centralize_map(d);
    }
}


data_type* __deque_alloc_bucket() {
    data_type* bucket = malloc(sizeof(data_type) * BUFFER_SIZE);
    for (int i = 0; i < BUFFER_SIZE; i++) {
        bucket[i] = NULL;
    }
    return bucket;
}
void __deque_free_bucket(data_type* bucket) {
    free(bucket);
}
