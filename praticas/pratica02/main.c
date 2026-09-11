#include <stdio.h>
#include <stdlib.h>
#include "grafo_lista.h"
#include "busca_largura.h"
#include "busca_profundidade.h"

int main() {
    int n = 6;
    GrafoLista *g = criar_grafo_lista(n);
    
    inserir_aresta_lista(g, 0, 1);
    inserir_aresta_lista(g, 0, 2);
    inserir_aresta_lista(g, 1, 3);
    inserir_aresta_lista(g, 2, 3);
    // Vertices 4 e 5 formam um componente separado
    inserir_aresta_lista(g, 4, 5);

    printf("--- Testes BFS e DFS ---\n");

    int dist[6], pred[6];
    bfs(g, 0, dist, pred);
    printf("BFS - Distancia do vertice 0 ao 3: %d\n", dist[3]);

    int componentes = contar_componentes(g);
    printf("Numero de componentes conexos: %d\n", componentes);

    int ciclo = tem_ciclo(g);
    printf("O grafo possui ciclo? %s\n", ciclo ? "Sim" : "Nao");

    int bipartido = eh_bipartido(g);
    printf("O grafo eh bipartido? %s\n", bipartido ? "Sim" : "Nao");

    liberar_grafo_lista(g);
    return 0;
}
