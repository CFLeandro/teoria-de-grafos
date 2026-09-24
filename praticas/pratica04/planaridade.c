#include <stdio.h>
#include <stdlib.h>
#include "planaridade.h"

int eh_planar_euler(GrafoLista *g) {
    if (!g) return 1;
    int n = g->num_vertices;
    int m = g->num_arestas;

    if (n <= 2) return 1;
    return (m <= 3 * n - 6);
}

static int adj[10][10];

static void construir_matriz(GrafoLista *g) {
    int n = g->num_vertices;
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            adj[i][j] = 0;
        }
    }
    for (int u = 0; u < n; u++) {
        for (No *p = g->lista[u]; p != NULL; p = p->prox) {
            adj[u][p->vertice] = 1;
        }
    }
}

static void suprimir_grau2(int n) {
    int alterou = 1;
    while (alterou) {
        alterou = 0;
        for (int i = 0; i < n; i++) {
            int grau = 0;
            int viz[10];
            for (int j = 0; j < n; j++) {
                if (adj[i][j]) {
                    viz[grau++] = j;
                }
            }
            if (grau == 2) {
                int u = viz[0];
                int w = viz[1];
                adj[i][u] = adj[u][i] = 0;
                adj[i][w] = adj[w][i] = 0;
                if (u != w) {
                    adj[u][w] = adj[w][u] = 1;
                }
                alterou = 1;
            }
        }
    }
}

static int tem_k5(int n) {
    for (int a = 0; a < n; a++) {
        for (int b = a + 1; b < n; b++) {
            for (int c = b + 1; c < n; c++) {
                for (int d = c + 1; d < n; d++) {
                    for (int e = d + 1; e < n; e++) {
                        int v[5] = {a, b, c, d, e};
                        int k5 = 1;
                        for (int i = 0; i < 5; i++) {
                            for (int j = i + 1; j < 5; j++) {
                                if (!adj[v[i]][v[j]]) {
                                    k5 = 0;
                                    break;
                                }
                            }
                            if (!k5) break;
                        }
                        if (k5) return 1;
                    }
                }
            }
        }
    }
    return 0;
}

static int tem_k33(int n) {
    for (int a = 0; a < n; a++) {
        for (int b = a + 1; b < n; b++) {
            for (int c = b + 1; c < n; c++) {
                for (int d = 0; d < n; d++) {
                    if (d == a || d == b || d == c) continue;
                    for (int e = d + 1; e < n; e++) {
                        if (e == a || e == b || e == c) continue;
                        for (int f = e + 1; f < n; f++) {
                            if (f == a || f == b || f == c) continue;
                            int set1[3] = {a, b, c};
                            int set2[3] = {d, e, f};
                            int k33 = 1;
                            for (int i = 0; i < 3; i++) {
                                for (int j = 0; j < 3; j++) {
                                    if (!adj[set1[i]][set2[j]]) {
                                        k33 = 0;
                                        break;
                                    }
                                }
                                if (!k33) break;
                            }
                            if (k33) return 1;
                        }
                    }
                }
            }
        }
    }
    return 0;
}

int eh_planar_kuratowski(GrafoLista *g) {
    if (!g) return 1;
    int n = g->num_vertices;
    if (n > 10) return eh_planar_euler(g);

    construir_matriz(g);
    suprimir_grau2(n);

    if (tem_k5(n) || tem_k33(n)) {
        return 0;
    }
    return 1;
}