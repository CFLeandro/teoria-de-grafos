#include <stdio.h>
#include <stdlib.h>
#include "dag.h"

// --- Estrutura de Fila Auxiliar ---
typedef struct {
    int *dados, cap, inicio, fim, tamanho;
} Fila;

static Fila* criar_fila(int cap) {
    Fila *f = (Fila*) malloc(sizeof(Fila));
    f->cap = cap; f->tamanho = 0; f->inicio = 0; f->fim = -1;
    f->dados = (int*) malloc(cap * sizeof(int));
    return f;
}
static void enfileirar(Fila *f, int v) {
    if (f->tamanho < f->cap) {
        f->fim = (f->fim + 1) % f->cap;
        f->dados[f->fim] = v; f->tamanho++;
    }
}
static int desenfileirar(Fila *f) {
    if (f->tamanho > 0) {
        int v = f->dados[f->inicio];
        f->inicio = (f->inicio + 1) % f->cap; f->tamanho--;
        return v;
    } return -1;
}
static int fila_vazia(Fila *f) { return f->tamanho == 0; }
static void liberar_fila(Fila *f) { free(f->dados); free(f); }

// --- Estrutura de Pilha Auxiliar ---
typedef struct {
    int *dados, topo, cap;
} Pilha;

static Pilha* criar_pilha(int cap) {
    Pilha *p = (Pilha*) malloc(sizeof(Pilha));
    p->cap = cap; p->topo = -1;
    p->dados = (int*) malloc(cap * sizeof(int));
    return p;
}
static void empilhar(Pilha *p, int v) {
    if (p->topo < p->cap - 1) p->dados[++(p->topo)] = v;
}
static int desempilhar(Pilha *p) {
    if (p->topo >= 0) return p->dados[(p->topo)--];
    return -1;
}
static void liberar_pilha(Pilha *p) { free(p->dados); free(p); }

// --- Funções Principais ---

int* ordenacao_topologica_kahn(GrafoLista *g, int *tamanho) {
    int *grau_entrada = (int*) calloc(g->n, sizeof(int));
    for (int i = 0; i < g->n; i++) {
        No *atual = g->adj[i];
        while (atual != NULL) {
            grau_entrada[atual->destino]++;
            atual = atual->prox;
        }
    }

    Fila *f = criar_fila(g->n);
    for (int i = 0; i < g->n; i++) {
        if (grau_entrada[i] == 0) enfileirar(f, i);
    }

    int *ordem = (int*) malloc(g->n * sizeof(int));
    int count = 0;

    while (!fila_vazia(f)) {
        int u = desenfileirar(f);
        ordem[count++] = u;

        No *atual = g->adj[u];
        while (atual != NULL) {
            int v = atual->destino;
            grau_entrada[v]--;
            if (grau_entrada[v] == 0) enfileirar(f, v);
            atual = atual->prox;
        }
    }

    free(grau_entrada);
    liberar_fila(f);

    if (count == g->n) {
        *tamanho = count;
        return ordem;
    } else {
        free(ordem);
        *tamanho = 0;
        return NULL; // Possui ciclo
    }
}

static void dfs_visit(GrafoLista *g, int u, int *estado, Pilha *p, int *tem_ciclo) {
    estado[u] = 1; // Visitando
    No *atual = g->adj[u];
    while (atual != NULL) {
        int v = atual->destino;
        if (estado[v] == 1) {
            *tem_ciclo = 1;
            return;
        }
        if (estado[v] == 0) {
            dfs_visit(g, v, estado, p, tem_ciclo);
        }
        atual = atual->prox;
    }
    estado[u] = 2; // Visitado
    empilhar(p, u);
}

int* ordenacao_topologica_dfs(GrafoLista *g, int *tamanho) {
    int *estado = (int*) calloc(g->n, sizeof(int)); // 0: branco, 1: cinza, 2: preto
    Pilha *p = criar_pilha(g->n);
    int tem_ciclo = 0;

    for (int i = 0; i < g->n; i++) {
        if (estado[i] == 0) {
            dfs_visit(g, i, estado, p, &tem_ciclo);
            if (tem_ciclo) break;
        }
    }

    free(estado);

    if (tem_ciclo) {
        liberar_pilha(p);
        *tamanho = 0;
        return NULL;
    }

    int *ordem = (int*) malloc(g->n * sizeof(int));
    *tamanho = g->n;
    for (int i = 0; i < g->n; i++) {
        ordem[i] = desempilhar(p);
    }
    
    liberar_pilha(p);
    return ordem;
}

int eh_dag(GrafoLista *g) {
    int tamanho;
    int *ordem = ordenacao_topologica_kahn(g, &tamanho);
    if (ordem != NULL) {
        free(ordem);
        return 1; // É um DAG
    }
    return 0; // Contém ciclo, não é DAG
}
