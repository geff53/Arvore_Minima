/* ***************************************** */
/* Aluno: Emanuel Gefferson Maciel Sampaio   */
/* CES-11: Algoritmos para grafos            */
/* Turma T3                                  */
/* ***************************************** */

#include "graph.h"

int main(void){

    GRAPH *graph = graph_read();
    Arv_MST(graph, 0);
    graph_destroy(graph);
    return 0;
}
