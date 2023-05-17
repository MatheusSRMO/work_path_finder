import numpy as np

def sum_matrices(matrix1, matrix2):
    result = np.add(matrix1, matrix2)
    return result

def matrix_multiplication(matrix1, matrix2):
    result = np.dot(matrix1, matrix2)
    return result

def elementwise_multiplication(matrix1, matrix2):
    result = np.multiply(matrix1, matrix2)
    return result

def matrix_multiply_by_scalar(matrix, scalar):
    result = np.multiply(matrix, scalar)
    return result

def matrix_transpose(matrix):
    result = np.transpose(matrix)
    return result

def matrix_sum_elements(matrix):
    result = np.sum(matrix)
    return result

def convolution(matrix, kernel):
    m_rows, m_cols = matrix.shape
    k_rows, k_cols = kernel.shape

    # Cria uma matriz de zeros para armazenar o resultado da convolução
    result = np.zeros_like(matrix)

    # Calcula o deslocamento do kernel para tratar a borda
    pad_rows = k_rows // 2
    pad_cols = k_cols // 2

    # Adiciona uma camada de zeros ao redor da matriz para tratar a borda
    padded_matrix = np.pad(matrix, ((pad_rows, pad_rows), (pad_cols, pad_cols)), mode='constant')

    # Realiza a convolução
    for i in range(m_rows):
        for j in range(m_cols):
            result[i, j] = np.sum(padded_matrix[i:i+k_rows, j:j+k_cols] * kernel)

    return result


# Matriz de imagem
matrix = np.array([[1, 2, 3],
                  [4, 5, 6],
                  [7, 8, 9]])

# Matriz do kernel
kernel = np.array([[1, 1, 1], 
                   [1, 0, 1], 
                   [1, 1, 1]])

# print(matrix)

# print("Test matrix sum")
# print(sum_matrices(matrix, matrix))

# print("Test matrix multiplication by scalar")
# print(matrix_multiply_by_scalar(matrix, 2))

# print("Test elementwise_multiplication")
# print(elementwise_multiplication(matrix, matrix))




print("Realiza a convolução")
result = convolution(matrix, kernel)

# # Imprime o resultado
# print(kernel)
print(result)
