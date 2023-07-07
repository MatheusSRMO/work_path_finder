#ifndef CIRCULAR_ARRAY_H
#define CIRCULAR_ARRAY_H


#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>


typedef void* data_type;
typedef struct circular_array CircularArray;


CircularArray* circular_array_construct(int capacity, bool dynamic);
bool circular_array_is_empty(CircularArray* circular_array);
bool circular_array_is_full(CircularArray* circular_array);
void circular_array_push(CircularArray* circular_array, data_type data);
data_type circular_array_pop(CircularArray* circular_array);
void circular_array_print(CircularArray* circular_array, void (*print_fn)(data_type));
void circular_array_destruct(CircularArray* circular_array);

#endif // CIRCULAR_ARRAY_H