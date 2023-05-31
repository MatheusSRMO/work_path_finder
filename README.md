# Implementação de Algoritmos de Busca em Labirinto

Este projeto consiste na implementação dos algoritmos de busca em labirinto: Busca em Profundidade (DFS), Busca em Largura (BFS) e Busca A* (A Star). Os algoritmos de busca em largura e profundidade são implementados sem recursão, utilizando filas e pilhas implementadas com a estrutura de dados deque. Já o algoritmo de busca A* utiliza a estrutura de dados heap e uma tabela hash para atualização eficiente das prioridades.

O labirinto é representado por uma matriz densa, onde cada célula pode ser livre (valor 0) ou ocupada (valor 1). A entrada do programa é fornecida pelo usuário e inclui:

- Nome do arquivo contendo o labirinto
- Coordenadas (linha e coluna) da célula de entrada
- Coordenadas da célula de saída
- Algoritmo a ser utilizado (BFS, DFS ou A*)
- Nome do arquivo de saída

O programa exibe na tela:
- A sequência de células que levam o agente da entrada para a saída, ou uma mensagem indicando que o labirinto é impossível
- O custo total do caminho com 2 casas decimais após a vírgula
- O número de nós no caminho
- O número de nós expandidos

## Formato do Arquivo do Labirinto

O labirinto é armazenado em um arquivo binário com o seguinte formato:

- Os primeiros 8 bytes contêm 2 inteiros, L e C, representando o número de linhas e colunas do labirinto.
- Cada célula é representada por um unsigned char (1 byte) com valor 0 se a célula for livre e 1 se for ocupada.
- As linhas são escritas em sequência no arquivo binário. Após os 2 inteiros iniciais, os próximos C bytes correspondem ao conteúdo da primeira linha, seguidos pelos próximos C bytes correspondendo ao conteúdo da segunda linha, e assim por diante.
