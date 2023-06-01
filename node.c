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

void node_show(NodePtr node) {
    printf("(%d, %d) ", node->i, node->j);
    switch (node->type) {
        case INT:
            printf("%d", *(int*)node->data);
            break;
        case FLOAT:
            printf("%.2f", *(float*)node->data);
            break;
        case DOUBLE:
            printf("%.2lf", *(double*)node->data);
            break;
        case CHAR:
            printf("%c", *(char*)node->data);
            break;
        case STRING:
            printf("%s", (char*)node->data);
            break;
        case BOOL:
            printf("%d", *(int*)node->data);
            break;
    }
}

NodePtr node_get_prev(NodePtr node) {
    return node->prev;
}

void node_set_prev(NodePtr node, NodePtr prev) {
    node->prev = prev;
}

int node__eq__(NodePtr node1, NodePtr node2) {
    return (
        node1->i == node2->i 
        && node1->j == node2->j 
        && node1->type == node2->type
        && node1->data == node2->data
    );
}

void node_destroy(NodePtr node) {
    free(node);
}
