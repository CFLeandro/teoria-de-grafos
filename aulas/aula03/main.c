#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "grafo_lista.h"
#include "busca_grafo.h"

int main(){
    GrafoLista *grafo = criar_grafo(5);

    adcionar_aresta(grafo, 0, 1);
    adcionar_aresta(grafo, 0, 2);
    adcionar_aresta(grafo, 1, 3);
    adcionar_aresta(grafo, 2, 3);
    adcionar_aresta(grafo, 3, 4);

    for(int i = 0; i<grafo->num_vertices; i++) {
        printf("%i: -> ", i+1);
        No *no = grafo->lista[i];

        while(no != NULL){
            printf("%i -> ", no->vertices + 1);
            no = no->proximo;
        }
        printf("Null\n");
    }
    //BUSCA
    int pilha[10];
    int visitado[10];

    memset(visitado, 0, sizeof(visitado));
    printf("\n==Inicia dfs pelo vertice 1==\n");
    dfs(grafo, 0, pilha, visitado);
    printf("\n");
    
    memset(visitado, 0, sizeof(visitado));
    printf("\n==Inicia dfs pelo vertice 2==\n");
    dfs(grafo, 1, pilha, visitado);
    printf("\n");

    memset(visitado, 0, sizeof(visitado));
    printf("\n==Inicia dfs pelo vertice 3==\n");
    dfs(grafo, 2, pilha, visitado);
    printf("\n");
    
    memset(visitado, 0, sizeof(visitado));
    printf("\n==Inicia dfs pelo vertice 4==\n");
    dfs(grafo, 3, pilha, visitado);
    printf("\n");

    memset(visitado, 0, sizeof(visitado));
    printf("\n==Inicia dfs pelo vertice 5==\n");
    dfs(grafo, 4, pilha, visitado);
    printf("\n");


    return 0;
}