#ifndef DEQUE_1D_DYNAMIC_H
#define DEQUE_1D_DYNAMIC_H


#include <stdlib.h>
#include <stdio.h>
#include "node.h"


typedef struct deque_1D_dynamic* Deque_1D_dynamic;

/// @brief create a new deque
/// @param capacity 
/// @return created deque
Deque_1D_dynamic deque_1D_construct(int capacity);

/// @brief get the size of the deque
/// @param deque 
/// @param item 
void deque_1D_push_back(Deque_1D_dynamic deque, NodePtr item);

/// @brief remove the last element of the deque
/// @param deque 
/// @return element removed
NodePtr deque_1D_pop_back(Deque_1D_dynamic deque);

/// @brief add an element to the front of the deque
/// @param deque 
/// @param item 
void deque_1D_push_front(Deque_1D_dynamic deque, NodePtr item);

/// @brief remove the first element of the deque
/// @param deque
/// @return the removed element
NodePtr deque_1D_pop_front(Deque_1D_dynamic deque);

/// @brief print deque
/// @param deque 
void deque_1D_print(Deque_1D_dynamic deque);

/// @brief destroy deque
/// @param deque 
void deque_1D_destruct(Deque_1D_dynamic deque);

#endif // DEQUE_1D_DYNAMIC_H