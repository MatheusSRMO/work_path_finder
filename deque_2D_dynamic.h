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

void deque_2D_push_back(Deque_2D_dynamic deque, NodePtr item);

void deque_2D_push_front(Deque_2D_dynamic deque, NodePtr item);

NodePtr deque_2D_pop_back(Deque_2D_dynamic deque);

void deque_2D_show(Deque_2D_dynamic deque);

NodePtr deque_2D_pop_front(Deque_2D_dynamic deque);

#endif // DEQUE_2D_DYNAMIC_H