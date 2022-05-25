/* ***************************************** */
/* Aluno: Emanuel Gefferson Maciel Sampaio   */
/* CES-11: Algoritmos para grafos            */
/* Turma T3                                  */
/* ***************************************** */

#include <assert.h>
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "graph.h"
#include "stack.h"

typedef struct edge EDGE;

struct edge {
    int index;
    int weight;
    EDGE *next;
};

struct graph {
  int order;
  EDGE **vertex;
};


GRAPH *graph_read() {
    int ordem, vertice_1, vertice_2, peso;
    scanf("%d", &ordem);
    GRAPH *grafo = graph_create(ordem);
    while ((scanf("%d %d %d", &vertice_1, &vertice_2, &peso)) != EOF){
        graph_add_edge(grafo, vertice_1, vertice_2, peso);
        graph_add_edge(grafo, vertice_2, vertice_1, peso);
    }

    return grafo;
}

GRAPH *graph_create(int order) {
    GRAPH *grafo = (GRAPH*)malloc(sizeof(GRAPH));
    grafo->order = order;
    grafo->vertex = (EDGE**)malloc(order*sizeof(EDGE*));

    for(int i=0; i<order; i++){
        grafo->vertex[i] = NULL;
    }

    return grafo;
}

void graph_destroy(GRAPH *graph) {
    if(graph != NULL){
        EDGE *temp;
        for(int i=0; i<graph->order; i++){
            for(EDGE *p = graph->vertex[i]; p != NULL; p = temp){
                temp = p->next;
                free(p);
            }
        }
        free(graph->vertex);
        free(graph);
    }
}

static EDGE *graph_create_edge(int v, int w) {
    EDGE *aresta = (EDGE*)malloc(sizeof(EDGE));
    aresta->index = v;
    aresta->weight = w;
    aresta->next = NULL;
    return aresta;
}

void graph_add_edge(GRAPH *graph, int u, int v, int w) {
    EDGE *aresta = graph_create_edge(v,w);
    if(graph->vertex[u] != NULL){
        for(EDGE *p = graph->vertex[u]; p != NULL; p = p->next){
            if(p->next != NULL){
                if(v>p->index && v<p->next->index){
                    aresta->next = p->next;
                    p->next = aresta;
                }
            }
            else{
                p->next = aresta;
                break;
            }
        }
    }
    else{
         graph->vertex[u] = aresta;
    }
}

bool graph_has_edge(const GRAPH *graph, int u, int v) {
    for(EDGE *p = graph->vertex[u]; p != NULL; p = p->next){
        if(p->index == v){
            return true;
        }
    }

    return false;
}

int graph_edge_weight(const GRAPH *graph, int u, int v) {
    if(graph->vertex[u] == NULL){
        return -1;
    }
    else{
        EDGE *aresta = graph->vertex[u];
        while(aresta != NULL && aresta->index != v){
            aresta = aresta->next;
        }
        return aresta->weight;
    }
}

typedef enum { PINK, BLUE } COLOR;

void arvore_minima(const GRAPH *graph, STACK *arvore,  int u, COLOR *color, int *previous, int *chave){

    if(color[u] == PINK){
        return;
    }

    color[u] = PINK;
    stack_push(arvore, u);

    for(int x=0; x<graph->order; x++){
        if(graph_has_edge(graph, u, x) == true && color[x] == BLUE){
            if(chave[x] > graph_edge_weight(graph, u, x)){
                previous[x] = u;
                chave[x] = graph_edge_weight(graph, u, x);
            }
        }
    }
    int menor_dist, posicao;
    menor_dist = INT_MAX;
    posicao = -1;
    for(int i=0; i<graph->order; i++){
        if(chave[i]<menor_dist && color[i] == BLUE){
            menor_dist = chave[i];
            posicao = i;
        }
    }
    if(posicao != -1){
        arvore_minima(graph, arvore, posicao, color, previous, chave);
    }
    return;
}

void Arv_MST(const GRAPH *graph, int u) {

    STACK *arv_min = stack_create();

    COLOR *cor = (COLOR*)malloc(graph->order*sizeof(COLOR));
    for(int i=0; i<graph->order; i++){
        cor[i] = BLUE;
    }

    int *previous = (int*)malloc(graph->order*sizeof(int));
    for(int i=0; i<graph->order; i++){
        previous[i] = -1;
    }

    int *chave = (int*)malloc(graph->order*sizeof(int));
    chave[u] = 0;
    for(int i=0; i<graph->order; i++){
        if(i != u){
           chave[i] = INT_MAX;
        }
    }

    for(int i=0; i<graph->order; ++i){
        arvore_minima(graph, arv_min, i, cor, previous, chave);
    }

    int *vertices = (int*)malloc(graph->order*sizeof(int));
    for(int i=graph->order-1; i>=0; i--){
        if(stack_isEmpty(arv_min) == false){
            vertices[i] = stack_top(arv_min);
            stack_pop(arv_min);
        }
    }

    for(int i=0; i<graph->order; i++){
        if(vertices[i] != u){
            printf("%d %d %d\n", vertices[i], previous[vertices[i]], chave[vertices[i]]);
        }
    }
    free(cor);
    free(arv_min);
    free(chave);
    free(previous);
    free(vertices);
}
