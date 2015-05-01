/* 
 * File:   graph.h
 * Author: panos
 *
 * Created on April 29, 2015, 9:18 PM
 */

#ifndef GRAPH_H
#define	GRAPH_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

#include "../includes/double_linked_list.h"
#include "../includes/queue.h"
#include "../includes/sparse.h"

    typedef struct graph {
        SPARSE *sparse;
        int root;
    } GRAPH;

    /*
     * Sparse array holds the edges of a graph
     * because the graph is undirected we insert
     * node1->node2 and node2->node1
     */
    void graph_insert_edge(GRAPH *graph, int i, int j);

    /*
     * Delete an edge from the graph
     */
    void graph_delete_edge(GRAPH *graph, int i, int j);

    /*
     * Starting from a vertex, finds the path to the
     * root of the spanning tree
     */
    void graph_find_parent(GRAPH *graph, DLL *dll, int vertex);

    /*
     * To find circles in a graph we start from a deactivated
     * edge, we find the path to the root for both vertices
     * and then we find the edges that form a circle
     * (Union(pathA, pathB)-Intesect(pathA, pathB))
     */
    void graph_find_circles(GRAPH *graph, NODE *edge);

    /*
     * Prints all the edges of the graph which are active,
     * i.e. prints the spanning tree of the graph
     */
    void graph_print_tree(GRAPH *graph);

    /*
     * Prints all the edges of the graph which are deactivated
     * i.e. prints the edges that form circles in the graph
     */
    void graph_print_deactivated_edges(GRAPH *graph);

    /*
     * Find all edges that connect a nodeA with
     * a nodeB and mark nodeA visited
     */
    void graph_mark_node_visited(GRAPH *graph, int node);

    /*
     * Mark the vertexA black, then check every edge that
     * connects the vertexA with a vertexB,
     * if vertexB is marked visited then deactivate the edge,
     * else mark vertexB visited in every edge that connect
     * vertexB with another node
     */
    void graph_work_with_node(GRAPH *graph, QUEUE *visited, int vertex);

    /*
     * Create a spanning tree of the graph
     * using the Breadth First Search algorithm
     */
    void graph_bfs(GRAPH *graph, QUEUE *visited);

#ifdef	__cplusplus
}
#endif

#endif	/* GRAPH_H */

