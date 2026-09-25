#ifndef GRAFO_MATRIZ_H
#define GRAFO_MATRIZ_H

// Estrutura obrigatória para Matriz de Adjacência
typedef struct {
    int n;       // Número de vértices
    int **adj;   // Matriz bidimensional alocada dinamicamente
} GrafoMatriz;

// Operações obrigatórias a implementar
GrafoMatriz* criar_grafo_matriz(int n);
void inserir_aresta_matriz(GrafoMatriz *g, int u, int v);
void remover_aresta_matriz(GrafoMatriz *g, int u, int v);
int grau_matriz(GrafoMatriz *g, int v);
int sao_adjacentes_matriz(GrafoMatriz *g, int u, int v);
void liberar_grafo_matriz(GrafoMatriz *g);

#endif // GRAFO_MATRIZ_H
