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

void node_destroy(NodePtr node);

#endif // NODE_H