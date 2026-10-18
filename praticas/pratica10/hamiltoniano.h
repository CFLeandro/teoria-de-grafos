#ifndef HAMILTONIANO_H
#define HAMILTONIANO_H

typedef struct {
    int n;
    int **adj;
} GrafoMatriz;

GrafoMatriz* criar_grafo_matriz(int n);
void adicionar_aresta_matriz(GrafoMatriz *g, int u, int v);
void liberar_grafo_matriz(GrafoMatriz *g);

int encontrar_caminho_hamiltoniano_bt(GrafoMatriz *g, int *caminho);
int encontrar_ciclo_hamiltoniano_bt(GrafoMatriz *g, int *ciclo);

#endif
