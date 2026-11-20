#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include <stdio.h>
#include <stdlib.h>

typedef struct NoPonderadoNode
{
    int vertice;
    int peso;
    struct NoPonderadoNode *proximo;
} NoPonderado;

typedef struct
{
    NoPonderado **lista;
    int num_vertices;
} GrafoListaPonderado;
typedef struct
{
    int vertice;
    int distancia;
} NoHeap;

typedef struct
{
    NoHeap *dados;
    int capacidade, tamanho;
    int *posicao;
} MinHeap;
// Funções do grafo ponderado
GrafoListaPonderado *criar_grafo_ponderado(int n);
void adicionar_aresta_ponderada(GrafoListaPonderado *g, int u, int v, int peso);
void adicionar_arco_ponderado(GrafoListaPonderado *g, int u, int v, int peso);

// Funções do Min-Heap
MinHeap *criar_min_heap(int capacidade);
NoHeap extrair_minimo(MinHeap *heap);
void diminuir_chave(MinHeap *heap, int vertice, int nova_distancia);

// Algoritmo de Dijkstra e reconstrução do caminho
void dijkstra(GrafoListaPonderado *g, int origem, int *dist, int *pred);
void reconstruir_caminho(int origem, int destino, int *pred);


#endif