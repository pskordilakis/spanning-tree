#include "../includes/graph.h"

void graph_insert_edge(GRAPH *graph, int i, int j) {
    sparse_insert(graph->sparse, i, j);
    if (i != j) {
        sparse_insert(graph->sparse, j, i);
    }
}

void graph_delete_edge(GRAPH *graph, int i, int j) {
    sparse_delete(graph->sparse, i, j);
    if (i != j) {
        sparse_delete(graph->sparse, i, j);
    }
}

void graph_find_parent(GRAPH *graph, DLL *dll, int vertex) {
    NODE *edge = graph->sparse->rowHeads[vertex];
    while (edge != NULL) {
        if (edge->status == 0) {
            if (vertex != graph->root) {
                dll_insert(dll, edge->vkey, edge->hkey);
                dll_insert(dll, edge->hkey, edge->vkey);
                graph_find_parent(graph, dll, edge->p);
            }
            break;
        }

        if (!sparse_has_next(edge)) {
            break;
        }
        sparse_next(&edge);
    }
}

void graph_find_circles(GRAPH *graph, NODE *edge) {
    if (edge->status != 0) {
        puts("The edge you chose does not create cycles");
    } else {
        DLL *setA = malloc(sizeof (QUEUE));
        DLL *setB = malloc(sizeof (QUEUE));
        graph_find_parent(graph, setA, edge->vkey);
        graph_find_parent(graph, setB, edge->hkey);
        DLL *setU = dll_union(setA, setB);
        DLL *setI = dll_intersect(setA, setB);
        DLL *setM = dll_minus(setU, setI);
        dll_clear(setU);
        free(setU);
        dll_clear(setI);
        free(setI);
        printf("The circle has the following edges :\n%d->%d ", edge->vkey, edge->hkey);
        dll_print(setM);
        dll_clear(setM);
        free(setM);
    }
}

void graph_print_tree(GRAPH *graph) {
    int counter;
    for (counter = 0; counter < 30; counter++) {
        NODE *aux = graph->sparse->rowHeads[counter];
        while (aux != NULL) {
            if (aux->status == 1) {
                printf("%d->%d\n", aux->vkey, aux->hkey);
            }
            if (!sparse_has_next(aux)) {
                break;
            }
            sparse_next(&aux);
        }
        if (aux != NULL) {
            puts("");
        }
    }
}

void graph_print_deactivated_edges(GRAPH *graph) {
    int counter;
    for (counter = 0; counter < 31; counter++) {
        NODE *aux = graph->sparse->rowHeads[counter];
        while (aux != NULL) {
            if (aux->status != 1) {
                printf("%d->%d\n", aux->vkey, aux->hkey);
            }
            if (!sparse_has_next(aux)) {
                break;
            }
            sparse_next(&aux);
        }
        if (aux != NULL) {
            puts("");
        }
    }
}

void graph_mark_node_visited(GRAPH *graph, int node) {
    NODE *aux = graph->sparse->rowHeads[node];
    while (aux != NULL) {
        NODE *aux2 = sparse_search(graph->sparse, aux->hkey, aux->vkey);
        if (aux->ci != BLACK && aux->ci != RED) {
            aux->ci = RED;
            aux2->cj = RED;
        }
        if (!sparse_has_next(aux)) {
            break;
        }
        sparse_next(&aux);
    }
}

void graph_work_with_node(GRAPH *graph, QUEUE *visited, int vertex) {
    NODE *aux = graph->sparse->rowHeads[vertex];
    while (aux != NULL) {
        NODE *aux2 = sparse_search(graph->sparse, aux->hkey, aux->vkey);
        aux->ci = BLACK;
        aux2->cj = BLACK;
        if (aux->cj != BLACK && aux->cj != RED) {
            graph_mark_node_visited(graph, aux->hkey);
            q_enqueue(visited, aux->hkey);
            aux->p = vertex;
            aux2->p = vertex;
        } else if (aux->cj == RED) {
            aux->status = 0;
            aux2->status = 0;
        }

        if (!sparse_has_next(aux)) {
            break;
        }
        sparse_next(&aux);
    }
}

void graph_bfs(GRAPH *graph, QUEUE *visited) {
    ;
    /*
     * The algorithm starts from the vertex that you
     * want as root in the spanning tree
     */
    q_enqueue(visited, graph->root); //Enqueue root in the visited set
    while (visited->head != NULL) {//while the visited set not empty
        QNODE *node = q_dequeue(visited); //dequeue the first node
        int workingNode = node->data;
        free(node);
        graph_work_with_node(graph, visited, workingNode);
    }
}

