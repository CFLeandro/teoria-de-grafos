#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "coloracao.h"

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

int* coloracao_gulosa(GrafoLista *g, int *num_cores) {
    int n = g->num_vertices;
    int *cores = (int*)malloc(n * sizeof(int));
    bool *disponivel = (bool*)malloc(n * sizeof(bool));

    for (int i = 0; i < n; i++) {
        cores[i] = -1;
        disponivel[i] = true;
    }

    cores[0] = 0;
    int max_cor = 0;

    for (int u = 1; u < n; u++) {
        for (No *p = g->lista[u]; p != NULL; p = p->prox) {
            int v = p->vertice;
            if (cores[v] != -1) {
                disponivel[cores[v]] = false;
            }
        }

        int cr;
        for (cr = 0; cr < n; cr++) {
            if (disponivel[cr]) {
                break;
            }
        }

        cores[u] = cr;
        if (cr > max_cor) {
            max_cor = cr;
        }

        for (No *p = g->lista[u]; p != NULL; p = p->prox) {
            int v = p->vertice;
            if (cores[v] != -1) {
                disponivel[cores[v]] = true;
            }
        }
    }

    if (num_cores) {
        *num_cores = max_cor + 1;
    }

    free(disponivel);
    return cores;
}

typedef struct {
    int vertice;
    int grau;
} VerticeGrau;

static int comparar_graus(const void *a, const void *b) {
    VerticeGrau *v1 = (VerticeGrau*)a;
    VerticeGrau *v2 = (VerticeGrau*)b;
    return v2->grau - v1->grau;
}

int* coloracao_welsh_powell(GrafoLista *g, int *num_cores) {
    int n = g->num_vertices;
    VerticeGrau *ordem = (VerticeGrau*)malloc(n * sizeof(VerticeGrau));

    for (int i = 0; i < n; i++) {
        ordem[i].vertice = i;
        int grau = 0;
        for (No *p = g->lista[i]; p != NULL; p = p->prox) {
            grau++;
        }
        ordem[i].grau = grau;
    }

    qsort(ordem, n, sizeof(VerticeGrau), comparar_graus);

    int *cores = (int*)malloc(n * sizeof(int));
    bool *disponivel = (bool*)malloc(n * sizeof(bool));

    for (int i = 0; i < n; i++) {
        cores[i] = -1;
        disponivel[i] = true;
    }

    int max_cor = 0;

    for (int i = 0; i < n; i++) {
        int u = ordem[i].vertice;

        for (No *p = g->lista[u]; p != NULL; p = p->prox) {
            int v = p->vertice;
            if (cores[v] != -1) {
                disponivel[cores[v]] = false;
            }
        }

        int cr;
        for (cr = 0; cr < n; cr++) {
            if (disponivel[cr]) {
                break;
            }
        }

        cores[u] = cr;
        if (cr > max_cor) {
            max_cor = cr;
        }

        for (No *p = g->lista[u]; p != NULL; p = p->prox) {
            int v = p->vertice;
            if (cores[v] != -1) {
                disponivel[cores[v]] = true;
            }
        }
    }

    if (num_cores) {
        *num_cores = max_cor + 1;
    }

    free(ordem);
    free(disponivel);
    return cores;
}

int eh_bipartido(GrafoLista *g) {
    int n = g->num_vertices;
    int *cor = (int*)malloc(n * sizeof(int));

    for (int i = 0; i < n; i++) {
        cor[i] = -1;
    }

    int *fila = (int*)malloc(n * sizeof(int));

    for (int i = 0; i < n; i++) {
        if (cor[i] == -1) {
            int inicio = 0, fim = 0;
            cor[i] = 0;
            fila[fim++] = i;

            while (inicio < fim) {
                int u = fila[inicio++];

                for (No *p = g->lista[u]; p != NULL; p = p->prox) {
                    int v = p->vertice;

                    if (cor[v] == -1) {
                        cor[v] = 1 - cor[u];
                        fila[fim++] = v;
                    } else if (cor[v] == cor[u]) {
                        free(cor);
                        free(fila);
                        return 0;
                    }
                }
            }
        }
    }

    free(cor);
    free(fila);
    return 1;
}