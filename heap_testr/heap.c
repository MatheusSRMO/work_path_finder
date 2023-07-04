#include "heap.h"

// Estrutura de um elemento do heap
typedef struct HeapNode {
    void* value;     // Valor do elemento
    int priority;    // Prioridade do elemento
} HeapNode;

// Estrutura do Heap
struct Heap {
    HeapNode* nodes;        // nodes para armazenar os elementos do heap
    int capacity;              // Capacidade máxima do heap
    int size;                  // Tamanho atual do heap
    HashTable* hash_table;     // Tabela hash para mapear os elementos para suas posições no heap
};

// Função auxiliar para trocar dois elementos no heap
void swap(HeapNode* a, HeapNode* b) {
    HeapNode temp = *a;
    *a = *b;
    *b = temp;
}

// Função auxiliar para subir um elemento no heap
void heapify_up(Heap* heap, int index) {
    if (index == 0)
        return;

    int parent = (index - 1) / 2;

    // Compara o elemento com seu pai e troca se a prioridade for maior
    if (heap->nodes[index].priority > heap->nodes[parent].priority) {
        // Atualiza a posição na tabela hash
        hash_table_set(heap->hash_table, heap->nodes[index].value, &parent);

        swap(&heap->nodes[index], &heap->nodes[parent]);
        heapify_up(heap, parent);
    }
}

// Função auxiliar para descer um elemento no heap
void heapify_down(Heap* heap, int index) {
    int left_child = 2 * index + 1;
    int right_child = 2 * index + 2;
    int largest = index;

    // Compara o elemento com seus filhos e encontra o maior deles
    if (left_child < heap->size && heap->nodes[left_child].priority > heap->nodes[largest].priority)
        largest = left_child;

    if (right_child < heap->size && heap->nodes[right_child].priority > heap->nodes[largest].priority)
        largest = right_child;

    // Se o maior elemento for diferente do atual, troca as posições
    if (largest != index) {
        // Atualiza a posição na tabela hash
        hash_table_set(heap->hash_table, heap->nodes[index].value, &largest);
        hash_table_set(heap->hash_table, heap->nodes[largest].value, &index);

        swap(&heap->nodes[index], &heap->nodes[largest]);
        heapify_down(heap, largest);
    }
}

// Cria um novo heap
Heap* heap_construct(HashTable* h) {
    Heap* heap = (Heap*)malloc(sizeof(Heap));
    heap->nodes = NULL;
    heap->capacity = 0;
    heap->size = 0;
    heap->hash_table = h;
    return heap;
}

// Insere um novo elemento no heap
void* heap_push(Heap* heap, void* value, double priority) {
    if (heap->size == heap->capacity) {
        // Se o nodes estiver cheio, redimensiona o tamanho
        int new_capacity = (heap->capacity == 0) ? 1 : 2 * heap->capacity;
        heap->nodes = (HeapNode*)realloc(heap->nodes, new_capacity * sizeof(HeapNode));
        heap->capacity = new_capacity;
    }

    // Verifica se o elemento já existe na tabela hash
    void* existing_index = hash_table_get(heap->hash_table, value);
    if (existing_index) {
        int index = *(int*)existing_index;
        // Se a nova prioridade for menor ou igual, retorna o valor existente
        if (priority <= heap->nodes[index].priority)
            return heap->nodes[index].value;
        else {
            // Atualiza a prioridade do elemento existente
            heap->nodes[index].priority = priority;
            heapify_up(heap, index);
            heapify_down(heap, index);
            return NULL;
        }
    }

    // Cria um novo elemento no heap
    HeapNode element;
    element.value = value;
    element.priority = priority;

    // Insere o elemento no final do nodes
    heap->nodes[heap->size] = element;

    // Atualiza a posição na tabela hash
    int index = heap->size;
    hash_table_set(heap->hash_table, value, &index);

    heapify_up(heap, heap->size);
    heap->size++;

    return NULL;
}

// Remove e retorna o elemento de maior prioridade do heap
void* heap_pop(Heap* heap) {
    if (heap->size == 0)
        return NULL;

    void* value = heap->nodes[0].value;
    hash_table_pop(heap->hash_table, value);

    if (heap->size == 1) {
        heap->size = 0;
        return value;
    }

    heap->nodes[0] = heap->nodes[heap->size - 1];
    int index = 0;
    hash_table_set(heap->hash_table, heap->nodes[0].value, &index);
    heap->size--;

    heapify_down(heap, 0);

    return value;
}

// Retorna a prioridade mínima do heap
int heap_min_priority(Heap* heap) {
    if (heap->size == 0)
        return -1;

    return heap->nodes[0].priority;
}

// Libera a memória alocada pelo heap
void heap_destroy(Heap* heap) {
    if (heap == NULL)
        return;

    free(heap->nodes);
    free(heap);
}
