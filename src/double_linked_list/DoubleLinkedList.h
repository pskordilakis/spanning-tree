/*
 * DoubleLinkedList.h
 *
 * Created on : Oct 8 2010
 *     Author : P. Skordilakis
 */

#ifndef DOUBLELINKEDLIST_H
#define DOUBLELINKEDLIST_H

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

typedef struct dll_node {
    int nodei, nodej;
    struct dll_node *np, *pp;
} DLL_NODE;

typedef struct dll {
    DLL_NODE *head, *tail;
} DLL;

int dl_is_empty(DLL_NODE *head);
int dll_has_next(DLL_NODE *aux);
void dll_next(DLL_NODE **aux);
int dll_has_previous(DLL_NODE *aux);
void dll_previous(DLL_NODE **aux);
int dll_node_exist(DLL_NODE *aux, int i, int j);
DLL_NODE *dll_search(DLL *dll, int i, int j);
int dll_insert(DLL *dll, int i, int j);
int dll_delete(DLL *dll, int i, int j);
DLL *dll_union(DLL *setA, DLL *setB);
DLL *dll_intersect(DLL *setA, DLL *setB);
DLL *dll_minus(DLL *setA, DLL *setB);
void dll_clear(DLL *dll);
void dll_print(DLL *dll);

#endif /* DOUBLELINKEDLIST_H_ */