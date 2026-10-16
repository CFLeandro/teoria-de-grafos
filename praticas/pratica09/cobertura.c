#include <stdio.h>
#include <stdlib.h>
#include "cobertura.h"

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

int eh_cobertura(GrafoLista *g, const int *coberto) {
    for (int u = 0; u < g->num_vertices; u++) {
        for (No *p = g->lista[u]; p != NULL; p = p->prox) {
            int v = p->vertice;
            if (u < v) {
                if (!coberto[u] && !coberto[v]) {
                    return 0;
                }
            }
        }
    }
    return 1;
}

static void bt_aux(GrafoLista *g, int vertice, int *sol_atual, int tam_atual, int *melhor_sol, int *melhor_tam) {
    if (tam_atual >= *melhor_tam) {
        return;
    }

    if (vertice == g->num_vertices) {
        if (eh_cobertura(g, sol_atual)) {
            *melhor_tam = tam_atual;
            for (int i = 0; i < g->num_vertices; i++) {
                melhor_sol[i] = sol_atual[i];
            }
        }
        return;
    }

    sol_atual[vertice] = 1;
    bt_aux(g, vertice + 1, sol_atual, tam_atual + 1, melhor_sol, melhor_tam);

    sol_atual[vertice] = 0;
    bt_aux(g, vertice + 1, sol_atual, tam_atual, melhor_sol, melhor_tam);
}

int cobertura_minima_bt(GrafoLista *g, int *melhor_solucao) {
    int n = g->num_vertices;
    int *sol_atual = (int*)calloc(n, sizeof(int));
    int melhor_tam = n + 1;

    for (int i = 0; i < n; i++) {
        melhor_solucao[i] = 1;
    }

    bt_aux(g, 0, sol_atual, 0, melhor_solucao, &melhor_tam);

    free(sol_atual);
    return melhor_tam;
}

int cobertura_gulosa(GrafoLista *g, int *solucao) {
    int n = g->num_vertices;
    for (int i = 0; i < n; i++) {
        solucao[i] = 0;
    }

    int **arestas_cobertas = (int**)malloc(n * sizeof(int*));
    for (int i = 0; i < n; i++) {
        arestas_cobertas[i] = (int*)calloc(n, sizeof(int));
    }

    int total_arestas_cobertas = 0;
    int tam_solucao = 0;

    while (total_arestas_cobertas < g->num_arestas) {
        int max_grau = -1;
        int melhor_vertice = -1;

        for (int u = 0; u < n; u++) {
            if (solucao[u]) continue;

            int grau_nao_coberto = 0;
            for (No *p = g->lista[u]; p != NULL; p = p->prox) {
                int v = p->vertice;
                if (!arestas_cobertas[u][v]) {
                    grau_nao_coberto++;
                }
            }

            if (grau_nao_coberto > max_grau) {
                max_grau = grau_nao_coberto;
                melhor_vertice = u;
            }
        }

        if (melhor_vertice == -1 || max_grau == 0) break;

        solucao[melhor_vertice] = 1;
        tam_solucao++;

        for (No *p = g->lista[melhor_vertice]; p != NULL; p = p->prox) {
            int v = p->vertice;
            if (!arestas_cobertas[melhor_vertice][v]) {
                arestas_cobertas[melhor_vertice][v] = 1;
                arestas_cobertas[v][melhor_vertice] = 1;
                total_arestas_cobertas++;
            }
        }
    }

    for (int i = 0; i < n; i++) {
        free(arestas_cobertas[i]);
    }
    free(arestas_cobertas);

    return tam_solucao;
}
