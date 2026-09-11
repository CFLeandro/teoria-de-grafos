#include <stdio.h>
#include <stdlib.h>
#include "grafo_lista.h"
#include "dag.h"

void imprimir_array(int *arr, int n) {
    if (!arr) return;
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {
    printf("--- Teste 1: Grafo DAG ---\n");
    GrafoLista *dag = criar_grafo_lista(6);
    inserir_aresta_lista(dag, 5, 2);
    inserir_aresta_lista(dag, 5, 0);
    inserir_aresta_lista(dag, 4, 0);
    inserir_aresta_lista(dag, 4, 1);
    inserir_aresta_lista(dag, 2, 3);
    inserir_aresta_lista(dag, 3, 1);

    printf("E DAG? %s\n", eh_dag(dag) ? "Sim" : "Nao");

    int tam = 0;
    int *ordem_kahn = ordenacao_topologica_kahn(dag, &tam);
    printf("Ordenacao Kahn: ");
    imprimir_array(ordem_kahn, tam);
    free(ordem_kahn);

    int *ordem_dfs = ordenacao_topologica_dfs(dag, &tam);
    printf("Ordenacao DFS : ");
    imprimir_array(ordem_dfs, tam);
    free(ordem_dfs);

    liberar_grafo_lista(dag);

    printf("\n--- Teste 2: Grafo com Ciclo ---\n");
    GrafoLista *ciclo = criar_grafo_lista(3);
    inserir_aresta_lista(ciclo, 0, 1);
    inserir_aresta_lista(ciclo, 1, 2);
    inserir_aresta_lista(ciclo, 2, 0); // Fechando ciclo

    printf("E DAG? %s\n", eh_dag(ciclo) ? "Sim" : "Nao");

    int *k_ciclo = ordenacao_topologica_kahn(ciclo, &tam);
    if (!k_ciclo) printf("Kahn detectou ciclo. Ordenacao impossivel.\n");

    liberar_grafo_lista(ciclo);

    return 0;
}
