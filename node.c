#include "node.h"

struct node {
    void* data;
    DataType type;
    struct node* prev;
};

NodePtr node_create(void* data, DataType type) {
    NodePtr node = malloc(sizeof(struct node));
    node->data = data;
    node->type = type;
    node->prev = NULL;
    return node;
}

void node_destroy(NodePtr node) {
    free(node);
}
