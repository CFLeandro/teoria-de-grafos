#include <stdio.h>
#include <stdlib.h>
#include "bellman_ford.h"

int main() {
    int n = 5;
    GrafoListaPonderado *g = criar_grafo(n);

    adicionar_aresta(g, 0, 1, -1);
    adicionar_aresta(g, 0, 2, 4);
    adicionar_aresta(g, 1, 2, 3);
    adicionar_aresta(g, 1, 3, 2);
    adicionar_aresta(g, 1, 4, 2);
    adicionar_aresta(g, 3, 2, 5);
    adicionar_aresta(g, 3, 1, 1);
    adicionar_aresta(g, 4, 3, -3);

    int *dist = (int*)malloc(n * sizeof(int));
    int *pred = (int*)malloc(n * sizeof(int));
    int origem = 0;

    printf("--- Grafo 1 (Sem ciclo negativo) ---\n");
    if (bellman_ford(g, origem, dist, pred)) {
        printf("Sucesso! Distancias a partir da origem (%d):\n", origem);
        for (int i = 0; i < n; i++) {
            printf("Vertice %d: Distancia = %d, Predecessor = %d\n", i, dist[i], pred[i]);
        }
    } else {
        printf("Ciclo negativo detectado!\n");
        reconstruir_ciclo_negativo(g, dist, pred);
    }

    liberar_grafo(g);

    GrafoListaPonderado *g2 = criar_grafo(4);
    adicionar_aresta(g2, 0, 1, 1);
    adicionar_aresta(g2, 1, 2, -1);
    adicionar_aresta(g2, 2, 3, -2);
    adicionar_aresta(g2, 3, 1, -1);

    int *dist2 = (int*)malloc(4 * sizeof(int));
    int *pred2 = (int*)malloc(4 * sizeof(int));

    printf("\n--- Grafo 2 (Com ciclo negativo) ---\n");
    if (bellman_ford(g2, 0, dist2, pred2)) {
        printf("Sucesso! Distancias calculadas com sucesso.\n");
    } else {
        printf("Ciclo negativo detectado!\n");
        reconstruir_ciclo_negativo(g2, dist2, pred2);
    }

    free(dist);
    free(pred);
    free(dist2);
    free(pred2);
    liberar_grafo(g2);

    return 0;
}
