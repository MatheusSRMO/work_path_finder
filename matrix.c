#include "matrix.h"
#define STANDARD_VALUE 0

// Complexidade: O(m+n)
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

// Complexidade: O(m*n)
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

// Complexidade: O(m+n) no pior dos casos
void matrix_assign_value(Matrix* matrix, int i, int j, data_type value) {
    // Verificar se 0 < i < m e 0 < j < n
    if (i < 0 || i >= matrix->m || j < 0 || j >= matrix->n) {
        printf("Valores ij inválidos!!\n");
        return;
    }

    Node** line = &(matrix->lines_heads[i]);
    Node** column = &(matrix->columns_heads[j]);

    while (*line != NULL && (*line)->j < j) {
        line = &((*line)->next_in_line);
    }

    while (*column != NULL && (*column)->i < i) {
        column = &((*column)->next_in_column);
    }

    if (*line != NULL && (*line)->j == j && (*line)->i == i) {
        if (value == STANDARD_VALUE) {
            Node* node_to_remove = *line;
            *line = (*line)->next_in_line;
            *column = (*column)->next_in_column;
            node_destroy(node_to_remove);
            return;
        }
        (*line)->data = value;
        return;
    }
    if (value != STANDARD_VALUE) 
        *line = *column = node_construct(i, j, value, *line, *column);
}


void matrix_remove_value(Matrix* matrix, int i, int j) {
    matrix_assign_value(matrix, i, j, STANDARD_VALUE);
}

// Complexidade: O(min(m, n))
data_type matrix_get_value(Matrix* matrix, int i, int j) {
    if(!(i < matrix->m && i >= 0) || !(j < matrix->n && j >= 0)) {
        exit(printf("Valores ij invalidos!!\n"));
    }
    data_type value = STANDARD_VALUE;
    if(i <= j) {
        Node* n = matrix->columns_heads[j];
        while(n != NULL) {
            if(n->i == i) {
                value = n->data;
                break;
            }
            n = n->next_in_column;
        }
    }
    else {
        Node* n = matrix->lines_heads[i];
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

void matrix_show_dense(Matrix* matrix, void (*print)(data_type)) {
    for(int i = 0; i < matrix->m; i++) {
        for(int j = 0; j < matrix->n; j++) {
            data_type val = matrix_get_value(matrix, i, j);
            print(val);
            printf(" ");
        }
        printf("\n");
    }
}

void matrix_show_sparce(Matrix* matrix, void (*print)(data_type)) {
    for(int i = 0; i < matrix->m; i++) {
        Node* node = matrix->lines_heads[i];
        while(node != NULL) {
            printf("(");
            print(node->i);
            printf(", ");
            print(node->j);
            printf(") -> ");
            print(node->data);
            printf("\n");
            node = node->next_in_line;
        }
        printf("\n");
    }
}

Matrix* matrix_sum(Matrix* m1, Matrix* m2) {
    if (m1->m != m2->m || m1->n != m2->n) {
        exit(printf("Não é possível realizar soma de matrizes com tamanhos diferentes\n"));
    }

    Matrix* result = matrix_construct(m1->m, m1->n);

    for (int i = 0; i < m1->m; i++) {
        Node* node1 = m1->lines_heads[i];
        Node* node2 = m2->lines_heads[i];

        while (node1 != NULL || node2 != NULL) {
            if (node1 != NULL && node2 != NULL && node1->j == node2->j) {
                // Elemento presente em ambas as matrizes
                data_type sum = node1->data + node2->data;
                
                if(sum != 0)
                    matrix_assign_value(result, i, node1->j, sum);
                
                node1 = node1->next_in_line;
                node2 = node2->next_in_line;
            }
            else if (node1 != NULL && (node2 == NULL || node1->j < node2->j)) {
                // Elemento presente apenas em m1
                matrix_assign_value(result, i, node1->j, node1->data);
                
                node1 = node1->next_in_line;
            }
            else {
                // Elemento presente apenas em m2
                matrix_assign_value(result, i, node2->j, node2->data);
                
                node2 = node2->next_in_line;
            }
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
            data_type in = 0;
            for(int k = 0; k < result->n; k++) {
                data_type v1 = matrix_get_value(m1, i, k);
                data_type v2 = matrix_get_value(m2, k, j);
                in += v1*v2;
            }
            if(in != 0) matrix_assign_value(result, i, j, in);
        }
    }
    return result;
}

Matrix* matrix_pointwise_operation(Matrix* m1, Matrix* m2) {
    if (m1->m != m2->m || m1->n != m2->n) {
        exit(printf("Não é possível realizar soma de matrizes com tamanhos diferentes\n"));
    }

    Matrix* result = matrix_construct(m1->m, m1->n);

    for (int i = 0; i < m1->m; i++) {
        Node* node1 = m1->lines_heads[i];
        Node* node2 = m2->lines_heads[i];

        while (node1 != NULL || node2 != NULL) {
            if (node1 != NULL && node2 != NULL && node1->j == node2->j) {
                // Elemento presente em ambas as matrizes
                data_type mult = node1->data * node2->data;
                
                if(mult != 0)
                    matrix_assign_value(result, i, node1->j, mult);
                
                node1 = node1->next_in_line;
                node2 = node2->next_in_line;
            }
            else if (node1 != NULL && (node2 == NULL || node1->j < node2->j)) {
                // Elemento presente apenas em m1                
                node1 = node1->next_in_line;
            }
            else {
                // Elemento presente apenas em m2                
                node2 = node2->next_in_line;
            }
        }
    }

    return result;
}


void matrix_swap_rows(Matrix* matrix, int row_index_1, int row_index_2) {
    if(row_index_1 < 0 || row_index_2 < 0 || row_index_1 >= matrix->m || row_index_2 >= matrix->m)
        exit(printf("Não é possível trocar linhas pois os indices não existem na matriz!\n"));
    
    row_index_1 --;
    row_index_2 --;

    Node* aux = matrix->lines_heads[row_index_1];
    matrix->lines_heads[row_index_1] = matrix->lines_heads[row_index_2];
    matrix->lines_heads[row_index_2] = aux;
    
    Node* n1 = matrix->lines_heads[row_index_1];
    Node* n2 = matrix->lines_heads[row_index_2];

    while(n1 != NULL) {
        n1->i = row_index_1;
        n1 = n1->next_in_line;
    }
    while(n2 != NULL) {
        n2->i = row_index_2;
        n2 = n2->next_in_line;
    }
}

void matrix_swap_columns(Matrix* matrix, int column_index_1, int column_index_2) {
    column_index_1 --;
    column_index_2 --;

    Node* aux = matrix->columns_heads[column_index_1];
    matrix->columns_heads[column_index_1] = matrix->columns_heads[column_index_2];
    matrix->columns_heads[column_index_2] = aux;
    
    Node* n1 = matrix->columns_heads[column_index_1];
    Node* n2 = matrix->columns_heads[column_index_2];

    while(n1 != NULL) {
        n1->j = column_index_1;
        n1 = n1->next_in_column;
    }
    while(n2 != NULL) {
        n2->j = column_index_2;
        n2 = n2->next_in_column;
    }
}

Matrix* matrix_get_submatrix(Matrix* matrix, int x1, int y1, int x2, int y2) {
    int m = matrix->m;
    int n = matrix->n;
    if(x1 < 0 || x1 >= m || x2 < 0 || x2 >= m || y1 < 0 || y1 >= n || y2 < 0 || y2 >= n) {
        exit(printf("Não é possível obter submatriz com as cordenadas fornecidas!\n"));
    }
    Matrix* result = matrix_construct(y2-y1+1, x2-x1+1);

    for(int i = y1, k = 1; i <= y2; i++, k++) 
        for(int j = x1, a = 1; j <= x2; j++, a++) {
            data_type cel = matrix_get_value(matrix, i, j);
            if(cel != STANDARD_VALUE) 
                matrix_assign_value(result, k, a, cel);
        }
    
    return result;
}

Matrix* matrix_transpose(Matrix* matrix) {
    Matrix* result = matrix_construct(matrix->n, matrix->m);

    for(int i = 1; i <= matrix->m; i++) {
        for(int j = 1; j <= matrix->n; j++) {
            data_type cel = matrix_get_value(matrix, i, j);
            if(cel != STANDARD_VALUE) 
                matrix_assign_value(result, j, i, cel);
        }
    }

    return result;
}
