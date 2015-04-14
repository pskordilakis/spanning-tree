/*
 * DoubleLinkedList.h
 *
 * Created on : Oct 8 2010
 *     Author : P. Skordilakis
 */

#ifndef DOUBLELINKEDLIST_H_
#define DOUBLELINKEDLIST_H_

/*
 * Use for finding Circles in the graph
 * represnts a graph edge
 */
typedef struct dll_node {
	int nodei, nodej;
	struct dll_node *np, *pp;
}DLL_NODE;

typedef struct dll {
	DLL_NODE  *head, *tail;
}DLL;
#endif /* DOUBLELINKEDLIST_H_ */

bool dllIsEmpty( DLL_NODE *head );
bool dllHasNext( DLL_NODE *aux );
bool dllHasPrevious( DLL_NODE *aux );
bool dllNodeExist( DLL_NODE *aux, int i, int j );
void dllNext( DLL_NODE **aux );
void dllPrevious( DLL_NODE **aux );
DLL_NODE *searchDll( DLL *dll, int i, int j );
void insertDll( DLL *dll, int i, int j );
void deleteDll( DLL *dll, int i, int j );
DLL *dllUnion(DLL *setA, DLL *setB );
DLL *dllIntersect(DLL *setA, DLL *setB );
DLL *dllMinus(DLL *setA, DLL *setB);
void clearDll( DLL *dll );
void printDllAll( DLL *dll );
