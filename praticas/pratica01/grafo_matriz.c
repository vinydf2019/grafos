#include <stdio.h>
#include <stdlib.h>
#include "grafo_matriz.h"

// 1. Cria o grafo e aloca a matriz g->n x g->n preenchida com 0
GrafoMatriz* criar_grafo_matriz(int n) {
    GrafoMatriz *g = (GrafoMatriz*) malloc(sizeof(GrafoMatriz));
    if (g == NULL) return NULL;

    g->n = n;
    
    // Aloca o vetor de ponteiros das linhas
    g->adj = (int**) malloc(n * sizeof(int*));
    if (g->adj == NULL) {
        free(g);
        return NULL;
    }

    // Aloca as colunas de cada linha e inicializa com 0 (sem arestas)
    for (int i = 0; i < n; i++) {
        g->adj[i] = (int*) calloc(n, sizeof(int));
    }

    return g;
}

// 2. Insere uma aresta entre u e v (Grafo não-direcionado)
void inserir_aresta_matriz(GrafoMatriz *g, int u, int v) {
    if (g != NULL && u >= 0 && u < g->n && v >= 0 && v < g->n) {
        g->adj[u][v] = 1;
        g->adj[v][u] = 1; // Espelhamento por ser não-direcionado
    }
}

// 3. Remove a aresta entre u e v
void remover_aresta_matriz(GrafoMatriz *g, int u, int v) {
    if (g != NULL && u >= 0 && u < g->n && v >= 0 && v < g->n) {
        g->adj[u][v] = 0;
        g->adj[v][u] = 0;
    }
}

// 4. Conta quantas arestas saem ou chegam no vértice v
int grau_matriz(GrafoMatriz *g, int v) {
    if (g == NULL || v < 0 || v >= g->n) return 0;

    int grau = 0;
    for (int i = 0; i < g->n; i++) {
        if (g->adj[v][i] == 1) {
            grau++;
        }
    }
    return grau;
}

// 5. Verifica se existe conexão direta entre u e v
int sao_adjacentes_matriz(GrafoMatriz *g, int u, int v) {
    if (g != NULL && u >= 0 && u < g->n && v >= 0 && v < g->n) {
        return g->adj[u][v];
    }
    return 0;
}

// 6. Desaloca toda a memória da matriz e da struct
void liberar_grafo_matriz(GrafoMatriz *g) {
    if (g != NULL) {
        for (int i = 0; i < g->n; i++) {
            free(g->adj[i]); // Libera cada linha
        }
        free(g->adj); // Libera o vetor de ponteiros
        free(g);     // Libera a estrutura principal
    }
}
