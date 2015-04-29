/*
 * Queue.h
 *
 *  Created on: Nov 10, 2010
 *      Author: P.Skordilakis
 */

#ifndef QUEUE_H_
#define QUEUE_H_

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

/*
 * if nodei or nodej equals 0 then we use the queue
 * to store vertices, else we use the queue to store
 * edges of a graph
 */
typedef struct QNode{
	int data; // to use if we store nodes of a graph
	int nodei, nodej; //to use if we store edges of a graph
	struct QNode *pp, *np;
}QNODE;

typedef struct queue {
	QNODE *head, *tail;
}QUEUE;

void q_enqueue( QUEUE *q, int node );
QNODE *q_dequeue( QUEUE *q );
void q_clear(QUEUE *q);
QUEUE *q_union( QUEUE *qA, QUEUE *qB );
QUEUE *q_intersect( QUEUE *qA, QUEUE *qB);
void q_print(QUEUE *q);

#endif /* QUEUE_H_ */
