#include <stdio.h>
#include <stdlib.h>
#include "node.h"
#include "matrix.h"

void print_int(data_type data) {
    printf("%d", data);
}

int main() {
    // Matrix* matrix_txt = matrix_from_txt_file("path/to/file.txt", read_int);
    // matrix_show_sparce(matrix_txt, print_int);

    // Teste matrix_construct
    Matrix* matrix = matrix_construct(3, 3);

    // Teste matrix_assign_value
    matrix_assign_value(matrix, 2, 2, 9);
    matrix_assign_value(matrix, 0, 0, 1);
    matrix_assign_value(matrix, 2, 1, 8);
    matrix_assign_value(matrix, 1, 0, 4);
    matrix_assign_value(matrix, 0, 1, 2);
    matrix_assign_value(matrix, 1, 2, 6);
    matrix_assign_value(matrix, 2, 0, 7);
    matrix_assign_value(matrix, 0, 2, 3);
    matrix_assign_value(matrix, 1, 1, 5);

    // Teste matrix_show_dense
    printf("\nMatrix elements:\n");
    matrix_show_dense(matrix, print_int);

    // Teste matrix_sum
    Matrix* sum_matrix = matrix_sum(matrix, matrix);
    printf("\nSum of matrices:\n");
    matrix_show_dense(sum_matrix, print_int);

    // Teste matrix_multiply_by_a_scalar
    Matrix* scalar_matrix = matrix_multiply_by_a_scalar(matrix, 2);
    printf("\nMatrix multiplied by scalar:\n");
    matrix_show_dense(scalar_matrix, print_int);

    // Teste matrix_multiply
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

    // Teste matrix_pointwise_operation
    Matrix* pointwise_matrix = matrix_pointwise_operation(matrix, matrix);
    printf("\nPointwise matrix operation:\n");
    matrix_show_dense(pointwise_matrix, print_int);

    // Teste matrix_transpose
    Matrix* transpose_matrix = matrix_transpose(matrix);
    printf("\nTransposed matrix:\n");
    matrix_show_dense(transpose_matrix, print_int);

    // Teste matrix_sum_elements
    data_type sum = matrix_sum_elements(matrix);
    printf("\nSum of matrix elements: %d\n", sum);

    // Teste matrix_convolution
    Matrix* kernel = matrix_construct(3, 3);
    matrix_assign_value(kernel, 0, 0, 1);
    matrix_assign_value(kernel, 0, 1, 1);
    matrix_assign_value(kernel, 0, 2, 1);
    matrix_assign_value(kernel, 1, 0, 1);
    matrix_assign_value(kernel, 1, 2, 1);
    matrix_assign_value(kernel, 2, 0, 1);
    matrix_assign_value(kernel, 2, 1, 1);
    matrix_assign_value(kernel, 2, 2, 1);

    Matrix* convolution_result = matrix_convolution(matrix, kernel);
    printf("\nConvolution result:\n");
    matrix_show_dense(convolution_result, print_int);

    // Teste matrix_to_binary_file
    matrix_to_binary_file(matrix, "matrix.bin");

    // Teste matrix_from_binary_file
    Matrix* matrix_from_file = matrix_from_binary_file("matrix.bin");
    matrix_swap_rows(matrix_from_file, 0, matrix_from_file->m - 1);
    matrix_swap_columns(matrix_from_file, 0, matrix_from_file->n - 1);
    printf("\nMatrix from file:\n");
    matrix_show_dense(matrix_from_file, print_int);

    // Libera espaço na memoria 
    // matrix_destroy(matrix_txt);
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
    matrix_destroy(matrix_from_file);
    return 0;
}
