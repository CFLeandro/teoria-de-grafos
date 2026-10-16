#ifndef AGM_H
#define AGM_H

typedef struct {
    int *pai, *rank;
    int n;
} DSU;

typedef struct {
    int u, v, peso;
} Aresta;

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

typedef struct {
    int vertice;
    int chave;
} NoHeap;

typedef struct {
    NoHeap *dados;
    int capacidade, tamanho;
    int *posicao;
} MinHeap;

GrafoListaPonderado* criar_grafo(int n);
void adicionar_aresta(GrafoListaPonderado *g, int u, int v, int peso);
void liberar_grafo(GrafoListaPonderado *g);

DSU* criar_dsu(int n);
void liberar_dsu(DSU *d);
int find(DSU *d, int x);
int unir(DSU *d, int x, int y);

MinHeap* criar_min_heap(int capacidade);
void liberar_min_heap(MinHeap *min_heap);
NoHeap extrair_minimo(MinHeap *min_heap);
void diminuir_chave(MinHeap *min_heap, int v, int chave);
int esta_no_min_heap(MinHeap *min_heap, int v);

void kruskal(GrafoListaPonderado *g, Aresta *resultado, int *num_arestas_agm, int *peso_total);
void prim(GrafoListaPonderado *g, int origem, int *pai, int *peso_total);

#endif
