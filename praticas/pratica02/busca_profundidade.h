#ifndef BUSCA_PROFUNDIDADE_H
#define BUSCA_PROFUNDIDADE_H

#include "grafo_lista.h"

typedef struct {
    int *dados;
    int topo, capacidade;
} Pilha;

Pilha* criar_pilha(int capacidade);
void empilhar(Pilha *p, int valor);
int desempilhar(Pilha *p);
int pilha_vazia(Pilha *p);
void liberar_pilha(Pilha *p);

void dfs_recursiva(GrafoLista *g, int u, int *visitado, int *pred);
int contar_componentes(GrafoLista *g);
int tem_ciclo(GrafoLista *g);

#endif
