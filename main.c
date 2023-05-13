#include <stdio.h>
#include <stdlib.h>
#include "node.h"
#include "matrix.h"


void print_int(data_type data) {
    printf("%d", data);
}

int main() {
    Matrix* matrix = matrix_construct(5, 5);


    matrix_assign_value(matrix, 1, 3, 2);

    matrix_assign_value(matrix, 2, 0, 2);
    matrix_assign_value(matrix, 0, 2, 2);
    matrix_assign_value(matrix, 4, 0, 3);
    matrix_assign_value(matrix, 1, 1, 1);
    matrix_assign_value(matrix, 2, 4, 4);
    matrix_assign_value(matrix, 2, 2, 2);

    matrix_assign_value(matrix, 0, 0, 1);
    matrix_assign_value(matrix, 4, 2, 4);
    matrix_assign_value(matrix, 4, 4, 5);

    matrix_assign_value(matrix, 0, 4, 3);

    matrix_assign_value(matrix, 3, 1, 2);
    matrix_assign_value(matrix, 3, 3, 3);

    matrix_show_dense(matrix, print_int);
    printf("\n");

    Matrix* res = matrix_multiply(matrix, matrix);
    matrix_show_dense(res, print_int);

    matrix_destroy(matrix);
    matrix_destroy(res);
    return 0;
}
