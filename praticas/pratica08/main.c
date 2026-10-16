#include <stdio.h>
#include <stdlib.h>
#include "agm.h"

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

    printf("--- Algoritmo de Kruskal ---\n");
    Aresta *resultado_kruskal = (Aresta*)malloc((n - 1) * sizeof(Aresta));
    int num_arestas_kruskal = 0;
    int peso_total_kruskal = 0;

    kruskal(g, resultado_kruskal, &num_arestas_kruskal, &peso_total_kruskal);

    printf("Arestas na AGM (Kruskal):\n");
    for (int i = 0; i < num_arestas_kruskal; i++) {
        printf("%d - %d (peso %d)\n", resultado_kruskal[i].u, resultado_kruskal[i].v, resultado_kruskal[i].peso);
    }
    printf("Peso Total (Kruskal): %d\n\n", peso_total_kruskal);

    printf("--- Algoritmo de Prim ---\n");
    int *pai_prim = (int*)malloc(n * sizeof(int));
    int peso_total_prim = 0;

    prim(g, 0, pai_prim, &peso_total_prim);

    printf("Arestas na AGM (Prim):\n");
    for (int i = 1; i < n; i++) {
        if (pai_prim[i] != -1) {
            printf("%d - %d\n", pai_prim[i], i);
        }
    }
    printf("Peso Total (Prim): %d\n", peso_total_prim);

    free(resultado_kruskal);
    free(pai_prim);
    liberar_grafo(g);

    return 0;
}
