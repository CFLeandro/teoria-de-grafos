#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "cobertura.h"

GrafoLista* gerar_grafo_teste(int n) {
    GrafoLista *g = criar_grafo(n);
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if ((i + j) % 2 == 0 || (i * j) % 3 == 0) {
                adicionar_aresta(g, i, j);
            }
        }
    }
    return g;
}

int main() {
    int tamanhos[] = {5, 8, 10, 12, 15};
    int num_testes = sizeof(tamanhos) / sizeof(tamanhos[0]);

    printf("=========================================================================\n");
    printf("  EXPERIMENTO: COBERTURA DE VERTICES (FORCA BRUTA BT vs GULOSA)\n");
    printf("=========================================================================\n");
    printf("%-5s | %-8s | %-15s | %-15s | %-8s\n", "N", "Arestas", "Tempo BT (s)", "Tempo Gulosa (s)", "Tam BT / Gulosa");
    printf("-------------------------------------------------------------------------\n");

    for (int i = 0; i < num_testes; i++) {
        int n = tamanhos[i];
        GrafoLista *g = gerar_grafo_teste(n);

        int *sol_bt = (int*)malloc(n * sizeof(int));
        int *sol_gulosa = (int*)malloc(n * sizeof(int));

        clock_t inicio_bt = clock();
        int tam_bt = cobertura_minima_bt(g, sol_bt);
        clock_t fim_bt = clock();
        double tempo_bt = (double)(fim_bt - inicio_bt) / CLOCKS_PER_SEC;

        clock_t inicio_gulosa = clock();
        int tam_gulosa = cobertura_gulosa(g, sol_gulosa);
        clock_t fim_gulosa = clock();
        double tempo_gulosa = (double)(fim_gulosa - inicio_gulosa) / CLOCKS_PER_SEC;

        printf("%-5d | %-8d | %-15.6f | %-15.6f | %d / %d\n",
               n, g->num_arestas, tempo_bt, tempo_gulosa, tam_bt, tam_gulosa);

        free(sol_bt);
        free(sol_gulosa);
        liberar_grafo(g);
    }
    printf("=========================================================================\n");

    return 0;
}
