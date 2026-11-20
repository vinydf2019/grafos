#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "dijkstra.h"

int main()
{
    int n = 5;
    int origem = 0;
    int destino = 4;

    GrafoListaPonderado *g = criar_grafo_ponderado(n);

    if (g == NULL)
    {
        printf("Erro ao criar o grafo.\n");
        return 1;
    }

    // Adicionando arestas e seus pesos
    adicionar_aresta_ponderada(g, 0, 1, 10);
    adicionar_aresta_ponderada(g, 0, 2, 3);
    adicionar_aresta_ponderada(g, 1, 2, 1);
    adicionar_aresta_ponderada(g, 1, 3, 2);
    adicionar_aresta_ponderada(g, 2, 3, 8);
    adicionar_aresta_ponderada(g, 2, 4, 2);
    adicionar_aresta_ponderada(g, 3, 4, 7);

    int dist[n];
    int pred[n];

    dijkstra(g, origem, dist, pred);

    printf("Distancias minimas a partir do vertice %d:\n", origem);

    for (int i = 0; i < n; i++)
    {
        if (dist[i] == INT_MAX)
            printf("Vertice %d: Inalcancavel\n", i);
        else
            printf("Vertice %d: %d\n", i, dist[i]);
    }

    printf("\nCaminho de %d ate %d:\n", origem, destino);
    reconstruir_caminho(origem, destino, pred);

    return 0;
}