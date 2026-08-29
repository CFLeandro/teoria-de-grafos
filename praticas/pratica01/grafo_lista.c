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

static No* criar_no(int v) {
    No *novo = (No*) malloc(sizeof(No));
    novo->destino = v;
    novo->prox = NULL;
    return novo;
}

void inserir_aresta_lista(GrafoLista *g, int u, int v) {
    if (u >= 0 && u < g->n && v >= 0 && v < g->n) {
        // Insere v na lista de u
        No *novo = criar_no(v);
        novo->prox = g->adj[u];
        g->adj[u] = novo;

        // Insere u na lista de v (assumindo grafo não direcionado)
        novo = criar_no(u);
        novo->prox = g->adj[v];
        g->adj[v] = novo;
    }
}

void remover_aresta_lista(GrafoLista *g, int u, int v) {
    if (u < 0 || u >= g->n || v < 0 || v >= g->n) return;

    // Remove v da lista de u
    No *atual = g->adj[u];
    No *ant = NULL;
    while (atual != NULL && atual->destino != v) {
        ant = atual;
        atual = atual->prox;
    }
    if (atual != NULL) {
        if (ant == NULL) g->adj[u] = atual->prox;
        else ant->prox = atual->prox;
        free(atual);
    }

    // Remove u da lista de v
    atual = g->adj[v];
    ant = NULL;
    while (atual != NULL && atual->destino != u) {
        ant = atual;
        atual = atual->prox;
    }
    if (atual != NULL) {
        if (ant == NULL) g->adj[v] = atual->prox;
        else ant->prox = atual->prox;
        free(atual);
    }
}

int grau_lista(GrafoLista *g, int u) {
    int grau = 0;
    if (u >= 0 && u < g->n) {
        No *atual = g->adj[u];
        while (atual != NULL) {
            grau++;
            atual = atual->prox;
        }
    }
    return grau;
}

int sao_adjacentes_lista(GrafoLista *g, int u, int v) {
    if (u >= 0 && u < g->n && v >= 0 && v < g->n) {
        No *atual = g->adj[u];
        while (atual != NULL) {
            if (atual->destino == v) return 1;
            atual = atual->prox;
        }
    }
    return 0;
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
