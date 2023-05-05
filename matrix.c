#include "matrix.h"
#define STANDARD_VALUE 0

Matrix* matrix_construct(int m, int n) {
    Matrix* matrix = (Matrix*) malloc(sizeof(Matrix));
    matrix->m = m;
    matrix->n = n;
    matrix->lines_heads = (Node**) malloc(m * sizeof(Node*));
    matrix->columns_heads = (Node**) malloc(n * sizeof(Node*));
    for(int i = 0; i < m; i++) {
        matrix->lines_heads[i] = NULL;
    }
    for(int i = 0; i < n; i++) {
        matrix->columns_heads[i] = NULL;
    }
    return matrix;
}

void matrix_destroy(Matrix* matrix) {
    for(int i = 0; i < matrix->m; i++) {
        Node* node = matrix->lines_heads[i];
        while(node != NULL) {
            Node* next = node->next_in_line;
            node_destroy(node);
            node = next;
        }
    }
    free(matrix->lines_heads);
    free(matrix->columns_heads);
    free(matrix);
}

void matrix_assign_value(Matrix* matrix, int i, int j, data_type value) {
    // Verifica se 0 <= i-1 < m e 0 <= j-1 < n
    if (i-1 < 0 || i-1 >= matrix->m || j-1 < 0 || j-1 >= matrix->n) {
        exit(printf("Valores ij invalidos!!\n"));
    }

    Node* line = matrix->lines_heads[i-1];
    Node* column = matrix->columns_heads[j-1];

    if (line == NULL || column == NULL) {
        Node* new_node = node_construct(i, j, value, line, column);
        matrix->lines_heads[i-1] = matrix->columns_heads[j-1] = new_node;
    } 
    else {
        while (line->j < j && line->next_in_line != NULL) {
            line = line->next_in_line;
        }
        while (column->i < i && column->next_in_column != NULL) {
            column = column->next_in_column;
        }
        if (line->j == j && column->i == i) {
            if(value == STANDARD_VALUE) {
                
                if(line == matrix->lines_heads[i-1]) {
                    matrix->lines_heads[i-1] = line->next_in_line;
                }
                else {
                    Node* prev = matrix->lines_heads[i-1];
                    while(prev->next_in_line != line) {
                        prev = prev->next_in_line;
                    }
                    prev->next_in_line = line->next_in_line;
                }

                if(column == matrix->columns_heads[j-1]) {
                    matrix->columns_heads[j-1] = column->next_in_column;
                }
                else {
                    Node* prev = matrix->columns_heads[j-1];
                    while(prev->next_in_column != column) {
                        prev = prev->next_in_column;
                    }
                    prev->next_in_column = column->next_in_column;
                }

                node_destroy(line);
            }
            else {
                line->data = value;
            }

        } 
        else if(value != STANDARD_VALUE) {
            Node* new_node = node_construct(i, j, value, line->next_in_line, column->next_in_column);
            line->next_in_line = column->next_in_column = new_node;
        }
    }
}

void matrix_remove_value(Matrix* matrix, int i, int j) {
    matrix_assign_value(matrix, i, j, STANDARD_VALUE);
}


data_type matrix_get_value(Matrix* matrix, int i, int j) {
    if(!(i-1 < matrix->m && i-1 >= 0) || !(j-1 < matrix->n && j-1 >= 0)) {
        exit(printf("Valores ij invalidos!!\n"));
    }
    data_type value = STANDARD_VALUE;
    if(i <= j) {
        Node* n = matrix->columns_heads[j-1];
        while(n != NULL) {
            if(n->i == i) {
                value = n->data;
                break;
            }
            n = n->next_in_column;
        }
    }
    else {
        Node* n = matrix->lines_heads[i-1];
        while(n != NULL) {
            if(n->j == j) {
                value = n->data;
                break;
            }
            n = n->next_in_line;
        }
    }

    return value;
}

void matrix_show(Matrix* matrix, void (*print)(data_type)) {
    for(int i = 1; i <= matrix->m; i++) {
        for(int j = 1; j <= matrix->n; j++) {
            data_type val = matrix_get_value(matrix, i, j);
            print(val);
            printf(" ");
        }
        printf("\n");
    }
}

Matrix* matrix_sum(Matrix* m1, Matrix* m2) {
    if((m1->m != m2->m) || (m1->n != m2->n))
        exit(printf("Não é possível realizar soma de matrizes com tamanho diferentes\n"));

    Matrix* result = matrix_construct(m1->m, m1->n);

    for(int i = 1; i <= result->m; i++) {
        for(int j = 1; j <= result->n; j++) {
            data_type v1 = matrix_get_value(m1, i, j);
            data_type v2 = matrix_get_value(m2, i, j);
            if(v1 != 0 || v2 != 0) 
                matrix_assign_value(result, i, j, v1+v2);
        }
    }

    return result;
}

Matrix* matrix_multiply_by_a_scalar(Matrix* matrix, data_type scalar) {
    Matrix* result = matrix_construct(matrix->m, matrix->n);

    for(int i=0; i < matrix->m; i++) {
        Node* node = matrix->lines_heads[i];
        while(node != NULL) {
            matrix_assign_value(result, node->i, node->j, node->data*scalar);
            node = node->next_in_line;
        }        
    }

    return result;
}

Matrix* matrix_multiply(Matrix* m1, Matrix* m2) {
    if(m1->n != m2->m)
        exit(printf("Não é possivel multiplicar A%dx%d por B%dx%d\n", m1->m, m1->n, m2->m, m2->n));

    Matrix* result = matrix_construct(m1->m, m2->n);
    for(int i = 0; i < result->m; i++) {
        for(int j = 0; i < result->n; j++) {
            
        }
    }
}
