#include <stdio.h>
#include <stdlib.h>
#include "dijkstra.h"

GrafoListaPonderado* criar_grafo(int n) {
    GrafoListaPonderado *g = (GrafoListaPonderado*)malloc(sizeof(GrafoListaPonderado));
    g->num_vertices = n;
    g->num_arestas = 0;
    g->lista = (NoAresta**)malloc(n * sizeof(NoAresta*));
    for (int i = 0; i < n; i++) {
        g->lista[i] = NULL;
    }
    return g;
}

void adicionar_aresta(GrafoListaPonderado *g, int u, int v, int peso) {
    NoAresta *novo = (NoAresta*)malloc(sizeof(NoAresta));
    novo->vertice = v;
    novo->peso = peso;
    novo->prox = g->lista[u];
    g->lista[u] = novo;

    novo = (NoAresta*)malloc(sizeof(NoAresta));
    novo->vertice = u;
    novo->peso = peso;
    novo->prox = g->lista[v];
    g->lista[v] = novo;

    g->num_arestas++;
}

void liberar_grafo(GrafoListaPonderado *g) {
    if (!g) return;
    for (int i = 0; i < g->num_vertices; i++) {
        NoAresta *atual = g->lista[i];
        while (atual) {
            NoAresta *temp = atual;
            atual = atual->prox;
            free(temp);
        }
    }
    free(g->lista);
    free(g);
}

MinHeap* criar_min_heap(int capacidade) {
    MinHeap *min_heap = (MinHeap*)malloc(sizeof(MinHeap));
    min_heap->capacidade = capacidade;
    min_heap->tamanho = 0;
    min_heap->dados = (NoHeap*)malloc(capacidade * sizeof(NoHeap));
    min_heap->posicao = (int*)malloc(capacidade * sizeof(int));
    for (int i = 0; i < capacidade; i++) {
        min_heap->posicao[i] = -1;
    }
    return min_heap;
}

void liberar_min_heap(MinHeap *min_heap) {
    if (!min_heap) return;
    free(min_heap->dados);
    free(min_heap->posicao);
    free(min_heap);
}

static void trocar_no_heap(MinHeap *min_heap, int i, int j) {
    NoHeap temp = min_heap->dados[i];
    min_heap->dados[i] = min_heap->dados[j];
    min_heap->dados[j] = temp;

    min_heap->posicao[min_heap->dados[i].vertice] = i;
    min_heap->posicao[min_heap->dados[j].vertice] = j;
}

static void min_heapify(MinHeap *min_heap, int idx) {
    int menor = idx;
    int esq = 2 * idx + 1;
    int dir = 2 * idx + 2;

    if (esq < min_heap->tamanho && min_heap->dados[esq].distancia < min_heap->dados[menor].distancia) {
        menor = esq;
    }

    if (dir < min_heap->tamanho && min_heap->dados[dir].distancia < min_heap->dados[menor].distancia) {
        menor = dir;
    }

    if (menor != idx) {
        trocar_no_heap(min_heap, idx, menor);
        min_heapify(min_heap, menor);
    }
}

int esta_no_min_heap(MinHeap *min_heap, int v) {
    return min_heap->posicao[v] < min_heap->tamanho && min_heap->posicao[v] != -1;
}

NoHeap extrair_minimo(MinHeap *min_heap) {
    if (min_heap->tamanho == 0) {
        NoHeap no_vazio = {-1, -1};
        return no_vazio;
    }

    NoHeap raiz = min_heap->dados[0];
    NoHeap ultimo_no = min_heap->dados[min_heap->tamanho - 1];

    min_heap->dados[0] = ultimo_no;
    min_heap->posicao[raiz.vertice] = min_heap->tamanho - 1;
    min_heap->posicao[ultimo_no.vertice] = 0;

    min_heap->tamanho--;
    min_heapify(min_heap, 0);

    return raiz;
}

void diminuir_chave(MinHeap *min_heap, int v, int distancia) {
    int i = min_heap->posicao[v];
    min_heap->dados[i].distancia = distancia;

    while (i > 0 && min_heap->dados[i].distancia < min_heap->dados[(i - 1) / 2].distancia) {
        trocar_no_heap(min_heap, i, (i - 1) / 2);
        i = (i - 1) / 2;
    }
}

void dijkstra(GrafoListaPonderado *g, int origem, int *dist, int *pred) {
    int n = g->num_vertices;
    MinHeap *min_heap = criar_min_heap(n);

    for (int v = 0; v < n; v++) {
        dist[v] = INF;
        pred[v] = -1;
        min_heap->dados[v].vertice = v;
        min_heap->dados[v].distancia = dist[v];
        min_heap->posicao[v] = v;
    }

    dist[origem] = 0;
    min_heap->dados[origem].distancia = 0;
    min_heap->tamanho = n;

    diminuir_chave(min_heap, origem, 0);

    while (min_heap->tamanho > 0) {
        NoHeap min_no = extrair_minimo(min_heap);
        int u = min_no.vertice;

        if (dist[u] == INF) break;

        for (NoAresta *p = g->lista[u]; p != NULL; p = p->prox) {
            int v = p->vertice;
            int peso = p->peso;

            if (esta_no_min_heap(min_heap, v) && dist[u] + peso < dist[v]) {
                dist[v] = dist[u] + peso;
                pred[v] = u;
                diminuir_chave(min_heap, v, dist[v]);
            }
        }
    }

    liberar_min_heap(min_heap);
}

void reconstruir_caminho(int origem, int destino, int *pred) {
    if (destino == origem) {
        printf("%d", origem);
        return;
    }
    if (pred[destino] == -1) {
        printf("Sem caminho");
        return;
    }
    reconstruir_caminho(origem, pred[destino], pred);
    printf(" -> %d", destino);
}
