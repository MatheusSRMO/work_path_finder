#ifndef MATRIX_H_
#define MATRIX_H_

#include <stdlib.h>
#include <stdio.h>
#include "node.h"

typedef struct Matrix {
    int m;
    int n;
    Node** lines_heads;
    Node** columns_heads;
} Matrix;

Matrix* matrix_construct(int m, int n);
void matrix_destroy(Matrix* matrix);
void matrix_assign_value(Matrix* matrix, int i, int j, data_type value);
data_type matrix_get_value(Matrix* matrix, int i, int j);
void matrix_show(Matrix* matrix, void (*print)(data_type));
Matrix* matrix_sum(Matrix* m1, Matrix* m2);
Matrix* matrix_multiply_by_a_scalar(Matrix* matrix, data_type scalar);
Matrix* matrix_multiply(Matrix* m1, Matrix* m2);
Matrix* matrix_pointwise_operation(Matrix* m1, Matrix* m2);
void matrix_swap_rows(Matrix* matrix, int row_index_1, int row_index_2);
void matrix_swap_columns(Matrix* matrix, int column_index_index_1, int column_index_index_2);

#endif  // MATRIX_H_
