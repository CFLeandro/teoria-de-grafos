#include <stdio.h>
#include <stdlib.h>
#include "conectividade.h"

GrafoLista* criar_grafo(int n) {
    GrafoLista *g = (GrafoLista*)malloc(sizeof(GrafoLista));
    g->num_vertices = n;
    g->num_arestas = 0;
    g->lista = (No**)malloc(n * sizeof(No*));
    for (int i = 0; i < n; i++) {
        g->lista[i] = NULL;
    }
    return g;
}

void adicionar_aresta(GrafoLista *g, int u, int v) {
    No *novo = (No*)malloc(sizeof(No));
    novo->vertice = v;
    novo->prox = g->lista[u];
    g->lista[u] = novo;

    novo = (No*)malloc(sizeof(No));
    novo->vertice = u;
    novo->prox = g->lista[v];
    g->lista[v] = novo;

    g->num_arestas++;
}

void liberar_grafo(GrafoLista *g) {
    if (!g) return;
    for (int i = 0; i < g->num_vertices; i++) {
        No *atual = g->lista[i];
        while (atual) {
            No *temp = atual;
            atual = atual->prox;
            free(temp);
        }
    }
    free(g->lista);
    free(g);
}

void dfs_articulacoes(GrafoLista *g, int u, int *tempo, int *descoberta, int *low, int *pai, int *articulacao) {
    int filhos = 0;
    descoberta[u] = low[u] = ++(*tempo);

    for (No *p = g->lista[u]; p != NULL; p = p->prox) {
        int v = p->vertice;
        if (descoberta[v] == 0) {
            filhos++;
            pai[v] = u;
            dfs_articulacoes(g, v, tempo, descoberta, low, pai, articulacao);

            if (low[v] < low[u]) {
                low[u] = low[v];
            }

            if (pai[u] == -1 && filhos > 1) {
                articulacao[u] = 1;
            }
            if (pai[u] != -1 && low[v] >= descoberta[u]) {
                articulacao[u] = 1;
            }
        } else if (v != pai[u]) {
            if (descoberta[v] < low[u]) {
                low[u] = descoberta[v];
            }
        }
    }
}

static void dfs_pontes(GrafoLista *g, int u, int *tempo, int *descoberta, int *low, int *pai) {
    descoberta[u] = low[u] = ++(*tempo);

    for (No *p = g->lista[u]; p != NULL; p = p->prox) {
        int v = p->vertice;
        if (descoberta[v] == 0) {
            pai[v] = u;
            dfs_pontes(g, v, tempo, descoberta, low, pai);

            if (low[v] < low[u]) {
                low[u] = low[v];
            }

            if (low[v] > descoberta[u]) {
                printf("Ponte: %d - %d\n", u, v);
            }
        } else if (v != pai[u]) {
            if (descoberta[v] < low[u]) {
                low[u] = descoberta[v];
            }
        }
    }
}

void detectar_pontes(GrafoLista *g) {
    int n = g->num_vertices;
    int *descoberta = (int*)calloc(n, sizeof(int));
    int *low = (int*)calloc(n, sizeof(int));
    int *pai = (int*)malloc(n * sizeof(int));
    int tempo = 0;

    for (int i = 0; i < n; i++) {
        pai[i] = -1;
    }

    for (int u = 0; u < n; u++) {
        if (descoberta[u] == 0) {
            dfs_pontes(g, u, &tempo, descoberta, low, pai);
        }
    }

    free(descoberta);
    free(low);
    free(pai);
}