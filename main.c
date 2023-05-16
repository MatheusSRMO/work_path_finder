#include <stdio.h>
#include <stdlib.h>
#include "node.h"
#include "matrix.h"


void print_int(data_type data) {
    printf("%d", data);
}

int main() {
    // Test matrix construction
    Matrix* matrix = matrix_construct(3, 3);

    // Test matrix assignment
    matrix_assign_value(matrix, 0, 0, 1);
    matrix_assign_value(matrix, 0, 1, 2);
    matrix_assign_value(matrix, 0, 2, 3);
    matrix_assign_value(matrix, 1, 0, 4);
    matrix_assign_value(matrix, 1, 1, 5);
    matrix_assign_value(matrix, 1, 2, 6);
    matrix_assign_value(matrix, 2, 0, 7);
    matrix_assign_value(matrix, 2, 1, 8);
    matrix_assign_value(matrix, 2, 2, 9);

    // Test matrix get value
    printf("\nMatrix elements:\n");
    matrix_show_dense(matrix, print_int);

    // Test matrix sum
    Matrix* sum_matrix = matrix_sum(matrix, matrix);
    printf("\nSum of matrices:\n");
    matrix_show_dense(sum_matrix, print_int);

    // Test matrix multiplication by scalar
    Matrix* scalar_matrix = matrix_multiply_by_a_scalar(matrix, 2);
    printf("\nMatrix multiplied by scalar:\n");
    matrix_show_dense(scalar_matrix, print_int);

    // Test matrix multiplication
    Matrix* m1 = matrix_construct(2, 3);
    Matrix* m2 = matrix_construct(3, 2);

    matrix_assign_value(m1, 0, 0, 1);
    matrix_assign_value(m1, 0, 1, 2);
    matrix_assign_value(m1, 0, 2, 3);
    matrix_assign_value(m1, 1, 0, 4);
    matrix_assign_value(m1, 1, 1, 5);
    matrix_assign_value(m1, 1, 2, 6);

    matrix_assign_value(m2, 0, 0, 1);
    matrix_assign_value(m2, 0, 1, 2);
    matrix_assign_value(m2, 1, 0, 3);
    matrix_assign_value(m2, 1, 1, 4);
    matrix_assign_value(m2, 2, 0, 5);
    matrix_assign_value(m2, 2, 1, 6);

    Matrix* multiplication_matrix = matrix_multiply(m1, m2);
    printf("\nMatrix multiplication:\n");
    matrix_show_dense(multiplication_matrix, print_int);

    // Test matrix pointwise operation
    Matrix* pointwise_matrix = matrix_pointwise_operation(matrix, matrix);
    printf("\nPointwise matrix operation:\n");
    matrix_show_dense(pointwise_matrix, print_int);

    // Test matrix transpose
    Matrix* transpose_matrix = matrix_transpose(matrix);
    printf("\nTransposed matrix:\n");
    matrix_show_dense(transpose_matrix, print_int);

    // Test matrix sum elements
    data_type sum = matrix_sum_elements(matrix);
    printf("\nSum of matrix elements: %d\n", sum);

    // Test matrix convolution
    Matrix* kernel = matrix_construct(3, 3);
    matrix_assign_value(kernel, 0, 0, 1);
    matrix_assign_value(kernel, 0, 1, 1);
    matrix_assign_value(kernel, 0, 2, 1);
    matrix_assign_value(kernel, 1, 0, 1);
    matrix_assign_value(kernel, 1, 2, 1);
    matrix_assign_value(kernel, 2, 0, 1);
    matrix_assign_value(kernel, 2, 1, 1);
    matrix_assign_value(kernel, 2, 2, 1);

    printf("\nKernel elements:\n");
    matrix_show_dense(kernel, print_int);

    Matrix* convolution_result = matrix_convolution(matrix, kernel);
    printf("\nConvolution result:\n");
    matrix_show_dense(convolution_result, print_int);

    // Cleanup
    matrix_destroy(matrix);
    matrix_destroy(sum_matrix);
    matrix_destroy(scalar_matrix);
    matrix_destroy(m1);
    matrix_destroy(m2);
    matrix_destroy(multiplication_matrix);
    matrix_destroy(pointwise_matrix);
    matrix_destroy(transpose_matrix);
    matrix_destroy(kernel);
    matrix_destroy(convolution_result);
    return 0;
}
