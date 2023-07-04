#include "heap.h"

// Estrutura de um elemento do heap
struct HeapNode {
    void* value;               // Valor do elemento
    int priority;              // Prioridade do elemento
};

// Estrutura do Heap
struct Heap {
    HeapNode* nodes;           // nodes para armazenar os elementos do heap
    int capacity;              // Capacidade máxima do heap
    int size;                  // Tamanho atual do heap
    HashTable* hash_table;     // Tabela hash para mapear os elementos para suas posições no heap
};


void swap(HeapNode* a, HeapNode* b) {
    HeapNode aux = *a;
    *a = *b;
    *b = aux;
}

void heapify(Heap* heap, int i) {
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    int* largest = malloc(sizeof(int));
    int* idx = malloc(sizeof(int));
    *largest = i;
    *idx = i;

    if (left < heap->size && heap->nodes[left].priority > heap->nodes[*largest].priority)
        *largest = left;

    if (right < heap->size && heap->nodes[right].priority > heap->nodes[*largest].priority)
        *largest = right;

    if (*largest != i) {
        int* old1 = hash_table_set(heap->hash_table, heap->nodes[i].value, largest);
        int* old2 = hash_table_set(heap->hash_table, heap->nodes[*largest].value, idx);

        if(old1 != NULL) free(old1);
        if(old2 != NULL) free(old2);

        swap(&heap->nodes[i], &heap->nodes[*largest]);
        heapify(heap, *largest);
    }
}

void heapify_up(Heap* heap, int i) {
    // Se o elemento for a raiz, não há nada a fazer
    int* idx = malloc(sizeof(int));
    *idx = i;
    int* parent = malloc(sizeof(int));
    *parent = (i - 1) / 2;

    // Se o elemento for maior que o pai, troca os dois
    if (parent >= 0 && heap->nodes[i].priority > heap->nodes[*parent].priority) {
        // Atualiza a tabela hash com as novas posições dos elementos
        int* old1 = hash_table_set(heap->hash_table, heap->nodes[i].value, parent);
        int* old2 = hash_table_set(heap->hash_table, heap->nodes[*parent].value, idx);
        
        if(old1 != NULL) free(old1);
        if(old2 != NULL) free(old2);

        // Troca os elementos
        swap(&heap->nodes[i], &heap->nodes[*parent]);
        // Continua a heapify para cima
        heapify_up(heap, *parent);
    }
}

Heap* heap_construct(HashTable *h) {
    Heap* heap = malloc(sizeof(Heap));
    heap->capacity = hash_table_size(h);
    heap->size = 0;
    heap->nodes = malloc(sizeof(HeapNode) * heap->capacity);
    heap->hash_table = h;
    return heap;
}

void heap_destroy(Heap *heap) {
    free(heap->nodes);
    free(heap);
}
