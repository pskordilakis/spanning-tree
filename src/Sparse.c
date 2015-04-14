/*
 * Sparse.c
 *
 *  Created on: 15 Οκτ 2010
 *      Author: P. Skordilakis
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <iso646.h>
#include <malloc.h>
#include "Sparse.h"

/*
 * Check if a list in the sparse array has nodes
 */
bool sparseIsEmpty( NODE *head ) {
	if ( head not_eq NULL ) {
		return false;
	}
	return true;
}

/*
 * check if a node points to another (np)
 */
bool sparseHasNext( NODE *aux ) {
	if ( aux->np not_eq NULL ) {
		return true;
	}
	return false;
}

/*
 * check if a node points to another (pp)
 */
bool sparseHasPrevious( NODE *aux ) {
	if ( aux->pp not_eq NULL ) {
		return true;
	}
	return false;
}

/*
 * check if a node points to another (up)
 */
bool sparseHasUp( NODE *aux ) {
	if ( aux->up not_eq NULL ) {
		return true;
	}
	return false;
}

/*
 * check if a node points to another (dp)
 */
bool sparseHasDown( NODE *aux ) {
	if ( aux->dp not_eq NULL ) {
		return true;
	}
	return false;
}

/***************************************************************************/

/*
 * Move aux to the next node
 */
void sparseNext( NODE **aux ) {
	*aux = (*aux)->np;
}

/*
 * Move aux to the previous node
 */
void sparsePrevious( NODE **aux ) {
	*aux = (*aux)->pp;
}

/*
 * Move aux up
 */
void sparseUp( NODE **aux ) {
	*aux = (*aux)->up;
}

/*
 * Move aux down
 */
void sparseDown(NODE **aux) {
	*aux = (*aux)->dp;
}

/***************************************************************************************************************/

/*
 * Check if a node exist in the sparse array
 */
bool sparseNodeExist( NODE *aux, int i, int j ) {
	if ( aux not_eq NULL and aux->vkey == i and aux->hkey == j) {
		return true;
	}
	return false;
}
/***************************************************************************************************************/

/*
 * Find a specific node in the sparse array
 */
NODE *searchSparse( SPARSE *s, int i, int j ) {
	NODE *aux = s->rowHeads[i];
	while (  aux not_eq NULL and sparseHasNext(aux) and aux->hkey < j ){
		sparseNext(&aux);
	}
	return aux;
}

/***************************************************************************************************************/

/*
 * Insert a node in the array
 */
void insertSparse( SPARSE *s, int i, int j ) {

	NODE *aux = s->rowHeads[i];
	while (  aux not_eq NULL and sparseHasNext(aux) and aux->hkey < j ){
		sparseNext(&aux);
	}

	if ( sparseNodeExist( aux, i, j ) ) {
		puts("The node exist");
	}
	else {
		NODE *newNode = malloc(sizeof(NODE));
		newNode->vkey = i;
		newNode->hkey = j;
		newNode->ci = newNode->cj = 0;
		newNode->status=true;

		if ( aux == NULL ) {
			s->rowHeads[i] = newNode;
			newNode->np = NULL;
			newNode->pp = NULL;
		}
		else {
			if ( not sparseHasPrevious(aux) and aux->hkey > j ) {
				s->rowHeads[i] = newNode;
				newNode->pp = NULL;
				newNode->np = aux;
				aux->pp = newNode;
			}
			else {
				if ( not sparseHasNext( aux ) and aux->hkey < j ) {//Insert at the end
					aux->np = newNode;
					newNode->np = NULL;
					newNode->pp = aux;
				}
				else {//Insert in the middle
					newNode->np = aux;
					newNode->pp = aux->pp;
					aux->pp->np = newNode;
					aux->pp = newNode;
				}
			}
		}

		aux = s->colHeads[j];
		while (  aux not_eq NULL and sparseHasDown(aux) and aux->vkey < i ){
			sparseDown(&aux);
		}

		if ( aux == NULL ) {
			s->colHeads[j] = newNode;
			newNode->dp = NULL;
			newNode->up = NULL;
		}
		else {
			if ( not sparseHasUp(aux) and aux->vkey > i ) {
				s->colHeads[j] = newNode;
				newNode->up = NULL;
				newNode->dp = aux;
				aux->up = newNode;
			}
			else {
				if ( not sparseHasDown( aux ) and aux->vkey < i ) {//Insert at the end
					aux->dp = newNode;
					newNode->dp = NULL;
					newNode->up = aux;
				}
				else {//Insert in the middle
					newNode->dp = aux;
					newNode->up = aux->up;
					aux->up->dp = newNode;
					aux->up = newNode;
				}
			}
		}
	}
}

/***************************************************************************************************************/

/*
 * Delete a node from the array
 */
void deleteSparse( SPARSE *s, int i, int j ) {

	NODE *aux = searchSparse( s, i, j );

	if( not sparseNodeExist( aux, i, j ) ) {
		puts("The node does not exist");
	}
	else {
		if ( not sparseHasNext(aux) and not sparseHasPrevious(aux) ) {//if the list has only one node
			s->rowHeads[i] = NULL;
		}
		else if ( not sparseHasNext(aux) ) {//Delete last node
			aux->pp->np = NULL;
		}
		else if ( not sparseHasPrevious(aux)) {//delete first node
			s->rowHeads[i] = aux->np;
			aux->np->pp = NULL;
		}
		else {
			aux->pp->np = aux->np;
			aux->np->pp = aux->pp;
		}

		if ( not sparseHasDown(aux) and not sparseHasUp(aux) ) {//if the list has only one node
			s->colHeads[j] = NULL;
		}
		else if ( not sparseHasDown(aux) ) {//Delete last node
			aux->up = NULL;
		}
		else if ( not sparseHasUp(aux)) {//delete first node
			s->colHeads[j] = aux->dp;
			aux->dp->up = NULL;
		}
		else {
			aux->up->dp = aux->dp;
			aux->dp->up = aux->up;
		}
		free(aux);
	}
}

/*
 * Delete every node from the array
 */
void clearSparse() {

}

/***************************************************************************************************************/

/*
 * Print a specific node in the array
 */
void printSparseNode( SPARSE *s, int i, int j ) {
	NODE *vaux, *haux;
	vaux = searchSparse( s, i,j);
	haux = searchSparse( s, j,i);
	if ( haux not_eq NULL and haux->hkey == j and vaux not_eq NULL and vaux->vkey == i ) {
		printf( "%d->%d\n", vaux->vkey, vaux->hkey );
	}
	else {
		puts("The node do not exist");
	}
}

/*
 * Print all nodes in the array
 */
void printSparseAll( SPARSE *s ) {
	int counter;
	for ( counter = 0; counter<31; counter++ ) {
		NODE *vaux = s->rowHeads[counter];
		while ( vaux not_eq NULL ) {
			printf("%d->%d; ",vaux->vkey, vaux->hkey );
			if ( not sparseHasNext(vaux) ) {
				break;
			}
			sparseNext(&vaux);
		}
		if ( vaux not_eq NULL ) {
			puts("");
		}
	}
}
