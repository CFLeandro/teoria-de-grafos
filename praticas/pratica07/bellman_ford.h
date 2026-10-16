#ifndef BELLMAN_FORD_H
#define BELLMAN_FORD_H

#define INF 1000000000

typedef struct NoAresta {
    int vertice;
    int peso;
    struct NoAresta *prox;
} NoAresta;

typedef struct {
    int num_vertices;
    int num_arestas;
    NoAresta **lista;
} GrafoListaPonderado;

GrafoListaPonderado* criar_grafo(int n);
void adicionar_aresta(GrafoListaPonderado *g, int u, int v, int peso);
void liberar_grafo(GrafoListaPonderado *g);

int bellman_ford(GrafoListaPonderado *g, int origem, int *dist, int *pred);
void reconstruir_ciclo_negativo(GrafoListaPonderado *g, int *dist, int *pred);

#endif
