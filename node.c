#include "node.h"

typedef enum {
    INT,
    FLOAT,
    DOUBLE,
    CHAR,
    STRING,
    BOOL
} DataType;

struct node {
    void* data;
    DataType type;
    struct node * prev;
};

