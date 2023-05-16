#include "node.h"

// O(1)
Node* node_construct(int i, int j, data_type data, Node* next_in_line, Node* next_in_column) {
    Node* node = (Node*) malloc(sizeof(Node));
    node->i = i;
    node->j = j;
    node->data = data;
    node->next_in_line = next_in_line;
    node->next_in_column = next_in_column;
    return node;
}

// O(1)
void node_destroy(Node* node) {
    free(node);
}
