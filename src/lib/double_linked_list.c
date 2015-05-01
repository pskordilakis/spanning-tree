/*
 * DoubleLinkedList.c
 *
 * Created on : Oct 8 2010
 *     Author : P. Skordilakis
 */

#include "../includes/double_linked_list.h"

/*
 * Check if a list in the sparse array has nodes
 */
int dll_is_empty(DLL_NODE *head) {
    if (head != NULL) {
        return 0;
    }
    return 1;
}

/*
 * check if a node points to another (np)
 */
int dll_has_next(DLL_NODE *aux) {
    if (aux->np != NULL) {
        return 0;
    }
    return 1;
}

/*
 * check if a node points to another (pp)
 */
int dll_has_previous(DLL_NODE *aux) {
    if (aux->pp != NULL) {
        return 0;
    }
    return 1;
}

/*
 * Move aux to the next node
 */
void dll_next(DLL_NODE **aux) {
    *aux = (*aux)->np;
}

/*
 * Move aux to the previous node
 */
void dll_previous(DLL_NODE **aux) {
    *aux = (*aux)->pp;
}

/*
 * Check if a node exist in a list
 */
int dll_node_exist(DLL_NODE *aux, int i, int j) {
    if (aux != NULL && aux->nodei == i && aux->nodej == j) {
        return 1;
    }
    return 0;
}

/*
 * Find a specific node in a list
 */
DLL_NODE *dll_search(DLL *dll, int i, int j) {
    DLL_NODE *aux = dll->head;
    while (aux != NULL && dll_has_next(aux) 
           && (aux->nodei < i 
           || (aux->nodei == i && aux->nodej < j))
    ) {
        dll_next(&aux);
    }
    return aux;
}

/*
 * Insert a node in a list
 */
int dll_insert(DLL *dll, int i, int j) {

    DLL_NODE *aux = dll->head;
    while (aux != NULL && dll_has_next(aux) 
           && (aux->nodei < i 
           || (aux->nodei == i && aux->nodej < j))
    ) {
        dll_next(&aux);
    }

    if (dll_node_exist(aux, i, j)) {
        return 0;
    } else {
        DLL_NODE *newNode = malloc(sizeof (DLL_NODE));
        newNode->nodei = i;
        newNode->nodej = j;

        if (aux == NULL) {//List is empty
            dll->head = newNode;
            newNode->np = NULL;
            newNode->pp = NULL;
        }            //Insert in the beginning of the list
        else if (!dll_has_previous(aux) 
                 && (aux->nodei > i 
                 || (aux->nodei == i && aux->nodej > j))
        ) {
            dll->head = newNode;
            newNode->pp = NULL;
            newNode->np = aux;
            aux->pp = newNode;
        }            //Insert at the end of the list
        else if (!dll_has_next(aux) 
                 && (aux->nodei < i 
                 || (aux->nodei == i && aux->nodej < j))
        ) {
            aux->np = newNode;
            newNode->np = NULL;
            newNode->pp = aux;
        } else {//Insert in any other index of the list
            newNode->np = aux;
            newNode->pp = aux->pp;
            aux->pp->np = newNode;
            aux->pp = newNode;
        }
    }

    return 1;
}

/*
 * Delete a node from the array
 */
int dll_delete(DLL *dll, int i, int j) {

    //Find the node to delete
    DLL_NODE *aux = dll_search(dll, i, j);

    if (!dll_node_exist(aux, i, j)) {
        return 0;
    } else {
        if (!dll_has_next(aux) && !dll_has_previous(aux)) {
            //if the list has only one node
            dll->head = NULL;
        } else if (!dll_has_next(aux)) {
            //delete last node
            aux->pp->np = NULL;
        } else if (!dll_has_previous(aux)) {
            //delete first node
            dll->head = aux->np;
            aux->np->pp = NULL;
        } else {
            aux->pp->np = aux->np;
            aux->np->pp = aux->pp;
        }
        free(aux);
    }
    return 1;
}

/*
 * Delete every node from the list
 */
void dll_clear(DLL *dll) {
    DLL_NODE *aux = dll->head;
    while (aux != NULL) {
        if (!dll_has_next(aux)) {
            free(aux);
            break;
        }
        dll_next(&aux);
        free(aux->pp);
    }
    dll->head = NULL;
    dll->tail = NULL;
}


/*
 * Insert both lists in a new list
 * because the insertion is sorted and
 * the list do not accept identical nodes
 * the new list is the union of the two lists
 */
DLL *dll_union(DLL *setA, DLL *setB) {

    DLL *setC = malloc(sizeof (DLL));

    DLL_NODE *auxA = setA->head;
    DLL_NODE *auxB = setB->head;

    //Insert list A in the new list C
    while (auxA != NULL) {
        dll_insert(setC, auxA->nodei, auxA->nodej);
        if (!dll_has_next(auxA)) {
            break;
        }
        dll_next(&auxA);
    }
    //Insert list B in list C
    while (auxB != NULL) {
        dll_insert(setC, auxB->nodei, auxB->nodej);
        if (!dll_has_next(auxB)) {
            break;
        }
        dll_next(&auxB);
    }
    return setC;
}

/*
 * For every node in the list A check if the node exist in
 * list B, if exist inserted in list C
 */
DLL *dll_intersect(DLL *setA, DLL *setB) {
    DLL *setC = malloc(sizeof (DLL));
    DLL_NODE *auxA = setA->head;
    while (auxA != NULL) {
        DLL_NODE *auxB = dll_search(setB, auxA->nodei, auxA->nodej);
        if (dll_node_exist(auxB, auxA->nodei, auxA->nodej)) {
            dll_insert(setC, auxA->nodei, auxA->nodej);
        }
        if (!dll_has_next(auxA)) {
            break;
        }
        dll_next(&auxA);
    }
    return setC;
}

/*
 * For every node in the list A check if the node exist in
 * list B, if it does ot exist inserted in list C
 */
DLL *dll_minus(DLL *setA, DLL *setB) {
    DLL *setC = malloc(sizeof (DLL));
    DLL_NODE *auxA = setA->head;
    while (auxA != NULL) {
        DLL_NODE *auxB = dll_search(setB, auxA->nodei, auxA->nodej);
        if (!dll_node_exist(auxB, auxA->nodei, auxA->nodej)) {
            dll_insert(setC, auxA->nodei, auxA->nodej);
        }
        if (!dll_has_next(auxA)) {
            break;
        }
        dll_next(&auxA);
    }
    return setC;
}

/*
 * Print all nodes in the list
 */
void dll_print(DLL *dll) {
    DLL_NODE *aux = dll->head;
    while (aux != NULL) {
        printf("%d-%d ", aux->nodei, aux->nodej);
        if (!dll_has_next(aux)) {
            break;
        }
        dll_next(&aux);
    }
    if (aux != NULL) {
        puts("");
    }
}
