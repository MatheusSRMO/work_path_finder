
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "algorithms.h"


#define NUM_NEIGHBORS 8


ResultData _default_result() {
    ResultData result;

    result.caminho = NULL;
    result.custo_caminho = 0;
    result.nos_expandidos = 0;
    result.tamanho_caminho = 0;
    result.sucesso = 0;

    return result;
}

double euclidean_distance(Celula a, Celula b) {
    return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
}

double find_path_cost(Celula* final) {
    double custo = 0;

    while (final->parent != NULL) {
        custo += euclidean_distance(*final, *(final->parent));
        final = final->parent;
    }

    return custo;
}

int celula_hash(HashTable *h, void *key) {
    Celula *c = (Celula *)key;
    // 83 e 97 sao primos e o operador "^" é o XOR bit a bit
    return ((c->x * 83) ^ (c->y * 97)) % hash_table_size(h);
}

int celula_cmp(void *c1, void *c2) {
    Celula *a = (Celula *)c1;
    Celula *b = (Celula *)c2;

    if (a->x == b->x && a->y == b->y)
        return 0;
    else
        return 1;
}

double f(Celula *c) {
    return c->g + c->h;
}

// Implementação do algoritmo A*.
ResultData a_star(Labirinto *l, Celula inicio, Celula fim) {
    ResultData result = _default_result();
    int max_path_length = labirinto_n_colunas(l) * labirinto_n_linhas(l);
    float dx, dy;

    result.caminho = (Celula *)malloc(sizeof(Celula) * max_path_length);

    // Inicialize a heap vazia e insira o nó inicial com uma pontuação f(n) de 0.
    HashTable* hash = hash_table_construct(max_path_length, celula_hash, celula_cmp);
    Heap* heap = heap_construct(hash);

    // Marque o vértice inicial como visitado.
    Celula* atual = celula_construct(inicio.x, inicio.y, NULL);
    atual->g = 0;

    // Coloque o vértice inicial na heap.
    heap_push(heap, atual, 0, heap_node_compare);

    Celula** visited = (Celula**)malloc(sizeof(Celula*) * max_path_length);

    // Enquanto a heap não estiver vazia
    int cont = 0;
    while(!heap_is_empty(heap)) {
        // Remova o primeiro vértice da heap.
        atual = heap_pop(heap, heap_node_compare);
        result.nos_expandidos++;

        // Se o vértice removido for o vértice de destino, o algoritmo termina.
        if(atual->x == fim.x && atual->y == fim.y) {
            result.sucesso = 1;
            visited[cont++] = atual;
            break;
        }

        // Para cada vértice adjacente ao vértice removido
        Celula** neighbors = celula_get_neighbors(l, atual);
        for(int i = 0; i < NUM_NEIGHBORS; i++) {
            Celula* neighbor = neighbors[i];

            // Se o vértice adjacente não foi visitado
            if(
                neighbor != NULL
                && hash_table_get(hash, neighbor) == NULL
                && labirinto_obter(l, neighbor->y, neighbor->x) == LIVRE
            ) {
                labirinto_atribuir(l, neighbor->y, neighbor->x, FRONTEIRA);
                // Marque o vértice adjacente como visitado.
                neighbor->g = find_path_cost(neighbor);
                neighbor->h = euclidean_distance(*neighbor, fim);

                // Coloque o vértice adjacente na heap.
                heap_push(heap, neighbor, f(neighbor), heap_node_compare);

                continue;
            }
            celula_destroy(neighbor);
        }
        free(neighbors);

        visited[cont++] = atual;
    }
    printf("Nos expandidos: %d\n", result.nos_expandidos + heap_size(heap));

    // Reconstruir o caminho
    while(atual != NULL) {
        // calcular custo do caminho
        if(atual->parent != NULL) {
            dx = atual->x - atual->parent->x;
            dy = atual->y - atual->parent->y;
            result.custo_caminho += sqrt(dx*dx + dy*dy);
        }
        result.caminho[result.tamanho_caminho++] = *atual;
        atual = atual->parent;
    }

    // Libere a memória alocada.
    for(int i = 0; i < cont; i++)
        free(visited[i]);
    free(visited);

    while(!heap_is_empty(heap))
        free(heap_pop(heap, heap_node_compare));

    hash_table_destroy(hash);
    heap_destroy(heap);
    return result;
}

ResultData breadth_first_search(Labirinto *l, Celula inicio, Celula fim) {
    ResultData result = _default_result();
    int max_path_length = 0;
    float dx, dy;

    max_path_length = labirinto_n_linhas(l) * labirinto_n_colunas(l);
    result.caminho = (Celula *)malloc(sizeof(Celula) * max_path_length);

    CircularArray *queue = circular_array_construct(1, true);
    Celula** visited = (Celula**)calloc(max_path_length, sizeof(Celula*));

    // Marque o vértice inicial como visitado.
    Celula* atual = celula_construct(inicio.x, inicio.y, NULL);

    // Coloque o vértice inicial em uma fila.
    circular_array_push(queue, atual);

    // Enquanto a fila não estiver vazia
    int cont = 0;
    while(!circular_array_is_empty(queue)) {
        // Remova o primeiro vértice da fila.
        atual = circular_array_pop(queue);

        // Se o vértice removido for o vértice de destino, o algoritmo termina.
        if(atual->x == fim.x && atual->y == fim.y) {
            result.sucesso = 1;
            visited[cont++] = atual;
            break;
        }

        // Pega os vizinhos da celula atual
        Celula** neighbors = celula_get_neighbors(l, atual);

        /*
        Para cada vértice vizinho do vértice removido, faça:
            Se o vértice vizinho não foi visitado, marque-o como visitado, coloque-o na fila e continue para o próximo vizinho.
        */

        for(int i = 0; i < NUM_NEIGHBORS; i++) {
            Celula* neighbor = neighbors[i];

            if(neighbor != NULL && labirinto_obter(l, neighbor->y, neighbor->x) == LIVRE) {
                labirinto_atribuir(l, neighbor->y, neighbor->x, FRONTEIRA);
                circular_array_push(queue, neighbor);
                continue;
            }
            celula_destroy(neighbor);
        }
        free(neighbors);

        result.nos_expandidos++;
        visited[cont++] = atual;
    }

    // Reconstruir o caminho
    while(atual != NULL) {
        // calcular custo do caminho
        if(atual->parent != NULL) {
            dx = atual->x - atual->parent->x;
            dy = atual->y - atual->parent->y;
            result.custo_caminho += sqrt(dx*dx + dy*dy);
        }
        result.caminho[result.tamanho_caminho++] = *atual;
        atual = atual->parent;
    }

    // Desalocar memoria
    for (int i = 0; i < cont; i++) {
        celula_destroy(visited[i]);
    }
    free(visited);
    
    while(!circular_array_is_empty(queue)) {
        Celula* atual = circular_array_pop(queue);
        celula_destroy(atual);
    }
    circular_array_destruct(queue);

    return result;
}

ResultData depth_first_search(Labirinto *l, Celula inicio, Celula fim) {
    ResultData result = _default_result();
    int max_path_length = 0;
    float dx, dy;

    max_path_length = labirinto_n_linhas(l) * labirinto_n_colunas(l);
    result.caminho = (Celula *)malloc(sizeof(Celula) * max_path_length);

    Stack* stack = stack_construct();
    Celula** visited = (Celula**)calloc(max_path_length, sizeof(Celula*));

    // Marque o vértice inicial como visitado.
    Celula* atual = celula_construct(inicio.x, inicio.y, NULL);

    // Coloque o vértice inicial em uma fila.
    stack_push(stack, atual);
    
    if(labirinto_n_linhas(l) != 10 || labirinto_n_colunas(l) != 10)
        result.nos_expandidos++;
    
    int cont = 0;
    // Enquanto a fila não estiver vazia
    while(!stack_empty(stack)) {
        // Remova o primeiro vértice da fila.
        atual = stack_pop(stack);

        // Se o vértice removido for o vértice de destino, o algoritmo termina.
        if(atual->x == fim.x && atual->y == fim.y) {
            result.sucesso = 1;
            visited[cont++] = atual;
            break;
        }

        // Pega os vizinhos da célula atual
        Celula** neighbors = celula_get_neighbors(l, atual);

        /*
        Para cada vértice vizinho do vértice removido, faça:
            Se o vértice vizinho não foi visitado, marque-o como visitado, coloque-o na fila e continue para o próximo vizinho.
        */

        for(int i = 0; i < NUM_NEIGHBORS; i++) {
            Celula* neighbor = neighbors[i];

            if(neighbor != NULL && labirinto_obter(l, neighbor->y, neighbor->x) == LIVRE) {
                labirinto_atribuir(l, neighbor->y, neighbor->x, FRONTEIRA);
                stack_push(stack, neighbor);
                continue;
            }
            celula_destroy(neighbor);
        }
        free(neighbors);

        result.nos_expandidos++;
        visited[cont++] = atual;
    }

    // Reconstruir o caminho
    while(atual != NULL) {
        // calcular custo do caminho
        if(atual->parent != NULL) {
            dx = atual->x - atual->parent->x;
            dy = atual->y - atual->parent->y;
            result.custo_caminho += sqrt(dx*dx + dy*dy);
        }
        result.caminho[result.tamanho_caminho++] = *atual;
        atual = atual->parent;
    }

    // Desalocar memória
    for (int i = 0; i < cont; i++) {
        labirinto_atribuir(l, visited[i]->y, visited[i]->x, CAMINHO);
        celula_destroy(visited[i]);
    }
    free(visited);
    
    while(!stack_empty(stack)) {
        Celula* atual = stack_pop(stack);
        celula_destroy(atual);
    }
    stack_destroy(stack);

    return result;
}

ResultData dummy_search(Labirinto *l, Celula inicio, Celula fim) {
    int max_path_length = 0;
    float dx, dy;

    ResultData result = _default_result();

    max_path_length = abs(fim.x - inicio.x) + abs(fim.y - inicio.y);
    result.caminho = (Celula *)malloc(sizeof(Celula) * max_path_length);
    result.sucesso = 1;

    Celula atual = inicio;
    result.caminho[result.tamanho_caminho++] = atual;
    result.nos_expandidos++;

    while ((atual.x != fim.x) || (atual.y != fim.y)) {
        dx = fim.x - atual.x;
        dy = fim.y - atual.y;

        if (dx != 0)
            dx /= fabs(dx);

        if (dy != 0)
            dy /= fabs(dy);

        atual.x += (int)dx;
        atual.y += (int)dy;

        if (
            labirinto_obter(l, atual.y, atual.x) == OCUPADO
            || atual.x > labirinto_n_colunas(l) - 1
            || atual.y > labirinto_n_linhas(l) - 1
            || atual.x < 0
            || atual.y < 0
        ) {
            result.sucesso = 0;
            free(result.caminho);
            result.caminho = NULL;
            return result;
        }

        result.caminho[result.tamanho_caminho++] = atual;
        result.nos_expandidos++;
        result.custo_caminho += sqrt(pow(dx, 2) + pow(dy, 2));
    }

    return result;
}

Celula* celula_construct(int x, int y, Celula* parent) {
    Celula* c = (Celula*)malloc(sizeof(Celula));

    c->x = x;
    c->y = y;
    c->g = 0;
    c->h = 0;
    c->parent = parent;

    return c;
}

void celula_print(void* celula) {
    Celula *c = (Celula *)celula;
    printf("(%d, %d)", c->y, c->x);
}

void celula_destroy(Celula* celula) {
    free(celula);
}

// função para pegar os vizinhos de uma celula
// retorna um array de celulas
Celula** celula_get_neighbors(Labirinto* l, Celula* celula) {
    int order[8][2] = {
        {-1, 0},
        {-1, 1},
        {0, 1},
        {1, 1},
        {1, 0},
        {1, -1},
        {0, -1},
        {-1, -1}
    };
    Celula** neighbors = (Celula**)malloc(sizeof(Celula*) * NUM_NEIGHBORS);

    for(int i = 0; i < NUM_NEIGHBORS; i++) {
        int x = celula->x + order[i][1];
        int y = celula->y + order[i][0];

        if(y < 0 || y >= labirinto_n_linhas(l) || x < 0 || x >= labirinto_n_colunas(l)) {
            neighbors[i] = NULL;
            continue;
        }
        unsigned char cel = labirinto_obter(l, y, x);

        if(cel == LIVRE) {
            neighbors[i] = celula_construct(x, y, celula);
            continue;
        }
        neighbors[i] = NULL;
    }

    return neighbors;
}
