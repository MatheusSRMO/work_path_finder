#include "circular_array.h"


struct circular_array {
    data_type* items;
    int capacity;
    int size;
    int front;
    int rear;
    bool dynamic;
};

CircularArray* circular_array_construct(int capacity, bool dynamic) {
    CircularArray* circular_array = malloc(sizeof(CircularArray));

    circular_array->capacity = capacity;
    circular_array->size = 0;
    circular_array->front = 0;
    circular_array->rear = -1;
    circular_array->dynamic = dynamic;
    circular_array->items = malloc(sizeof(data_type) * capacity);

    return circular_array;
}

bool circular_array_is_empty(CircularArray* circular_array) {
    // Verifica se o tamanho é igual a zero
    if (circular_array->size == 0) {
        // Se o tamanho for zero, o array está vazio
        return true;
    } else {
        // Caso contrário, o array não está vazio
        return false;
    }
}

bool circular_array_is_full(CircularArray* circular_array) {
    if (circular_array->size == circular_array->capacity) {
        return true;
    } else {

        return false;
    }
}

void circular_array_push(CircularArray* circular_array, data_type data) {
    if (circular_array_is_full(circular_array) && !circular_array->dynamic) {
        exit(printf("Error: circular array is full and not dynamic.\n"));
    }
    else if(circular_array_is_full(circular_array) && circular_array->dynamic) {
        // Aumenta a capacidade do CircularArray
        int new_capacity = circular_array->capacity * 2;
        data_type* new_items = malloc(sizeof(data_type) * new_capacity);

        // Copia os elementos do CircularArray atual para o novo array com a nova capacidade
        int i, j;
        for (i = circular_array->front, j = 0; j < circular_array->size; i = (i + 1) % circular_array->capacity, j++) {
            new_items[j] = circular_array->items[i];
        }

        // Atualiza os ponteiros e capacidade do CircularArray
        circular_array->front = 0;
        circular_array->rear = circular_array->size - 1;
        circular_array->capacity = new_capacity;

        // Libera a memória do array antigo
        free(circular_array->items);

        // Atualiza o ponteiro de items para apontar para o novo array
        circular_array->items = new_items;
    }

    // Avança o ponteiro rear e adiciona o novo elemento no CircularArray
    circular_array->rear = (circular_array->rear + 1) % circular_array->capacity;
    circular_array->items[circular_array->rear] = data;

    // Incrementa o tamanho do CircularArray
    circular_array->size++;
}

data_type circular_array_pop(CircularArray* circular_array) {
    if (circular_array_is_empty(circular_array)) {
        exit(printf("Error: circular array is empty.\n"));
    }

    // Obtém o elemento na posição do front
    data_type popped_item = circular_array->items[circular_array->front];

    // Move o ponteiro front para a próxima posição
    circular_array->front = (circular_array->front + 1) % circular_array->capacity;

    // Decrementa o tamanho do CircularArray
    circular_array->size--;

    return popped_item;
}

void circular_array_print(CircularArray* circular_array, void (*print_fn)(data_type)) {
    printf("[");
    for(int i = circular_array->front, j = 0; j < circular_array->size; j++, i = (i + 1) % circular_array->capacity) {
        print_fn(circular_array->items[i]);
        if(i != circular_array->rear) {
            printf(", ");
        }
    }
    printf("]\n");
}

void circular_array_destruct(CircularArray* circular_array) {
    free(circular_array->items);
    free(circular_array);
}