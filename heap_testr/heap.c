#include "heap.h"

// Estrutura de um elemento do heap
typedef struct HeapNode {
    void* value;               // Valor do elemento
    int priority;              // Prioridade do elemento
} HeapNode;

// Estrutura do Heap
struct Heap {
    HeapNode* nodes;           // nodes para armazenar os elementos do heap
    int capacity;              // Capacidade máxima do heap
    int size;                  // Tamanho atual do heap
    HashTable* hash_table;     // Tabela hash para mapear os elementos para suas posições no heap
};

Heap* heap_construct(HashTable *h) {
    Heap* heap = malloc(sizeof(Heap));
    heap->capacity = hash_table_size(h);
    heap->size = 0;
    heap->nodes = malloc(sizeof(HeapNode) * heap->capacity);
    heap->hash_table = h;
    return heap;
}

void swap(HeapNode* a, HeapNode* b) {
    HeapNode aux = *a;
    *a = *b;
    *b = aux;
}

void heapify(Heap* heap, int i) {
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    int largest = i;

    if (left < heap->size && heap->nodes[left].priority > heap->nodes[largest].priority)
        largest = left;

    if (right < heap->size && heap->nodes[right].priority > heap->nodes[largest].priority)
        largest = right;

    if (largest != i) {
        hash_table_set(heap->hash_table, heap->nodes[i].value, largest);
        hash_table_set(heap->hash_table, heap->nodes[largest].value, i);
        swap(&heap->nodes[i], &heap->nodes[largest]);
        heapify(heap, largest);
    }
}
