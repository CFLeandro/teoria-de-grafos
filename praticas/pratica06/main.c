#include <stdio.h>
#include <stdlib.h>
#include "dijkstra.h"

int main() {
    int n = 6;
    GrafoListaPonderado *g = criar_grafo(n);

    adicionar_aresta(g, 0, 1, 4);
    adicionar_aresta(g, 0, 2, 2);
    adicionar_aresta(g, 1, 2, 1);
    adicionar_aresta(g, 1, 3, 5);
    adicionar_aresta(g, 2, 3, 8);
    adicionar_aresta(g, 2, 4, 10);
    adicionar_aresta(g, 3, 4, 2);
    adicionar_aresta(g, 3, 5, 6);
    adicionar_aresta(g, 4, 5, 3);

    int *dist = (int*)malloc(n * sizeof(int));
    int *pred = (int*)malloc(n * sizeof(int));

    int origem = 0;
    dijkstra(g, origem, dist, pred);

    printf("Distancias minimas a partir da origem (%d):\n", origem);
    for (int i = 0; i < n; i++) {
        if (dist[i] == INF) {
            printf("Vertice %d: Inalcancavel\n", i);
        } else {
            printf("Vertice %d: Distancia = %d, Caminho = ", i, dist[i]);
            reconstruir_caminho(origem, i, pred);
            printf("\n");
        }
    }

    free(dist);
    free(pred);
    liberar_grafo(g);

    return 0;
}
