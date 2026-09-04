#include <stdio.h>
#include <stdlib.h>
#include "grafo_lista.h"

int topo = 0;

void dfs(GrafoLista *g, int u, int *p, int *visitado){
    visitado[u] = 1;
    p[topo++] = u; //Empilha vertice
    printf("Empilha %i, visita %i\n", u+1, u+1);
    No *no = g->lista[u];

    while(no != NULL){
        int v = no->vertices;
        if(!visitado[v]) dfs(g, v, p, visitado); //Pilha recursiva
        no = no->proximo;
    }
    topo--; //Desempilha vertice
    printf("Desempilha %i\n", u+1);
}