#include <stdio.h>
#include <stdlib.h>
#include "node.h"
#include "matrix.h"


void print_int(data_type data) {
    printf("%d", data);
}

int main() {
    Matrix* matrix = matrix_construct(5, 11);

    matrix_assign_value(matrix, 1, 4, 8);
    matrix_assign_value(matrix, 2, 8, 3);
    matrix_assign_value(matrix, 1, 8, 3);
    matrix_assign_value(matrix, 5, 4, 8);
    matrix_assign_value(matrix, 5, 8, 0);
    matrix_assign_value(matrix, 5, 8, 1);

    matrix_show(matrix, print_int);
    printf("\n");

    Matrix* res = matrix_multiply_by_a_scalar(matrix, 2);
    matrix_show(res, print_int);
    printf("\n");

    Matrix* res2 = matrix_sum(matrix, res);
    matrix_show(res2, print_int);

    matrix_destroy(res);
    matrix_destroy(res2);
    matrix_destroy(matrix);
    return 0;
}
