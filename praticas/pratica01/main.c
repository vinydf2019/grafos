#include <stdio.h>
#include <stdlib.h>
#include "grafo_matriz.h"
#include "grafo_lista.h"

int main() {
    int n = 5; // Grafo com 5 vértices (0 a 4)

    printf("=== TESTANDO MATRIZ DE ADJACENCIA ===\n");
    GrafoMatriz *gm = criar_grafo_matriz(n);
    if (gm != NULL) {
        inserir_aresta_matriz(gm, 0, 1);
        inserir_aresta_matriz(gm, 0, 4);
        inserir_aresta_matriz(gm, 1, 2);
        inserir_aresta_matriz(gm, 1, 3);
        inserir_aresta_matriz(gm, 1, 4);
        inserir_aresta_matriz(gm, 2, 3);
        inserir_aresta_matriz(gm, 3, 4);

        printf("Grau do vertice 1 (Matriz): %d (Esperado: 4)\n", grau_matriz(gm, 1));
        printf("0 e 2 sao adjacentes? %s (Esperado: Nao)\n", sao_adjacentes_matriz(gm, 0, 2) ? "Sim" : "Nao");

        remover_aresta_matriz(gm, 1, 4);
        printf("Apos remover aresta (1,4), grau do vertice 1: %d (Esperado: 3)\n", grau_matriz(gm, 1));

        liberar_grafo_matriz(gm);
        printf("Memoria da matriz liberada com sucesso.\n\n");
    }

    printf("=== TESTANDO LISTA DE ADJACENCIA ===\n");
    GrafoLista *gl = criar_grafo_lista(n);
    if (gl != NULL) {
        inserir_aresta_lista(gl, 0, 1);
        inserir_aresta_lista(gl, 0, 4);
        inserir_aresta_lista(gl, 1, 2);
        inserir_aresta_lista(gl, 1, 3);
        inserir_aresta_lista(gl, 1, 4);
        inserir_aresta_lista(gl, 2, 3);
        inserir_aresta_lista(gl, 3, 4);

        printf("Grau do vertice 1 (Lista): %d (Esperado: 4)\n", grau_lista(gl, 1));
        printf("0 e 2 sao adjacentes? %s (Esperado: Nao)\n", sao_adjacentes_lista(gl, 0, 2) ? "Sim" : "Nao");

        remover_aresta_lista(gl, 1, 4);
        printf("Apos remover aresta (1,4), grau do vertice 1: %d (Esperado: 3)\n", grau_lista(gl, 1));

        liberar_grafo_lista(gl);
        printf("Memoria da lista liberada com sucesso.\n");
    }

    return 0;
}
