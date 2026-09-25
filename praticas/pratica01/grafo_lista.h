#ifndef GRAFO_LISTA_H
#define GRAFO_LISTA_H

// Estruturas obrigatórias para Lista de Adjacência
typedef struct No {
    int destino;
    struct No *prox;
} No;

typedef struct {
    int n;       // Número de vértices
    No **adj;    // Vetor de ponteiros para nós (lista encadeada)
} GrafoLista;

// Operações obrigatórias a implementar
GrafoLista* criar_grafo_lista(int n);
void inserir_aresta_lista(GrafoLista *g, int u, int v);
void remover_aresta_lista(GrafoLista *g, int u, int v);
int grau_lista(GrafoLista *g, int v);
int sao_adjacentes_lista(GrafoLista *g, int u, int v);
void liberar_grafo_lista(GrafoLista *g);

#endif // GRAFO_LISTA_H
