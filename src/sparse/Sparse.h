/*
 * Sparse.h
 *
 *  Created on: 15 Οκτ 2010
 *      Author: P. Skordilakis
 */

#ifndef SPARSE_H_
#define SPARSE_H_

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

#define BLACK 2
#define RED 1

/*
 * A node in the sparse array is use to store an
 * edge of a graph, the edge have two vertices(vkey and hkey)
 * a color for each vertex(ci, cj), if the color of a vertex is
 * BLACK or RED then the vertex has been visited,
 * and a parent(p), which is the parent node of the edge.
 * To search the sparse array we use pointers(np,pp,up,down);
 */
typedef struct node {
	int vkey, hkey, ci, cj, p;
	struct node *np, *pp, *up, *dp;
	int status;
}NODE;

typedef struct sparse_array {
	NODE *rowHeads[31];
	NODE *colHeads[31];
}SPARSE;

int sparse_is_empty(NODE *head);
int sparse_has_next(NODE *aux); //Check if an aux has next node
int sparse_has_previous(NODE *aux); //Check if an aux has previous node
int sparse_has_up(NODE *aux); //Check if an aux has upper node
int sparse_has_down(NODE *aux); //Check if an aux has down node

void sparse_next(NODE **aux); //Set an aux pointing to the next node
void sparse_previous(NODE **aux); //Set an aux pointing to the previous node
void sparse_up(NODE **aux); //Set an aux pointing to the upper node
void sparse_down(NODE **aux); //set an aux pointing to the down node

NODE *sparse_search( SPARSE *s, int i, int j );

int sparse_insert(SPARSE *s, int i, int j); //Insert a node in a specific place

int sparse_delete(SPARSE *s, int i, int j); //Delete a node from a specific place

void sparse_clear(); //Delete every node
void sparse_print(SPARSE *s, int i, int j); //Print a specific node
void sparse_print_all(SPARSE *s); //Print all the nodes

#endif /* SPARSE_H_ */
