#include <stdio.h>
#include <stdlib.h>
#include "node.h"
#include "matrix.h"


void print_int(data_type data) {
    printf("%d", data);
}

int main() {
    Matrix* matrix = matrix_construct(3, 3);

    matrix_assign_value(matrix, 1, 3, 8);
    matrix_assign_value(matrix, 2, 2, 3);
    matrix_assign_value(matrix, 1, 1, 2);

    matrix_swap_rows(matrix, 1, 2);
    matrix_swap_columns(matrix, 1, 3);

    matrix_show(matrix, print_int);
    printf("\n");


    matrix_destroy(matrix);
    return 0;
}
