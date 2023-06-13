
#include "deque.h"
#include "types.h"
#include <stdlib.h>

struct node {
    data_type data;
    struct node* prev;
    struct node* next;
};

typedef struct node Node;


Node* node_contruct(data_type data, Node* prev, Node* next) {
    Node* node = malloc(sizeof(Node));
    node->data = data;
    node->prev = prev;
    node->next = prev;
    return node;
}

void node_destruct(Node* node) {
    free(node);
}


struct Deque {
    int size;
    Node* head;
    Node* rear;
};


Deque* deque_construct() {
    Deque* deque = malloc(sizeof(Deque));
    deque->size = 0;
    deque->head = NULL;
    deque->rear = NULL;
    return deque;
}

void deque_destroy(Deque* deque) {
    Node* node = deque->head;
    while(node != NULL) {
        Node* aux = node->next;
        node_destruct(node);
        node = aux;
    }
    free(deque);
}

// funcoes para insercao na direita e esquerda (devem ser feitas em O(1), com eventual realloc)
void deque_push_back(Deque *d, void *val) {
    Node* new_node = node_contruct(val, d->rear, NULL);
    if(d->rear == NULL) {
        d->head = d->rear = new_node;
    }
    else {
        d->rear = d->rear->next = new_node;
    }
    d->size++;
}
void deque_push_front(Deque *d, void *val) {
    Node* new_node = node_construct(val, NULL, d->head);
    
    if(d->head == NULL) {

        d->head = d->rear = new_node;
    }
    else {
        d->head = d->head->prev = new_node;
    }
    d->size++;
}

// funcoes para remocao na direita e esquerda (devem ser feitas em O(1))
void *deque_pop_back(Deque *d) {
    if(d->rear == NULL) {
        exit(printf("Error: Deque is empty!\n"));
    }
    Node* node = d->rear;
    data_type data = node->data;

    d->rear = d->rear->prev;
    if(d->rear != NULL) {

        d->rear->next = NULL;
    }

    node_destroy(node);
    d->size--;

    if(d->size <= 1) {
        d->head = d->rear;
    }

    return data;
}
void *deque_pop_front(Deque *d) {
    if(d->head == NULL) {
        exit(printf("Error: Deque is empty!\n"));
    }
    
    Node* node = d->head;
    data_type data = node->data;

    d->head = d->head->next;
    if(d->head != NULL) {
        d->head->prev = NULL;
    }

    node_destroy(node);
    d->size--;

    if(d->size <= 1) {
        d->rear = d->head;
    }

    return data;
}

// numero de elementos
int deque_size(Deque *d) {
    return d->size;
}

// obtem o i-esimo elemento
void *deque_get(Deque *d, int idx) {
    int i = 0;
    Node* node = d->head;
    while(i < idx) {
        node = node->next;
    }
    return node->data;
}