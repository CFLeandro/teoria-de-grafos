#include <stdio.h>
#include <stdlib.h>
#include "grafo_lista.h"

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

void bfs(GrafoLista *g, int u, int *visitado) {
    int fila[10];
    int inicio = 0;
    int final = 0;

    visitado[u] = 1;
    fila[final++] = u;
    printf("Visita %i, Enfileira %i \n", u+1, u+1);
    

    while(inicio < final) {
        int i = fila[inicio++];
        print("Desinfilera\n", i+1);
        No *no = g->lista[u];

        while(no != NULL){
            int v = no->vertices;
            if(!visitado[v]){
                visitado[v] = 1;
                printf("Enfileira %i \n", u+1);
                fila[final++] = v;
            }
            no = no->proximo;
        }
    }
}