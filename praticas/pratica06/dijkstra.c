#include "dijkstra.h"
#include <limits.h>

void descer_no_heap(MinHeap *heap, int i);
GrafoListaPonderado *criar_grafo_ponderado(int n)
{
    GrafoListaPonderado *g = malloc(sizeof(GrafoListaPonderado));

    if (g == NULL)
        return NULL;

    g->num_vertices = n;
    g->lista = malloc(n * sizeof(NoPonderado *));

    if (g->lista == NULL)
    {
        free(g);
        return NULL;
    }

    for (int i = 0; i < n; i++)
    {
        g->lista[i] = NULL;
    }

    return g;
}
void adicionar_arco_ponderado(GrafoListaPonderado *g, int u, int v, int peso)
{
    if (g == NULL || u < 0 || u >= g->num_vertices ||
        v < 0 || v >= g->num_vertices || peso < 0)
        return;

    NoPonderado *no = malloc(sizeof(NoPonderado));

    if (no == NULL)
        return;

    no->vertice = v;
    no->peso = peso;
    no->proximo = g->lista[u];
    g->lista[u] = no;
}

void adicionar_aresta_ponderada(GrafoListaPonderado *g, int u, int v, int peso)
{
    if (g == NULL || u < 0 || u >= g->num_vertices ||
        v < 0 || v >= g->num_vertices || peso < 0)
        return;

    adicionar_arco_ponderado(g, u, v, peso);
    adicionar_arco_ponderado(g, v, u, peso);
}
void trocar(MinHeap *heap, int i, int j)
{
    NoHeap temp = heap->dados[i];
    heap->dados[i] = heap->dados[j];
    heap->dados[j] = temp;

    heap->posicao[heap->dados[i].vertice] = i;
    heap->posicao[heap->dados[j].vertice] = j;
}
MinHeap *criar_min_heap(int capacidade)
{
    MinHeap *heap = malloc(sizeof(MinHeap));

    if (heap == NULL)
        return NULL;

    heap->capacidade = capacidade;
    heap->tamanho = 0;

    heap->dados = malloc(capacidade * sizeof(NoHeap));
    heap->posicao = malloc(capacidade * sizeof(int));

    if (heap->dados == NULL || heap->posicao == NULL)
    {
        free(heap->dados);
        free(heap->posicao);
        free(heap);
        return NULL;
    }

    for (int i = 0; i < capacidade; i++)
    {
        heap->posicao[i] = -1;
    }

    return heap;
}
void subir_no_heap(MinHeap *heap, int i)
{
    while (i > 0)
    {
        int pai = (i - 1) / 2;

        if (heap->dados[i].distancia < heap->dados[pai].distancia)
        {
            trocar(heap, i, pai);
            i = pai;
        }
        else
        {
            break;
        }
    }
}
void diminuir_chave(MinHeap *heap, int vertice, int nova_distancia)
{
    int i = heap->posicao[vertice];

    if (i == -1)
        return;

    if (nova_distancia >= heap->dados[i].distancia)
        return;

    heap->dados[i].distancia = nova_distancia;

    subir_no_heap(heap, i);
}
NoHeap extrair_minimo(MinHeap *heap)
{
    NoHeap minimo = heap->dados[0];
    NoHeap ultimo = heap->dados[heap->tamanho - 1];

    heap->dados[0] = ultimo;

    heap->posicao[ultimo.vertice] = 0;
    heap->posicao[minimo.vertice] = -1;

    heap->tamanho--;

    descer_no_heap(heap, 0);

    return minimo;
}
void descer_no_heap(MinHeap *heap, int i)
{
    int menor = i;
    int esquerdo = 2 * i + 1;
    int direito = 2 * i + 2;

    if (esquerdo < heap->tamanho &&
        heap->dados[esquerdo].distancia < heap->dados[menor].distancia)
    {
        menor = esquerdo;
    }

    if (direito < heap->tamanho &&
        heap->dados[direito].distancia < heap->dados[menor].distancia)
    {
        menor = direito;
    }

    if (menor != i)
    {
        trocar(heap, i, menor);
        descer_no_heap(heap, menor);
    }
}
void dijkstra(GrafoListaPonderado *g, int origem, int *dist, int *pred)
{
    if (g == NULL || dist == NULL || pred == NULL ||
        origem < 0 || origem >= g->num_vertices)
        return;

    int n = g->num_vertices;

    MinHeap *heap = criar_min_heap(n);

    if (heap == NULL)
        return;

    // Inicializa as distâncias e os predecessores
    for (int i = 0; i < n; i++)
    {
        dist[i] = INT_MAX;
        pred[i] = -1;

        heap->dados[i].vertice = i;
        heap->dados[i].distancia = INT_MAX;
        heap->posicao[i] = i;
    }

    // A distância da origem é zero
    dist[origem] = 0;
    heap->dados[origem].distancia = 0;

    heap->tamanho = n;

    // Processa os vértices
    while (heap->tamanho > 0)
    {
        NoHeap atual = extrair_minimo(heap);
        int u = atual.vertice;

        if (dist[u] == INT_MAX)
            break;

        NoPonderado *no = g->lista[u];

        while (no != NULL)
        {
            int v = no->vertice;
            int peso = no->peso;

            if (heap->posicao[v] != -1 &&
                dist[u] <= INT_MAX - peso &&
                dist[u] + peso < dist[v])
            {
                dist[v] = dist[u] + peso;
                pred[v] = u;

                diminuir_chave(heap, v, dist[v]);
            }

            no = no->proximo;
        }
    }

    free(heap->dados);
    free(heap->posicao);
    free(heap);
}
void reconstruir_caminho(int origem, int destino, int *pred)
{
    if (origem == destino)
    {
        printf("%d\n", origem);
        return;
    }

    if (pred[destino] == -1)
    {
        printf("Nao existe caminho entre %d e %d.\n", origem, destino);
        return;
    }

    reconstruir_caminho(origem, pred[destino], pred);

    printf("%d\n", destino);
}