/*
 * spanning.c
 *
 *  Created on: 10 Νοε 2010
 *      Author: P. Skordilakis
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <iso646.h>
#include <malloc.h>


#include "includes/graph.h"
#include "includes/double_linked_list.h"
#include "includes/queue.h"
int root;

/*
 * The menu to insert an edge in the graph
 */
void commandInsertEdges(GRAPH *graph) {
    int vertexi, vertexj;
    vertexi = vertexj = -1;
    while ((vertexi <= 0 or vertexi >= 31) or(vertexj <= 0 or vertexj >= 31)) {
        puts("Type the edge you want to insert(va-vb)");
        scanf("%d-%d", &vertexi, &vertexj);
        getchar();
    }
    graph_insert_edge(graph, vertexi, vertexj);
}

/*
 * The menu to delete an edge from the graph
 */
void commandDeleteEdges(GRAPH *graph) {
    int vertexi, vertexj;
    vertexi = vertexj = -1;
    while ((vertexi <= 0 or vertexi >= 31) or(vertexj <= 0 or vertexj >= 31)) {
        puts("Type the edge you want to insert(va-vb)");
        scanf("%d-%d", &vertexi, &vertexj);
        getchar();
    }
    graph_delete_edge(graph, vertexi, vertexj);
}

/*
 * The menu to find circles in the graph
 */
void commandCircles(GRAPH *graph) {
    int nodei, nodej;
    puts("Choose an edge from below to find the circle in the graph(va-vb)");
    graph_print_deactivated_edges(graph);
    scanf("%d-%d", &nodei, &nodej);
    getchar();
    NODE *edge = sparse_search(graph->sparse, nodei, nodej);
    graph_find_circles(graph, edge);
}

/*
 * Menu with printing options
 */
void commandPrint(GRAPH *graph) {
    int subchoice = -1;
    while (subchoice not_eq 0) {
        puts("Please Choose :\n\t1. Graph\n\t2. Tree\n\t0. Back");
        scanf("%d", &subchoice);
        getchar();
        switch (subchoice) {
            case 1:
            {
                sparse_print_all(graph->sparse);
                break;
            }
            case 2:
            {
                graph_print_tree(graph);
                break;
            }
        }
    }
}

int main() {

    GRAPH *graph = malloc(sizeof (GRAPH));
    graph->sparse = malloc(sizeof (SPARSE));
    QUEUE *visited = malloc(sizeof (QUEUE));

    int choice;

    for (choice = 0; choice < 30; choice++) {
        graph->sparse->rowHeads[choice] = NULL;
        graph->sparse->colHeads[choice] = NULL;
    }

    while (choice not_eq 0) {
        printf("Please Choose :\n\t1. Insert an edge\n\t2. Delete an edge\n\t3. BFS\n\t4. Cicles\n\t"
                "5. Print\n\t0. Quit\n");
        scanf("%d", &choice);
        getchar();
        switch (choice) {
            case 1:
            {
                commandInsertEdges(graph);
                break;
            }
            case 2:
            {
                commandDeleteEdges(graph);
                break;
            }
            case 3:
            {
                //set root node in graph
                puts("Type root vertex of graph for the spannign tree");
                scanf("%d", &(graph->root));
                graph_bfs(graph, visited);
                break;
            }
            case 4:
            {
                commandCircles(graph);
                break;
            }
            case 5:
            {
                commandPrint(graph);
                break;
            }
        }
    }
    return EXIT_SUCCESS;
}
