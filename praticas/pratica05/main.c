#include <stdio.h>
#include <stdlib.h>
#include "coloracao.h"

int main() {
    int n = 6;
    GrafoLista *g = criar_grafo(n);

    adicionar_aresta(g, 0, 1);
    adicionar_aresta(g, 0, 2);
    adicionar_aresta(g, 1, 3);
    adicionar_aresta(g, 2, 3);
    adicionar_aresta(g, 3, 4);
    adicionar_aresta(g, 4, 5);

    int num_cores_gulosa = 0;
    int *cores_gulosa = coloracao_gulosa(g, &num_cores_gulosa);

    printf("Coloracao Gulosa (Total de cores: %d):\n", num_cores_gulosa);
    for (int i = 0; i < n; i++) {
        printf("Vertice %d -> Cor %d\n", i, cores_gulosa[i]);
    }

    int num_cores_wp = 0;
    int *cores_wp = coloracao_welsh_powell(g, &num_cores_wp);

    printf("\nColoracao Welsh-Powell (Total de cores: %d):\n", num_cores_wp);
    for (int i = 0; i < n; i++) {
        printf("Vertice %d -> Cor %d\n", i, cores_wp[i]);
    }

    printf("\nO grafo eh bipartido? %s\n", eh_bipartido(g) ? "Sim" : "Nao");

    free(cores_gulosa);
    free(cores_wp);
    liberar_grafo(g);

    return 0;
}