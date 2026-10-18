#include <stdio.h>
#include <stdlib.h>
#include "hamiltoniano.h"

GrafoMatriz* criar_grafo_matriz(int n) {
    GrafoMatriz *g = (GrafoMatriz*)malloc(sizeof(GrafoMatriz));
    g->n = n;
    g->adj = (int**)malloc(n * sizeof(int*));
    for (int i = 0; i < n; i++) {
        g->adj[i] = (int*)calloc(n, sizeof(int));
    }
    return g;
}

void adicionar_aresta_matriz(GrafoMatriz *g, int u, int v) {
    if (u >= 0 && u < g->n && v >= 0 && v < g->n) {
        g->adj[u][v] = 1;
        g->adj[v][u] = 1;
    }
}

void liberar_grafo_matriz(GrafoMatriz *g) {
    if (!g) return;
    for (int i = 0; i < g->n; i++) {
        free(g->adj[i]);
    }
    free(g->adj);
    free(g);
}

static int caminho_bt_aux(GrafoMatriz *g, int pos, int *visitado, int *caminho) {
    if (pos == g->n) {
        return 1;
    }

    int u = caminho[pos - 1];
    for (int v = 0; v < g->n; v++) {
        if (g->adj[u][v] && !visitado[v]) {
            visitado[v] = 1;
            caminho[pos] = v;

            if (caminho_bt_aux(g, pos + 1, visitado, caminho)) {
                return 1;
            }

            visitado[v] = 0;
        }
    }

    return 0;
}

int encontrar_caminho_hamiltoniano_bt(GrafoMatriz *g, int *caminho) {
    int n = g->n;
    int *visitado = (int*)calloc(n, sizeof(int));

    for (int inicio = 0; inicio < n; inicio++) {
        visitado[inicio] = 1;
        caminho[0] = inicio;

        if (caminho_bt_aux(g, 1, visitado, caminho)) {
            free(visitado);
            return 1;
        }

        visitado[inicio] = 0;
    }

    free(visitado);
    return 0;
}

static int ciclo_bt_aux(GrafoMatriz *g, int pos, int *visitado, int *ciclo) {
    if (pos == g->n) {
        if (g->adj[ciclo[pos - 1]][ciclo[0]]) {
            return 1;
        }
        return 0;
    }

    int u = ciclo[pos - 1];
    for (int v = 0; v < g->n; v++) {
        if (g->adj[u][v] && !visitado[v]) {
            visitado[v] = 1;
            ciclo[pos] = v;

            if (ciclo_bt_aux(g, pos + 1, visitado, ciclo)) {
                return 1;
            }

            visitado[v] = 0;
        }
    }

    return 0;
}

int encontrar_ciclo_hamiltoniano_bt(GrafoMatriz *g, int *ciclo) {
    int n = g->n;
    if (n == 0) return 0;

    int *visitado = (int*)calloc(n, sizeof(int));
    visitado[0] = 1;
    ciclo[0] = 0;

    int encontrou = ciclo_bt_aux(g, 1, visitado, ciclo);

    free(visitado);
    return encontrou;
}
