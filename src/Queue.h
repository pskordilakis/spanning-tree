/*
 * Queue.h
 *
 *  Created on: Nov 10, 2010
 *      Author: P.Skordilakis
 */

#ifndef QUEUE_H_
#define QUEUE_H_

/*
 * if nodei or nodej equals 0 then we use the queue
 * to store vertices, else we use the queue to store
 * edges of a graph
 */
typedef struct QNode{
	int data; // to use if we store nodes of a graph
	int nodei, nodej; //to use if we store edes of a graph
	struct QNode *pp, *np;
}QNODE;

typedef struct queue {
	QNODE *head, *tail;
}QUEUE;

void enqueue( QUEUE *q, int node );
QNODE *dequeue( QUEUE *q );
QUEUE *qunion( QUEUE *qA, QUEUE *qB );
QUEUE *qintersect( QUEUE *qA, QUEUE *qB);
void printQueue(QUEUE *q);

#endif /* QUEUE_H_ */
