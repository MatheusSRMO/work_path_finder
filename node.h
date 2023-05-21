#ifndef NODE_H_
#define NODE_H_
#include <stdlib.h>

typedef float data_type;

typedef struct Node {
    int i;
    int j;
    data_type data;
    struct Node* next_in_line;
    struct Node* next_in_column;
} Node;

// Aloca memória para um nó
Node* node_construct(int i, int j, data_type data, Node* next_in_line, Node* next_in_column);

// Libera a memória alocada para um nó
void node_destroy(Node* node);

#endif  // NODE_H_