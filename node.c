#include "node.h"

struct node {
    int i, j;
    void* data;
    DataType type;
    struct node* prev;
};

NodePtr node_create(int i, int j, void* data, DataType type) {
    NodePtr node = malloc(sizeof(struct node));
    node->i = i;
    node->j = j;
    node->data = data;
    node->type = type;
    node->prev = NULL;
    return node;
}

NodePtr node_get_prev(NodePtr node) {
    return node->prev;
}

void node_set_prev(NodePtr node, NodePtr prev) {
    node->prev = prev;
}

void node_destroy(NodePtr node) {
    free(node);
}
