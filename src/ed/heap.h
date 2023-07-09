#ifndef _HEAP_H_
#define _HEAP_H_

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include "hash.h"
#include "forward_list.h"

typedef struct Heap Heap;
typedef struct HeapNode HeapNode;

// a funcao de comparacao para o heap está dentro da hash table
Heap* heap_construct(HashTable* hash_table);
void* heap_push(Heap *heap, void *data, double priority, int (*compare)(HeapNode, HeapNode));
bool heap_is_empty(Heap *heap);
int heap_size(Heap *heap);
void* heap_max(Heap *heap);
double heap_max_priority(Heap *heap);
double heap_min_priority(Heap* heap);
void* heap_pop(Heap* heap, int (*compare)(HeapNode, HeapNode));
void print_heap(Heap* heap, void (*print_node_fn)(HeapNode), void (*print_fn)(void*));
void print_heap_node(HeapNode node);
void heap_destroy(Heap *heap);

int heap_node_compare(HeapNode a, HeapNode b);

#endif // _HEAP_H_