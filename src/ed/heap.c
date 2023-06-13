#include "heap.h"
#include <stdio.h>
#include <stdlib.h>


typedef struct {
    data_type data;
    double priority;
} HeapNode;


struct Heap {
    HeapNode* nodes;
    int size;
    int capacity;
};


Heap *heap_construct(int capacity) {
    Heap* heap = malloc(sizeof(Heap));
    heap->nodes = malloc(sizeof(HeapNode) * capacity);
    heap->capacity = capacity;
    heap->size = 0;
    return heap;
}

void heap_swap(HeapNode *a, HeapNode *b) {
    HeapNode temp = *a;
    *a = *b;
    *b = temp;
}

void heap_up(Heap *heap, int index) {
    int parent = (index - 1) / 2;
    while (index > 0 && heap->nodes[index].priority < heap->nodes[parent].priority) {
        heap_swap(&heap->nodes[index], &heap->nodes[parent]);
        index = parent;
        parent = (index - 1) / 2;
    }
}

void heap_down(Heap *heap, int index) {
    int left_child = 2 * index + 1;
    int right_child = 2 * index + 2;
    int smallest = index;
    
    if (left_child < heap->size && heap->nodes[left_child].priority < heap->nodes[smallest].priority) {
        smallest = left_child;
    }
    
    if (right_child < heap->size && heap->nodes[right_child].priority < heap->nodes[smallest].priority) {
        smallest = right_child;
    }
    
    if (smallest != index) {
        heap_swap(&heap->nodes[index], &heap->nodes[smallest]);
        heap_down(heap, smallest);
    }
}

void heap_push(Heap *heap, void *data, double priority) {
    if (heap->size >= heap->capacity) {
        // Heap is full, handle accordingly (e.g., resize the array)
        return;
    }
    
    HeapNode node;
    node.data = data;
    node.priority = priority;
    
    heap->nodes[heap->size] = node;
    heap_up(heap, heap->size);
    heap->size++;
}

void *heap_pop(Heap *heap) {
    if (heap->size == 0) {
        return NULL;
    }
    
    void *data = heap->nodes[0].data;
    heap->size--;
    heap->nodes[0] = heap->nodes[heap->size];
    heap_down(heap, 0);
    
    return data;
}

bool heap_empty(Heap *heap) {
    return heap->size == 0;
}

void *heap_max(Heap *heap) {
    if (heap->size == 0) {
        return NULL;
    }
    
    return heap->nodes[0].data;
}

double heap_max_priority(Heap *heap) {
    if (heap->size == 0) {
        return 0.0;
    }
    
    return heap->nodes[0].priority;
}

int heap_size(Heap *heap) {
    return heap->size;
}

void heap_destroy(Heap *heap) {
    free(heap->nodes);
    free(heap);
}
