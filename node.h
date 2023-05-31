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


/// @brief Node constructor
/// @param data void pointer to data
/// @param type enum DataType
/// @return new NodePtr
NodePtr node_create(void* data, DataType type);

/// @brief Get previous node
/// @param node NodePtr
/// @return prev NodePtr
NodePtr node_get_prev(NodePtr node);

/// @brief Set previous node
/// @param node NodePtr
/// @param prev NodePtr
void node_set_prev(NodePtr node, NodePtr prev);

/// @brief Node destructor
/// @param node NodePtr
void node_destroy(NodePtr node);

#endif // NODE_H