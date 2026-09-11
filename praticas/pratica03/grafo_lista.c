#include <stdio.h>
#include <stdlib.h>
#include "grafo_lista.h"

GrafoLista* criar_grafo_lista(int n) {
    GrafoLista *g = (GrafoLista*) malloc(sizeof(GrafoLista));
    g->n = n;
    g->adj = (No**) malloc(n * sizeof(No*));
    for (int i = 0; i < n; i++) {
        g->adj[i] = NULL;
    }
    return g;
}

void inserir_aresta_lista(GrafoLista *g, int u, int v) {
    if (u >= 0 && u < g->n && v >= 0 && v < g->n) {
        No *novo = (No*) malloc(sizeof(No));
        novo->destino = v;
        novo->prox = g->adj[u];
        g->adj[u] = novo;
    }
}

void liberar_grafo_lista(GrafoLista *g) {
    if (g) {
        for (int i = 0; i < g->n; i++) {
            No *atual = g->adj[i];
            while (atual != NULL) {
                No *temp = atual;
                atual = atual->prox;
                free(temp);
            }
        }
        free(g->adj);
        free(g);
    }
}
