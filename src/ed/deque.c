#include "deque.h"

#define INITIAL_MAP_SIZE 5
#define CHUNK_SIZE 5


struct Deque {
    void*** chunks;
    int front_block;
    int front_index;
    int rear_block;
    int rear_index;
    int size;
};


// criacao do deque
Deque *deque_construct(void) {
    Deque* deque = malloc(sizeof(Deque));

    deque->chunks = malloc(sizeof(void**) * INITIAL_MAP_SIZE);
    deque->chunks[0] = malloc(sizeof(void*) * CHUNK_SIZE);
    deque->front_block = INITIAL_MAP_SIZE/2 + 1;
    deque->rear_block = INITIAL_MAP_SIZE/2 + 1;
    deque->front_index = 0;
    deque->rear_index = 0;
    deque->size = 0;

    return deque;
}

// funcoes para insercao na direita e esquerda (devem ser feitas em O(1), com eventual realloc)
void deque_push_back(Deque *d, void *val) {

}
void deque_push_front(Deque *d, void *val);

// funcoes para remocao na direita e esquerda (devem ser feitas em O(1))
void *deque_pop_back(Deque *d);
void *deque_pop_front(Deque *d);

// numero de elementos
int deque_size(Deque *d) {
    return d->size;
}

// obtem o i-esimo elemento
void *deque_get(Deque *d, int idx);

// libera o espaco alocado para o deque
void deque_destroy(Deque *d);
