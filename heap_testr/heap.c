#include <stdio.h>
#include <stdlib.h>
#include "heap.h"
#include "hash.h"

struct HeapNode {
    void* data; // Ponteiro genérico para o dado armazenado
    double priority; // Prioridade do elemento
};

// Estrutura para representar um heap
struct Heap {
    HeapNode* data; // Array de ponteiros genéricos
    int size;    // Tamanho atual do heap
    int capacity; // Capacidade máxima do heap
    HashTable* hash_table; // Tabela de hash para mapear os elementos do heap
};

// Função auxiliar para criar um novo heap
Heap* heap_construct(HashTable* hash_table) {
    int capacity = hash_table_size(hash_table);
    Heap* heap = (Heap*)malloc(sizeof(Heap));
    heap->data = (HeapNode*)malloc(capacity * sizeof(HeapNode));
    heap->size = 0;
    heap->capacity = capacity;
    heap->hash_table = hash_table;
    return heap;
}

// Função auxiliar para trocar dois elementos no heap
void swap(HeapNode* a, HeapNode* b) {
    HeapNode temp = *a;
    *a = *b;
    *b = temp;
}

int heap_node_compare(HeapNode a, HeapNode b) {
    if (a.priority < b.priority) {
        return -1;
    } else if (a.priority > b.priority) {
        return 1;
    } else {
        return 0;
    }
}

// Função para ajustar o heap para baixo (quando um elemento é removido)
void heapify_down(Heap* heap, int index, int (*compare)(HeapNode, HeapNode)) {
    int left_child = 2 * index + 1;
    int right_child = 2 * index + 2;
    int largest = index;

    if (left_child < heap->size && compare(heap->data[left_child], heap->data[largest]) > 0) {
        largest = left_child;
    }

    if (right_child < heap->size && compare(heap->data[right_child], heap->data[largest]) > 0) {
        largest = right_child;
    }

    if (largest != index) {
        swap(&heap->data[index], &heap->data[largest]);
        heapify_down(heap, largest, compare);
    }
}

// Função para ajustar o heap para cima (quando um elemento é inserido)
void heapify_up(Heap* heap, int index, int (*compare)(HeapNode, HeapNode)) {
    int parent = (index - 1) / 2;

    if (parent >= 0 && compare(heap->data[index], heap->data[parent]) > 0) {
        swap(&heap->data[index], &heap->data[parent]);
        heapify_up(heap, parent, compare);
    }
}

// Função para inserir um elemento no heap
void* heap_push(Heap *heap, void *data, double priority, int (*compare)(HeapNode, HeapNode)) {
    if (heap->size == heap->capacity) {
        heap->capacity *= 2;
        heap->data = realloc(heap->data, heap->capacity * sizeof(HeapNode));
    }

    void* del = NULL;
    del hash_table_get(heap->hash_table, data);
    if(del != NULL) {
        hash_table_pop()
    }
    hash_table_set(heap->hash_table, data, &priority);

    HeapNode node;
    node.data = data;
    node.priority = priority;
    
    heap->data[heap->size] = node;
    heap->size++;
    heapify_up(heap, heap->size - 1, compare);
    return del;
}

void* heap_pop(Heap* heap, int (*compare)(HeapNode, HeapNode)) {
    if (heap->size == 0) {
        printf("O heap está vazio. Não há elementos para remover.\n");
        return NULL;
    }

    HeapNode maxItem = heap->data[0];
    heap->data[0] = heap->data[heap->size - 1];
    heap->size--;
    heapify_down(heap, 0, compare);

    return maxItem.data;
}

double heap_min_priority(Heap* heap) {
    return heap->data[0].priority;
}

void heap_destroy(Heap *heap) {
    for(int i = 0; i < heap->size; i++)
        free(heap->data[i].data);
    free(heap->data);
    free(heap);
}
