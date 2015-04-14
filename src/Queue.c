/*
 * Queue.c
 *
 * Created on : Nov 10 2010
 *     Author : P. Skordilakis
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <iso646.h>
#include <malloc.h>
#include "Queue.h"

/*
 * Enqueue a node
 * we use the queue
 * to store vertices a graph
 */

void enqueue( QUEUE *q, int node ) {
	QNODE *newNode = malloc(sizeof(QNODE));
	newNode->data = node;

	if ( q->tail == NULL ) {
		q->head = q->tail = newNode;
	}
	else {
		q->tail->pp = newNode;
		newNode->np = q->tail;
		newNode->pp = NULL;
		q->tail = newNode;
	}
}

/*
 * Dequeue a node, if the queue is empty
 * it returns null
 */
QNODE *dequeue( QUEUE *q ) {
	if ( q->head == NULL ) {
		//puts("Queue is empty");
	}
	else {
		QNODE *aux = q->head;
		if ( aux->pp != NULL ) {
			aux->pp->np = NULL;
			q->head = aux->pp;
		}
		else {
			q->head=q->tail=NULL;
		}
		return aux;
	}
	return NULL;
}

void clearQueue(QUEUE *q) {
	QNODE *aux = q->tail;
	while ( aux not_eq NULL ) {
		if ( aux->np == NULL ) {
			free(aux);
			break;
		}
		aux = aux->np;
		free(aux->pp);
	}
	q->head = NULL;
	q->tail = NULL;
}

/************************************************************************************/
/*
 * Print the nodes in the queue
 */
void printQueue(QUEUE *q) {
QNODE *aux = q->tail;
while (aux not_eq NULL) {
	printf("%d|", aux->data);
	if ( aux->np == NULL ) {
		puts("");
		break;
	}
	aux=aux->np;
}
}
