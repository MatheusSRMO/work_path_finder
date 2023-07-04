#ifndef _HEAP_H_
#define _HEAP_H_

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include "hash.h"
#include "forward_list.h"

typedef struct Heap Heap;

// a funcao de comparacao para o heap está dentro da hash table
Heap* heap_construct(HashTable *h);
void* heap_push(Heap *heap, void *data, double priority);
bool heap_empty(Heap *heap);
void* heap_max(Heap *heap);
double heap_max_priority(Heap *heap);
int heap_min_priority(Heap* heap);
void* heap_pop(Heap *heap);
void heap_destroy(Heap *heap);

#endif // _HEAP_H_