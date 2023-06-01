#ifndef DEQUE_2D_DYNAMIC_H
#define DEQUE_2D_DYNAMIC_H


#include <stdio.h>
#include <stdlib.h>

#include "deque_1D_dynamic.h"

typedef struct deque_2D_dynamic* Deque_2D_dynamic;

/// @brief deque_2D_construct
/// @param num_rows 
/// @param num_columns 
/// @return empty 2D deque
Deque_2D_dynamic deque_2D_construct(int num_rows, int num_columns);

#endif // DEQUE_2D_DYNAMIC_H