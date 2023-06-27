#include <stdio.h>
#include <stdlib.h>
#include "deque.h"
#include "types.h"

#define CHUNK_SIZE 10

struct Deque {
    void*** chunks;
    int front_chunk;
    int front_index;
    int rear_chunk;
    int rear_index;
};


Deque* deque_create() {
    Deque* deque = (Deque*)malloc(sizeof(Deque));
    deque->chunks = malloc(sizeof(void**));
    deque->chunks[0] = malloc(sizeof(void*) * CHUNK_SIZE);
    deque->front_chunk = 0;
    deque->front_index = CHUNK_SIZE - 1;
    deque->rear_chunk = 0;
    deque->rear_index = 0;
    return deque;
}

void deque_destroy(Deque* deque) {
    free(deque->chunks[0]);
    free(deque->chunks);
    free(deque);
}

void deque_push_front(Deque* deque, void* value) {
    if (deque->front_index == CHUNK_SIZE - 1) {
        deque->front_index = 0;
        deque->front_chunk++;
        if (deque->front_chunk >= deque->rear_chunk && deque->front_chunk > 0) {
            void*** new_chunks = (void***)realloc(deque->chunks, sizeof(void**) * (deque->rear_chunk + 2));
            if (new_chunks == NULL) {
                printf("deque_push_front: Erro de alocação de memória.\n");
                return;
            }
            deque->chunks = new_chunks;
            deque->chunks[deque->rear_chunk + 1] = (void**)malloc(sizeof(void*) * CHUNK_SIZE);
            deque->rear_chunk++;
        }
    } else {
        deque->front_index++;
    }
    deque->chunks[deque->front_chunk][deque->front_index] = value;
}

void deque_push_back(Deque* deque, void* value) {
    if (deque->rear_index == 0) {
        if (deque->rear_chunk > deque->front_chunk) {
            deque->rear_chunk--;
            deque->rear_index = CHUNK_SIZE - 1;
        } else {
            void*** new_chunks = (void***)realloc(deque->chunks, sizeof(void**) * (deque->rear_chunk + 2));
            if (new_chunks == NULL) {
                printf("Erro de alocação de memória.\n");
                return;
            }
            deque->chunks = new_chunks;
            deque->chunks[deque->rear_chunk + 1] = (void**)malloc(sizeof(void*) * CHUNK_SIZE);
            deque->rear_chunk++;
            deque->rear_index = CHUNK_SIZE - 1;
        }
    } else {
        deque->rear_index--;
    }
    deque->chunks[deque->rear_chunk][deque->rear_index] = value;
}

void* deque_pop_front(Deque* deque) {
    void* value = deque->chunks[deque->front_chunk][deque->front_index];
    if (deque->front_index == 0) {
        if (deque->front_chunk > deque->rear_chunk) {
            deque->front_chunk--;
            deque->front_index = CHUNK_SIZE - 1;
        } else {
            free(deque->chunks[0]);
            for (int i = 0; i < deque->rear_chunk; i++) {
                deque->chunks[i] = deque->chunks[i + 1];
            }
            deque->rear_chunk--;
            deque->front_index = CHUNK_SIZE - 1;
        }
    } else {
        deque->front_index--;
    }
    return value;
}

void* deque_pop_back(Deque* deque) {
    void* value = deque->chunks[deque->rear_chunk][deque->rear_index];
    if (deque->rear_index == CHUNK_SIZE - 1) {
        if (deque->rear_chunk < deque->front_chunk) {
            deque->rear_chunk++;
            deque->rear_index = 0;
        } else {
            free(deque->chunks[deque->rear_chunk]);
            deque->rear_chunk--;
            deque->rear_index = 0;
        }
    } else {
        deque->rear_index++;
    }
    return value;
}

// int deque_size(Deque *d) {
//     return d.
// }
