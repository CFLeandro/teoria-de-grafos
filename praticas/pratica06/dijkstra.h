#ifndef DIJKSTRA_H
#define DIJKSTRA_H

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

typedef struct {
    int vertice;
    int distancia;
} NoHeap;

typedef struct {
    NoHeap *dados;
    int capacidade, tamanho;
    int *posicao; // mapeia vértice -> índice no heap
} MinHeap;

GrafoListaPonderado* criar_grafo(int n);
void adicionar_aresta(GrafoListaPonderado *g, int u, int v, int peso);
void liberar_grafo(GrafoListaPonderado *g);

MinHeap* criar_min_heap(int capacidade);
void liberar_min_heap(MinHeap *min_heap);
NoHeap extrair_minimo(MinHeap *min_heap);
void diminuir_chave(MinHeap *min_heap, int v, int distancia);
int esta_no_min_heap(MinHeap *min_heap, int v);

void dijkstra(GrafoListaPonderado *g, int origem, int *dist, int *pred);
void reconstruir_caminho(int origem, int destino, int *pred);

#endif
