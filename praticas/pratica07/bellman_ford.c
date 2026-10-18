#include <stdio.h>
#include <stdlib.h>
#include "bellman_ford.h"

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

int bellman_ford(GrafoListaPonderado *g, int origem, int *dist, int *pred) {
    int n = g->num_vertices;

    for (int i = 0; i < n; i++) {
        dist[i] = INF;
        pred[i] = -1;
    }
    dist[origem] = 0;

    for (int i = 1; i <= n - 1; i++) {
        for (int u = 0; u < n; u++) {
            if (dist[u] == INF) continue;
            for (NoAresta *p = g->lista[u]; p != NULL; p = p->prox) {
                int v = p->vertice;
                int peso = p->peso;
                if (dist[u] + peso < dist[v]) {
                    dist[v] = dist[u] + peso;
                    pred[v] = u;
                }
            }
        }
    }

    for (int u = 0; u < n; u++) {
        if (dist[u] == INF) continue;
        for (NoAresta *p = g->lista[u]; p != NULL; p = p->prox) {
            int v = p->vertice;
            int peso = p->peso;
            if (dist[u] + peso < dist[v]) {
                return 0;
            }
        }
    }

    return 1;
}

void reconstruir_ciclo_negativo(GrafoListaPonderado *g, int *dist, int *pred) {
    int n = g->num_vertices;
    int x = -1;

    for (int u = 0; u < n; u++) {
        if (dist[u] == INF) continue;
        for (NoAresta *p = g->lista[u]; p != NULL; p = p->prox) {
            int v = p->vertice;
            int peso = p->peso;
            if (dist[u] + peso < dist[v]) {
                x = v;
                break;
            }
        }
        if (x != -1) break;
    }

    if (x == -1) {
        printf("Nenhum ciclo negativo detectado.\n");
        return;
    }

    for (int i = 0; i < n; i++) {
        if (x != -1 && pred[x] != -1) {
            x = pred[x];
        }
    }

    int *ciclo = (int*)malloc((n + 1) * sizeof(int));
    int count = 0;
    int v = x;

    do {
        ciclo[count++] = v;
        v = pred[v];
    } while (v != x && v != -1 && count < n + 1);

    ciclo[count++] = x;

    printf("Ciclo negativo detectado: ");
    for (int i = count - 1; i >= 0; i--) {
        printf("%d%s", ciclo[i], (i == 0) ? "" : " -> ");
    }
    printf("\n");

    free(ciclo);
}