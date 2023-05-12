#include <stdio.h>
#include <stdlib.h>
#include "node.h"
#include "matrix.h"


void print_int(data_type data) {
    printf("%d", data);
}

int main() {
    Matrix* matrix = matrix_construct(3, 3);

    matrix_assign_value(matrix, 0, 2, 3);
    matrix_assign_value(matrix, 0, 0, 1);
    matrix_assign_value(matrix, 0, 1, 2);
    
    matrix_assign_value(matrix, 1, 0, 2);
    matrix_assign_value(matrix, 2, 0, 3);

    matrix_assign_value(matrix, 1, 2, 4);
    matrix_assign_value(matrix, 2, 1, 6);

    matrix_assign_value(matrix, 2, 2, 8);

    matrix_assign_value(matrix, 1, 1, 9);

    matrix_show_sparce(matrix, print_int);
    matrix_show_dense(matrix, print_int);

    matrix_destroy(matrix);
    return 0;
}
