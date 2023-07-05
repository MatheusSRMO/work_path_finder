
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "heap.h"
#include "hash.h"

typedef struct {
    int x, y;
    float g, h;
} Celula;

Celula *celula_create(int x, int y) {
    Celula *c = malloc(sizeof(Celula));
    c->x = x;
    c->y = y;
    return c;
}

void celula_destroy(Celula *c) {
    free(c);
}

int celula_hash(HashTable *h, void *key) {
    Celula *c = (Celula *)key;
    // 83 e 97 sao primos e o operador "^" é o XOR bit a bit
    return ((c->x * 83) ^ (c->y * 97)) % hash_table_size(h);
}

int celula_cmp(void *c1, void *c2) {
    Celula *a = (Celula *)c1;
    Celula *b = (Celula *)c2;

    if (a->x == b->x && a->y == b->y)
        return 0;
    else
        return 1;
}

void celula_print(void* cel) {
    Celula* c = cel;
    printf("(%d, %d)\n", c->x, c->y);
}

int main() {
    int i, n, x, y, priority;
    char cmd[10];

    HashTable *h = hash_table_construct(19, celula_hash, celula_cmp);
    Heap *heap = heap_construct(h);

    // TODO

    celula_print(heap_push(heap, celula_create(1, 1), 1, heap_node_compare));
    celula_print(heap_push(heap, celula_create(2, 2), 2, heap_node_compare));
    celula_print(heap_push(heap, celula_create(3, 3), 3, heap_node_compare));
    celula_print(heap_push(heap, celula_create(4, 4), 4, heap_node_compare));
    celula_print(heap_push(heap, celula_create(5, 5), 5, heap_node_compare));

    Celula* c1 = heap_pop(heap, heap_node_compare);
    Celula* c2 = heap_pop(heap, heap_node_compare);
    Celula* c3 = heap_pop(heap, heap_node_compare);

    celula_print(c1);
    celula_print(c2);
    celula_print(c3);

    celula_destroy(c1);
    celula_destroy(c2);
    celula_destroy(c3);


    hash_table_destroy(h);
    heap_destroy(heap);

    return 0;
}