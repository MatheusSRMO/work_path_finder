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

// Cria uma matriz com o número especificado de linhas e colunas
Matrix* matrix_construct(int m, int n);

// Libera a memória alocada para a matriz e seus nós
void matrix_destroy(Matrix* matrix);

// Atribui um valor a uma posição específica (i, j) da matriz
void matrix_assign_value(Matrix* matrix, int i, int j, data_type value);

// Remove o valor de uma posição específica (i, j) da matriz
void matrix_remove_value(Matrix* matrix, int i, int j);

// Retorna o valor em uma posição específica (i, j) da matriz
data_type matrix_get_value(Matrix* matrix, int i, int j);

// Mostra a matriz de forma densa, imprimindo seus elementos em uma representação tabular
void matrix_show_dense(Matrix* matrix, void (*print)(data_type));

// Mostra a matriz de forma esparsa, imprimindo apenas os elementos não nulos e suas posições
void matrix_show_sparce(Matrix* matrix, void (*print)(data_type));

// Realiza a soma de duas matrizes
Matrix* matrix_sum(Matrix* m1, Matrix* m2);

// Multiplica todos os elementos da matriz por um escalar
Matrix* matrix_multiply_by_a_scalar(Matrix* matrix, data_type scalar);

// Realiza a multiplicação de duas matrizes
Matrix* matrix_multiply(Matrix* m1, Matrix* m2);

// Realiza uma operação ponto a ponto entre duas matrizes
Matrix* matrix_pointwise_operation(Matrix* m1, Matrix* m2);

// Troca as posições de duas linhas na matriz
void matrix_swap_rows(Matrix* matrix, int row_index_1, int row_index_2);

// Troca as posições de duas colunas na matriz
void matrix_swap_columns(Matrix* matrix, int column_index_index_1, int column_index_index_2);

// Obtém uma submatriz da matriz original com base nos índices especificados
Matrix* matrix_get_submatrix(Matrix* matrix, int x1, int y1, int x2, int y2);

// Calcula a matriz transposta da matriz original
Matrix* matrix_transpose(Matrix* matrix);

// Calcula a soma de todos os elementos da matriz
data_type matrix_sum_elements(Matrix* matrix);

// Realiza a convolução entre a matriz e o kernel especificado
Matrix* matrix_convolution(Matrix* input, Matrix* kernel);

// Salva a matriz em um arquivo binário 
void matrix_to_binary_file(Matrix* matrix, const char* filename);

// Carrega uma matriz de um arquivo binário
Matrix* matrix_from_binary_file(const char* filename);

#endif  // MATRIX_H_
