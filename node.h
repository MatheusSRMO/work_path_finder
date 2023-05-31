#ifndef NODE_H
#define NODE_H


#include <stdio.h>
#include <stdlib.h>

typedef enum {
    INT,
    FLOAT,
    DOUBLE,
    CHAR,
    STRING,
    BOOL
} DataType;

typedef struct node* NodePtr;

NodePtr node_create(void* data, DataType type);

void node_set_prev(NodePtr node, NodePtr prev);

NodePtr node_get_prev(NodePtr node);

void node_destroy(NodePtr node);

#endif // NODE_H