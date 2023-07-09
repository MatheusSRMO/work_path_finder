
#ifndef _DEQUE_H_
#define _DEQUE_H_

typedef void* data_type;
typedef struct Deque Deque;

// criacao do deque
Deque *deque_create(void);

// funcoes para insercao na direita e esquerda (devem ser feitas em O(1), com eventual realloc)
void deque_push_back(Deque *d, void *val);
void deque_push_front(Deque *d, void *val);

// funcoes para remocao na direita e esquerda (devem ser feitas em O(1))
void *deque_pop_back(Deque *d);
void *deque_pop_front(Deque *d);

// numero de elementos
int deque_size(Deque *d);

// obtem o i-esimo elemento
void *deque_get(Deque *d, int idx);

// libera o espaco alocado para o deque
void deque_destroy(Deque *d);
void print_deque(Deque* deque, void (*print)(void*));
void print_infos_deque(Deque* d);
void __deque_realoc_map(Deque *d, int new_map_size);
data_type* __deque_alloc_bucket();
void __deque_free_bucket(data_type* bucket);
void __deque_centralize_map(Deque* d);

#endif