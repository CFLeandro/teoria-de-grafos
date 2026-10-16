#ifndef COBERTURA_H
#define COBERTURA_H

typedef struct No {
    int vertice;
    struct No *prox;
} No;

typedef struct {
    int num_vertices;
    int num_arestas;
    No **lista;
} GrafoLista;

GrafoLista* criar_grafo(int n);
void adicionar_aresta(GrafoLista *g, int u, int v);
void liberar_grafo(GrafoLista *g);

int eh_cobertura(GrafoLista *g, const int *coberto);
int cobertura_minima_bt(GrafoLista *g, int *melhor_solucao);
int cobertura_gulosa(GrafoLista *g, int *solucao);

#endif
