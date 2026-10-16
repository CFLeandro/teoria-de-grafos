#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "hamiltoniano.h"
#include "tps.h"

GrafoMatriz* gerar_grafo_teste(int n) {
    GrafoMatriz *g = criar_grafo_matriz(n);
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if ((i + j) % 2 == 0 || (i * j) % 3 == 0) {
                adicionar_aresta_matriz(g, i, j);
            }
        }
    }
    return g;
}

int main() {
    int tamanhos[] = {5, 8, 10, 12};
    int num_testes = sizeof(tamanhos) / sizeof(tamanhos[0]);

    printf("===========================================================================================\n");
    printf("  EXPERIMENTO TSP: FORCA BRUTA vs VIZINHO MAIS PROXIMO vs INSERCAO\n");
    printf("===========================================================================================\n");
    printf("%-4s | %-12s %-8s | %-12s %-8s | %-12s %-8s\n",
           "N", "T. FB (s)", "Custo", "T. VMP (s)", "Custo", "T. INS (s)", "Custo");
    printf("-------------------------------------------------------------------------------------------\n");

    for (int t = 0; t < num_testes; t++) {
        int n = tamanhos[t];
        GrafoMatriz *g = gerar_grafo_teste(n);
        GrafoPonderadoMatriz *gp = grafo_para_tsp(g);

        int *caminho_fb = (int*)malloc(n * sizeof(int));
        int *caminho_vmp = (int*)malloc(n * sizeof(int));
        int *caminho_ins = (int*)malloc(n * sizeof(int));

        clock_t i_fb = clock();
        int custo_fb = tsp_forca_bruta(gp, caminho_fb);
        clock_t f_fb = clock();
        double tempo_fb = (double)(f_fb - i_fb) / CLOCKS_PER_SEC;

        clock_t i_vmp = clock();
        int custo_vmp = tsp_vizinho_mais_proximo(gp, caminho_vmp);
        clock_t f_vmp = clock();
        double tempo_vmp = (double)(f_vmp - i_vmp) / CLOCKS_PER_SEC;

        clock_t i_ins = clock();
        int custo_ins = tsp_insercao(gp, caminho_ins);
        clock_t f_ins = clock();
        double tempo_ins = (double)(f_ins - i_ins) / CLOCKS_PER_SEC;

        printf("%-4d | %-12.6f %-8d | %-12.6f %-8d | %-12.6f %-8d\n",
               n, tempo_fb, custo_fb, tempo_vmp, custo_vmp, tempo_ins, custo_ins);

        free(caminho_fb);
        free(caminho_vmp);
        free(caminho_ins);
        liberar_grafo_ponderado(gp);
        liberar_grafo_matriz(g);
    }
    printf("===========================================================================================\n");

    return 0;
}
