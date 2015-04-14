/*
 * Sparse.h
 *
 *  Created on: 15 Οκτ 2010
 *      Author: P. Skordilakis
 */

#ifndef SPARSE_H_
#define SPARSE_H_
#define BLACK 2
#define RED 1

/*
 * A node in the sparse array is use to store an
 * edge of a graph, the edge have two vertices(vkey and hkey)
 * a color for eatch vertex(ci, cj), if the color of a vertex is
 * BLACK or RED then the vertex has been visited,
 * and a parent(p), wich is the parent node of the edge.
 * To search the sparse array we use pointers(np,pp,up,down);
 */
typedef struct node {
	int vkey, hkey, ci, cj, p;
	struct node *np, *pp, *up, *dp;
	bool status;
}NODE;

typedef struct sparse_array {
	NODE *rowHeads[31];
	NODE *colHeads[31];
}SPARSE;

bool sparseIsEmpty();
bool sparseHasNext(); //Check if an aux has next node
bool sparseHasPrevious(); //Check if an aux has previous node
bool sparseHasUp(); //Check if an aux has upper node
bool sparseHasDown(); //Check if an aux has down node

void sparseNext(); //Set an aux pointing to the next node
void sparsePrevious(); //Set an aux pointing to the previous node
void sparseUp(); //Set an aux pointing to the upper node
void sparseDown(); //set an aux pointing to the down node

NODE *searchSparse( SPARSE *s, int i, int j );

void insertSparse(); //Insert a node in a specific place

void deleteSparse(); //Delete a node from a specific place

void clearSparse(); //Delete every node
void printSparseNode(); //Print a specific node
void printSparseAll(); //Print all the nodes

#endif /* SPARSE_H_ */
