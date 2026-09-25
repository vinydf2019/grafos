#include <stdio.h>
#include <stdlib.h>
#include "grafo_lista.h"

// 1. Cria o grafo alocando o vetor de ponteiros e iniciando cada lista como NULL
GrafoLista* criar_grafo_lista(int n) {
    GrafoLista *g = (GrafoLista*) malloc(sizeof(GrafoLista));
    if (g == NULL) return NULL;

    g->n = n;
    
    // Aloca o vetor que guardará os ponteiros para a cabeça de cada lista encadeada
    g->adj = (No**) malloc(n * sizeof(No*));
    if (g->adj == NULL) {
        free(g);
        return NULL;
    }

    // Inicializa todas as listas como vazias (NULL)
    for (int i = 0; i < n; i++) {
        g->adj[i] = NULL;
    }

    return g;
}

// Auxiliar: Aloca um novo nó da lista encadeada
No* criar_no(int destino) {
    No *novo = (No*) malloc(sizeof(No));
    if (novo != NULL) {
        novo->destino = destino;
        novo->prox = NULL;
    }
    return novo;
}

// 2. Insere uma aresta entre u e v inserindo no início de ambas as listas (Simetria)
void inserir_aresta_lista(GrafoLista *g, int u, int v) {
    if (g == NULL || u < 0 || u >= g->n || v < 0 || v >= g->n) return;

    // Evita a inserção de duplicatas (opcional, dependendo do rigor do corretor)
    if (sao_adjacentes_lista(g, u, v)) return;

    // Insere v na lista de u
    No *novo_u = criar_no(v);
    if (novo_u != NULL) {
        novo_u->prox = g->adj[u];
        g->adj[u] = novo_u;
    }

    // Insere u na lista de v
    No *novo_v = criar_no(u);
    if (novo_v != NULL) {
        novo_v->prox = g->adj[v];
        g->adj[v] = novo_v;
    }
}

// 3. Remove a aresta removendo o nó correspondente de ambas as listas
void remover_aresta_lista(GrafoLista *g, int u, int v) {
    if (g == NULL || u < 0 || u >= g->n || v < 0 || v >= g->n) return;

    // Auxiliar para remover de uma lista específica de forma genérica
    void remover_da_lista(No **cabeca, int destino) {
        No *atual = *cabeca;
        No *anterior = NULL;

        while (atual != NULL && atual->destino != destino) {
            anterior = atual;
            atual = atual->prox;
        }

        if (atual != NULL) { // Achou o nó
            if (anterior == NULL) {
                *cabeca = atual->prox; // Removendo o primeiro nó
            } else {
                anterior->prox = atual->prox; // Removendo do meio ou fim
            }
            free(atual);
        }
    }

    remover_da_lista(&(g->adj[u]), v);
    remover_da_lista(&(g->adj[v]), u);
}

// 4. Conta quantos nós existem na lista do vértice v
int grau_lista(GrafoLista *g, int v) {
    if (g == NULL || v < 0 || v >= g->n) return 0;

    int grau = 0;
    No *atual = g->adj[v];
    while (atual != NULL) {
        grau++;
        atual = atual->prox;
    }
    return grau;
}

// 5. Varre a lista do vértice u procurando se o destino v está lá
int sao_adjacentes_lista(GrafoLista *g, int u, int v) {
    if (g == NULL || u < 0 || u >= g->n || v < 0 || v >= g->n) return 0;

    No *atual = g->adj[u];
    while (atual != NULL) {
        if (atual->destino == v) {
            return 1; // Encontrou a conexão
        }
        atual = atual->prox;
    }
    return 0;
}

// 6. Desaloca todos os nós de todas as listas, o vetor e a struct
void liberar_grafo_lista(GrafoLista *g) {
    if (g != NULL) {
        for (int i = 0; i < g->n; i++) {
            No *atual = g->adj[i];
            while (atual != NULL) {
                No *aux = atual;
                atual = atual->prox;
                free(aux); // Libera cada nó individualmente
            }
        }
        free(g->adj); // Libera o vetor de ponteiros
        free(g);     // Libera a estrutura do grafo
    }
}
