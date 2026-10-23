#include <stdio.h>
#include <stdlib.h>
#include "agm.h"

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

DSU* criar_dsu(int n) {
    DSU *d = (DSU*)malloc(sizeof(DSU));
    d->n = n;
    d->pai = (int*)malloc(n * sizeof(int));
    d->rank = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        d->pai[i] = i;
        d->rank[i] = 0;
    }
    return d;
}

void liberar_dsu(DSU *d) {
    if (!d) return;
    free(d->pai);
    free(d->rank);
    free(d);
}

int find(DSU *d, int x) {
    if (d->pai[x] != x) {
        d->pai[x] = find(d, d->pai[x]);
    }
    return d->pai[x];
}

int unir(DSU *d, int x, int y) {
    int raiz_x = find(d, x);
    int raiz_y = find(d, y);

    if (raiz_x != raiz_y) {
        if (d->rank[raiz_x] < d->rank[raiz_y]) {
            d->pai[raiz_x] = raiz_y;
        } else if (d->rank[raiz_x] > d->rank[raiz_y]) {
            d->pai[raiz_y] = raiz_x;
        } else {
            d->pai[raiz_y] = raiz_x;
            d->rank[raiz_x]++;
        }
        return 1;
    }
    return 0;
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

    if (esq < min_heap->tamanho && min_heap->dados[esq].chave < min_heap->dados[menor].chave) {
        menor = esq;
    }

    if (dir < min_heap->tamanho && min_heap->dados[dir].chave < min_heap->dados[menor].chave) {
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

void diminuir_chave(MinHeap *min_heap, int v, int chave) {
    int i = min_heap->posicao[v];
    min_heap->dados[i].chave = chave;

    while (i > 0 && min_heap->dados[i].chave < min_heap->dados[(i - 1) / 2].chave) {
        trocar_no_heap(min_heap, i, (i - 1) / 2);
        i = (i - 1) / 2;
    }
}

static int comparar_arestas(const void *a, const void *b) {
    Aresta *a1 = (Aresta*)a;
    Aresta *a2 = (Aresta*)b;
    return a1->peso - a2->peso;
}

void kruskal(GrafoListaPonderado *g, Aresta *resultado, int *num_arestas_agm, int *peso_total) {
    int n = g->num_vertices;
    int total_arestas = g->num_arestas;

    Aresta *arestas = (Aresta*)malloc(total_arestas * sizeof(Aresta));
    int idx = 0;

    for (int u = 0; u < n; u++) {
        for (NoAresta *p = g->lista[u]; p != NULL; p = p->prox) {
            int v = p->vertice;
            if (u < v) {
                arestas[idx].u = u;
                arestas[idx].v = v;
                arestas[idx].peso = p->peso;
                idx++;
            }
        }
    }

    qsort(arestas, total_arestas, sizeof(Aresta), comparar_arestas);

    DSU *dsu = criar_dsu(n);
    *peso_total = 0;
    *num_arestas_agm = 0;

    for (int i = 0; i < total_arestas && *num_arestas_agm < n - 1; i++) {
        int u = arestas[i].u;
        int v = arestas[i].v;
        int peso = arestas[i].peso;

        if (unir(dsu, u, v)) {
            resultado[*num_arestas_agm].u = u;
            resultado[*num_arestas_agm].v = v;
            resultado[*num_arestas_agm].peso = peso;
            (*num_arestas_agm)++;
            *peso_total += peso;
        }
    }

    free(arestas);
    liberar_dsu(dsu);
}

void prim(GrafoListaPonderado *g, int origem, int *pai, int *peso_total) {
    int n = g->num_vertices;
    int *chave = (int*)malloc(n * sizeof(int));
    MinHeap *min_heap = criar_min_heap(n);

    for (int v = 0; v < n; v++) {
        chave[v] = 1000000000;
        pai[v] = -1;
        min_heap->dados[v].vertice = v;
        min_heap->dados[v].chave = chave[v];
        min_heap->posicao[v] = v;
    }

    chave[origem] = 0;
    min_heap->dados[origem].chave = 0;
    min_heap->tamanho = n;

    diminuir_chave(min_heap, origem, 0);

    *peso_total = 0;

    while (min_heap->tamanho > 0) {
        NoHeap min_no = extrair_minimo(min_heap);
        int u = min_no.vertice;

        *peso_total += min_no.chave;

        for (NoAresta *p = g->lista[u]; p != NULL; p = p->prox) {
            int v = p->vertice;
            int peso = p->peso;

            if (esta_no_min_heap(min_heap, v) && peso < chave[v]) {
                chave[v] = peso;
                pai[v] = u;
                diminuir_chave(min_heap, v, chave[v]);
            }
        }
    }

    free(chave);
    liberar_min_heap(min_heap);
}
