#include <stdio.h>
#include <stdlib.h>
#include "tps.h"

GrafoPonderadoMatriz* criar_grafo_ponderado(int n) {
    GrafoPonderadoMatriz *g = (GrafoPonderadoMatriz*)malloc(sizeof(GrafoPonderadoMatriz));
    g->n = n;
    g->custo = (int**)malloc(n * sizeof(int*));
    for (int i = 0; i < n; i++) {
        g->custo[i] = (int*)calloc(n, sizeof(int));
    }
    return g;
}

void liberar_grafo_ponderado(GrafoPonderadoMatriz *g) {
    if (!g) return;
    for (int i = 0; i < g->n; i++) {
        free(g->custo[i]);
    }
    free(g->custo);
    free(g);
}

GrafoPonderadoMatriz* grafo_para_tsp(GrafoMatriz *g) {
    int n = g->n;
    GrafoPonderadoMatriz *gp = criar_grafo_ponderado(n);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j) {
                gp->custo[i][j] = 0;
            } else if (g->adj[i][j]) {
                gp->custo[i][j] = 1;
            } else {
                gp->custo[i][j] = 2;
            }
        }
    }

    return gp;
}

static void permutar_tsp(GrafoPonderadoMatriz *g, int pos, int *visitado, int *caminho_atual, int custo_atual, int *melhor_custo, int *melhor_caminho) {
    int n = g->n;

    if (pos == n) {
        int custo_total = custo_atual + g->custo[caminho_atual[n - 1]][caminho_atual[0]];
        if (custo_total < *melhor_custo) {
            *melhor_custo = custo_total;
            for (int i = 0; i < n; i++) {
                melhor_caminho[i] = caminho_atual[i];
            }
        }
        return;
    }

    if (custo_atual >= *melhor_custo) {
        return;
    }

    int u = caminho_atual[pos - 1];
    for (int v = 1; v < n; v++) {
        if (!visitado[v]) {
            visitado[v] = 1;
            caminho_atual[pos] = v;

            permutar_tsp(g, pos + 1, visitado, caminho_atual, custo_atual + g->custo[u][v], melhor_custo, melhor_caminho);

            visitado[v] = 0;
        }
    }
}

int tsp_forca_bruta(GrafoPonderadoMatriz *g, int *melhor_caminho) {
    int n = g->n;
    int *caminho_atual = (int*)malloc(n * sizeof(int));
    int *visitado = (int*)calloc(n, sizeof(int));

    caminho_atual[0] = 0;
    visitado[0] = 1;

    int melhor_custo = INF_TSP;

    permutar_tsp(g, 1, visitado, caminho_atual, 0, &melhor_custo, melhor_caminho);

    free(caminho_atual);
    free(visitado);

    return melhor_custo;
}

int tsp_vizinho_mais_proximo(GrafoPonderadoMatriz *g, int *caminho) {
    int n = g->n;
    int *visitado = (int*)calloc(n, sizeof(int));

    caminho[0] = 0;
    visitado[0] = 1;

    int custo_total = 0;
    int atual = 0;

    for (int i = 1; i < n; i++) {
        int prox = -1;
        int menor_dist = INF_TSP;

        for (int v = 0; v < n; v++) {
            if (!visitado[v] && g->custo[atual][v] < menor_dist) {
                menor_dist = g->custo[atual][v];
                prox = v;
            }
        }

        caminho[i] = prox;
        visitado[prox] = 1;
        custo_total += menor_dist;
        atual = prox;
    }

    custo_total += g->custo[atual][caminho[0]];

    free(visitado);
    return custo_total;
}

int tsp_insercao(GrafoPonderadoMatriz *g, int *caminho) {
    int n = g->n;
    if (n <= 2) {
        for (int i = 0; i < n; i++) caminho[i] = i;
        int c = 0;
        for (int i = 0; i < n; i++) c += g->custo[i][(i + 1) % n];
        return c;
    }

    int *em_subciclo = (int*)calloc(n, sizeof(int));
    int tam_subciclo = 0;

    caminho[0] = 0;
    em_subciclo[0] = 1;

    int v_proximo = -1;
    int menor_custo = INF_TSP;
    for (int v = 1; v < n; v++) {
        if (g->custo[0][v] < menor_custo) {
            menor_custo = g->custo[0][v];
            v_proximo = v;
        }
    }

    caminho[1] = v_proximo;
    em_subciclo[v_proximo] = 1;
    tam_subciclo = 2;

    while (tam_subciclo < n) {
        int k_escolhido = -1;
        int dist_min = INF_TSP;

        for (int k = 0; k < n; k++) {
            if (em_subciclo[k]) continue;

            for (int i = 0; i < tam_subciclo; i++) {
                int u = caminho[i];
                if (g->custo[u][k] < dist_min) {
                    dist_min = g->custo[u][k];
                    k_escolhido = k;
                }
            }
        }

        int melhor_pos = -1;
        int menor_aumento = INF_TSP;

        for (int i = 0; i < tam_subciclo; i++) {
            int u = caminho[i];
            int v = caminho[(i + 1) % tam_subciclo];

            int aumento = g->custo[u][k_escolhido] + g->custo[k_escolhido][v] - g->custo[u][v];
            if (aumento < menor_aumento) {
                menor_aumento = aumento;
                melhor_pos = i + 1;
            }
        }

        for (int j = tam_subciclo; j > melhor_pos; j--) {
            caminho[j] = caminho[j - 1];
        }
        caminho[melhor_pos] = k_escolhido;
        em_subciclo[k_escolhido] = 1;
        tam_subciclo++;
    }

    int custo_total = 0;
    for (int i = 0; i < n; i++) {
        custo_total += g->custo[caminho[i]][caminho[(i + 1) % n]];
    }

    free(em_subciclo);
    return custo_total;
}
