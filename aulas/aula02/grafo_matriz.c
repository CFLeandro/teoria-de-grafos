#include <stdio.h>
#include <string.h>
#include "grafo_matriz.h"

void inicializar(GrafoMatriz *grafo, int numero){
    memset(grafo, 0, sizeof(GrafoMatriz));
}

void inserir_aresta(GrafoMatriz *grafo, int u, int v){
    grafo->adjascencia[u][v] = 1;
}

void inserir_arco(GrafoMatriz *grafo, int u, int v){
    grafo->adjascencia[u][v] = 1;
}

void exibir_matriz(GrafoMatriz *grafo){
    for(int i=0; i < grafo->num_vertices; i++) {
        for(int j=0; j < grafo->num_vertices; j++){
            printf("%31", grafo->adjascencia[i][j]);
        }
        printf("\n");
    }
}