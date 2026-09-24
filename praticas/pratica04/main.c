#include <stdio.h>
#include <stdlib.h>
#include "conectividade.h"
#include "planaridade.h"

int main() {
    int n = 6;
    GrafoLista *g = criar_grafo(n);

    adicionar_aresta(g, 0, 1);
    adicionar_aresta(g, 1, 2);
    adicionar_aresta(g, 2, 0);
    adicionar_aresta(g, 2, 3);
    adicionar_aresta(g, 3, 4);
    adicionar_aresta(g, 4, 5);

    int *descoberta = (int*)calloc(n, sizeof(int));
    int *low = (int*)calloc(n, sizeof(int));
    int *pai = (int*)malloc(n * sizeof(int));
    int *articulacao = (int*)calloc(n, sizeof(int));
    int tempo = 0;

    for (int i = 0; i < n; i++) {
        pai[i] = -1;
    }

    for (int i = 0; i < n; i++) {
        if (descoberta[i] == 0) {
            dfs_articulacoes(g, i, &tempo, descoberta, low, pai, articulacao);
        }
    }

    printf("Vértices de Corte:\n");
    for (int i = 0; i < n; i++) {
        if (articulacao[i]) {
            printf("%d ", i);
        }
    }
    printf("\n");

    printf("Pontes:\n");
    detectar_pontes(g);

    printf("Planar por Euler: %s\n", eh_planar_euler(g) ? "Sim" : "Não");
    printf("Planar por Kuratowski: %s\n", eh_planar_kuratowski(g) ? "Sim" : "Não");

    free(descoberta);
    free(low);
    free(pai);
    free(articulacao);
    liberar_grafo(g);

    return 0;
}