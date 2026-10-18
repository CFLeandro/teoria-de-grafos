#ifndef TPS_H
#define TPS_H

#include "hamiltoniano.h"

#define INF_TSP 1000000000

typedef struct {
    int n;
    int **custo;
} GrafoPonderadoMatriz;

GrafoPonderadoMatriz* criar_grafo_ponderado(int n);
void liberar_grafo_ponderado(GrafoPonderadoMatriz *g);

GrafoPonderadoMatriz* grafo_para_tsp(GrafoMatriz *g);

int tsp_forca_bruta(GrafoPonderadoMatriz *g, int *melhor_caminho);
int tsp_vizinho_mais_proximo(GrafoPonderadoMatriz *g, int *caminho);
int tsp_insercao(GrafoPonderadoMatriz *g, int *caminho);

#endif
