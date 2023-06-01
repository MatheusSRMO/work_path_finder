#include <stdio.h>
#include <stdlib.h>
#include "deque_1D_dynamic.h"
#include "node.h"


int main() {
    // Cria um deque com capacidade inicial de 4
    Deque_1D_dynamic deque = deque_1D_construct(4);

    // Insere elementos no final do deque
    printf("Inserindo elementos no final do deque...\n");
    for (int i = 0; i < 6; i++) {
        NodePtr item = node_create(0, 0, &i, INT);
        deque_1D_push_back(deque, item);
        printf("Elemento %d inserido no final do deque.\n", i);
    }

    // Imprime o deque
    printf("Deque: ");
    deque_1D_print(deque);

    // Remove elementos do final do deque
    printf("Removendo elementos do final do deque...\n");
    for (int i = 0; i < 3; i++) {
        deque_1D_pop_back(deque);
        printf("Elemento removido do final do deque.\n");
    }

    // Imprime o deque atualizado
    printf("Deque: ");
    deque_1D_print(deque);

    // Insere elementos no início do deque
    printf("Inserindo elementos no início do deque...\n");
    for (int i = 10; i < 14; i++) {
        NodePtr item = node_create(0, 0, &i, INT);
        deque_1D_push_front(deque, item);
        printf("Elemento %d inserido no início do deque.\n", i);
    }

    // Imprime o deque
    printf("Deque: ");
    deque_1D_print(deque);

    // Remove elementos do início do deque
    printf("Removendo elementos do início do deque...\n");
    for (int i = 0; i < 2; i++) {
        deque_1D_pop_front(deque);
        printf("Elemento removido do início do deque.\n");
    }

    // Imprime o deque atualizado
    printf("Deque: ");
    deque_1D_print(deque);

    // Libera a memória do deque
    deque_1D_destruct(deque);

    return 0;
}
