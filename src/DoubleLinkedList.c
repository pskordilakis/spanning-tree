/*
 * DoubleLinkedList.c
 *
 * Created on : Oct 8 2010
 *     Author : P. Skordilakis
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <iso646.h>
#include <malloc.h>
#include "DoubleLinkedList.h"

/*
 * Check if a list in the sparse array has nodes
 */
bool dllIsEmpty( DLL_NODE *head ) {
	if ( head not_eq NULL ) {
		return false;
	}
	return true;
}

/*
 * check if a node points to another (np)
 */
bool dllHasNext( DLL_NODE *aux ) {
	if ( aux->np not_eq NULL ) {
		return true;
	}
	return false;
}

/*
 * check if a node points to another (pp)
 */
bool dllHasPrevious( DLL_NODE *aux ) {
	if ( aux->pp not_eq NULL ) {
		return true;
	}
	return false;
}
/***************************************************************************/

/*
 * Move aux to the next node
 */
void dllNext( DLL_NODE **aux ) {
	*aux = (*aux)->np;
}

/*
 * Move aux to the previous node
 */
void dllPrevious( DLL_NODE **aux ) {
	*aux = (*aux)->pp;
}

/***************************************************************************************************************/

/*
 * Check if a node exist in a list
 */
bool dllNodeExist( DLL_NODE *aux, int i, int j ) {
	if ( aux not_eq NULL and aux->nodei == i and aux->nodej == j) {
		return true;
	}
	return false;
}
/***************************************************************************************************************/

/*
 * Find a specific node in a list
 */
DLL_NODE *searchDll( DLL *dll, int i, int j ) {
	DLL_NODE *aux = dll->head;
	while (  aux not_eq NULL and dllHasNext(aux) and ( aux->nodei < i or ( aux->nodei == i  and aux->nodej < j ) ) ) {
		dllNext(&aux);
	}
	return aux;
}

/***************************************************************************************************************/

/*
 * Insert a node in a list
 */
void insertDll( DLL *dll, int i, int j ) {

	DLL_NODE *aux = dll->head;
	while (  aux not_eq NULL and dllHasNext(aux) and ( aux->nodei < i or ( aux->nodei == i  and aux->nodej < j ) ) ) {
		dllNext(&aux);
	}

	if ( dllNodeExist( aux, i, j ) ) {
		//puts("The node exist");
	}
	else {
		DLL_NODE *newNode = malloc(sizeof(DLL_NODE));
		newNode->nodei = i;
		newNode->nodej = j;

		if ( aux == NULL ) {//List is empty
			dll->head = newNode;
			newNode->np = NULL;
			newNode->pp = NULL;
		}
		//Insert in the begining of the list
		else if ( not dllHasPrevious(aux) and ( aux->nodei > i or ( aux->nodei == i  and aux->nodej > j ) )  ) {
			dll->head = newNode;
			newNode->pp = NULL;
			newNode->np = aux;
			aux->pp = newNode;
		}
		//Insert at the end of the list
		else if ( not dllHasNext( aux ) and ( aux->nodei < i or ( aux->nodei == i  and aux->nodej < j ) ) ){//Insert at the end
			aux->np = newNode;
			newNode->np = NULL;
			newNode->pp = aux;
		}
		else {//Insert in any other index of the list
			newNode->np = aux;
			newNode->pp = aux->pp;
			aux->pp->np = newNode;
			aux->pp = newNode;
		}
	}
}

/***************************************************************************************************************/

/*
 * Delete a node from the array
 */
void deleteDll( DLL *dll, int i, int j ) {

	//Find the node to delete
	DLL_NODE *aux = searchDll( dll, i, j );

	if( not dllNodeExist( aux, i, j ) ) {
		//puts("The node does not exist");
	}
	else {
		if ( not dllHasNext(aux) and not dllHasPrevious(aux) ) {//if the list has only one node
			dll->head = NULL;
		}
		else if ( not dllHasNext(aux) ) {//delete last node
			aux->pp->np = NULL;
		}
		else if ( not dllHasPrevious(aux)) {//delete first node
			dll->head = aux->np;
			aux->np->pp = NULL;
		}
		else {
			aux->pp->np = aux->np;
			aux->np->pp = aux->pp;
		}
		free(aux);
	}
}

/*
 * Delete every node from the list
 */
void clearDll( DLL *dll ) {
	DLL_NODE *aux = dll->head;
	while ( aux not_eq NULL ) {
		if ( not dllHasNext(aux) ) {
			free(aux);
			break;
		}
		dllNext(&aux);
		free(aux->pp);
	}
	dll->head = NULL;
	dll->tail = NULL;
}

/************************************************************************************/

/*
 * dllUnion, dllIintersect and dllMinus
 *will be used to find the cycles of a graph
 */

/*
 * Insert both lists in a new list
 * because the insertion is sorted and
 * the list do not accept identical nodes
 * the new list is the union of the two lists
 */
DLL *dllUnion(DLL *setA, DLL *setB ) {

	DLL *setC = malloc(sizeof(DLL));

	DLL_NODE *auxA = setA->head;
	DLL_NODE *auxB = setB->head;

	//Insert list A in the new list C
	while ( auxA not_eq NULL ) {
		insertDll(setC,auxA->nodei, auxA->nodej);
		if ( not dllHasNext(auxA) ) {
			break;
		}
		dllNext(&auxA);
	}
	//Insert list B in list C
	while ( auxB not_eq NULL ) {
		insertDll(setC,auxB->nodei, auxB->nodej);
		if ( not dllHasNext(auxB) ) {
			break;
		}
		dllNext(&auxB);
	}
	return setC;
}

/*
 * For every node in the list A check if the node exist in
 * list B, if exist inserted in list C
 */
DLL *dllIntersect(DLL *setA, DLL *setB ) {
	DLL *setC = malloc(sizeof(DLL));
	DLL_NODE *auxA = setA->head;
	while ( auxA not_eq NULL ) {
		DLL_NODE *auxB = searchDll( setB, auxA->nodei, auxA->nodej );
		if ( dllNodeExist( auxB, auxA->nodei, auxA->nodej ) ) {
			insertDll(setC,auxA->nodei, auxA->nodej);
		}
		if ( not dllHasNext(auxA) ) {
			break;
		}
		dllNext(&auxA);
	}
return setC;
}

/*
 * For every node in the list A check if the node exist in
 * list B, if it does ot exist inserted in list C
 */
DLL *dllMinus(DLL *setA, DLL *setB) {
	DLL *setC = malloc(sizeof(DLL));
	DLL_NODE *auxA = setA->head;
	while ( auxA not_eq NULL ) {
		DLL_NODE *auxB = searchDll( setB, auxA->nodei, auxA->nodej );
		if ( not dllNodeExist( auxB, auxA->nodei, auxA->nodej ) ) {
			insertDll(setC,auxA->nodei, auxA->nodej);
		}
		if ( not dllHasNext(auxA) ) {
			break;
		}
		dllNext(&auxA);
	}
	return setC;
}
/***************************************************************************************************************/

/*
 * Print all nodes in the list
 */
void printDllAll( DLL *dll ) {
	DLL_NODE *aux = dll->head;
	while ( aux not_eq NULL ) {
		printf("%d-%d ",aux->nodei, aux->nodej );
		if ( not dllHasNext(aux) ) {
			break;
		}
		dllNext(&aux);
	}
	if ( aux not_eq NULL ) {
		puts("");
	}
}
