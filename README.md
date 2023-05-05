## Matrizes Esparsas

Este é um código em C para representar matrizes esparsas usando uma estrutura encadeada. O objetivo é permitir operações matemáticas com matrizes esparsas, como multiplicação por um escalar e soma de matrizes.

A implementação utiliza um tipo abstrato de dados para representar a matriz esparsa. A matriz é representada por uma estrutura que contém o número de linhas e colunas, o número de elementos diferentes de zero e um ponteiro para a lista encadeada que armazena os elementos diferentes de zero.

A lista encadeada é implementada com nós que contêm as coordenadas do elemento e o valor do elemento. A lista é ordenada pelas coordenadas da linha e, em caso de empate, pelas coordenadas da coluna.

