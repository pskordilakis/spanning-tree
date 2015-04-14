/*
 * spanning.c
 *
 *  Created on: 10 Νοε 2010
 *      Author: P. Skordilakis
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <iso646.h>
#include <malloc.h>
#include "Sparse.h"
#include "Queue.h"
#include "DoubleLinkedList.h"

int root;

/*
 * Sparse array holds the edges of a graph
 * because the graph is undirected we insert
 * node1->node2 and node2->node1
 */
void insertEdge( SPARSE *graph, int i, int j ) {
	insertSparse(graph,i,j);
	if ( i != j ) {
		insertSparse(graph,j,i);
	}
}

/*
 * Delete an edge from the graph
 */
void deleteEdge( SPARSE *graph, int i, int j ) {
	deleteSparse(graph, i, j);
	if ( i != j ) {
		deleteSparse(graph, i, j);
	}
}

/*
 * Find all edges that connect a nodeA with
 * a nodeB and mark nodeA visited
 */
void markVisited( SPARSE *graph, int node ) {
	NODE *aux=graph->rowHeads[node];
	while ( aux not_eq NULL ) {
		NODE *aux2 = searchSparse(graph,aux->hkey,aux->vkey);
		if ( aux->ci not_eq BLACK and aux->ci not_eq RED ){
			aux->ci=RED;
			aux2->cj=RED;
		}
		if ( not sparseHasNext(aux) ) {
			break;
		}
		sparseNext(&aux);
	}
}

/*
 * Mark the vertexA black, then check every edge that
 * coonects the vertexA with a vertexB,
 * if vertexB is marked visited then deactivate the edge,
 * else marke vertexB visited in every edge tha connect
 * vertexB with another node
 */
void workWith( SPARSE *graph, QUEUE *visited, int vertex ) {
	NODE *aux = graph->rowHeads[vertex];
	while ( aux not_eq NULL ) {
		NODE *aux2 = searchSparse(graph,aux->hkey,aux->vkey);
		aux->ci = BLACK;
		aux2->cj = BLACK;
		if (aux->cj not_eq BLACK and aux->cj not_eq RED){
			markVisited(graph,aux->hkey);
			enqueue(visited,aux->hkey );
			aux->p = vertex;
			aux2->p = vertex;
		}
		else if ( aux->cj == RED ) {
			aux->status=false;
			aux2->status=false;
		}

		if ( not sparseHasNext(aux) ) {
			break;
		}
		sparseNext(&aux);
	}
}

/*
 * Create a spanning tree of the graph
 * using the Breadth First Search algorithm
 */
void bfs( SPARSE *graph , QUEUE *visited ) {
	/*
	 * The algorihm starts from the vertex that you
	 * want as root in the spanning tree
	 */
	puts( "Type Root" );
	scanf( "%d", &root );
	getchar();
	enqueue( visited, root );//Enqueue root in the visited set
	while ( visited->head not_eq NULL ) {//while the visited set not empty
		QNODE *node = dequeue( visited );//dequeue the first node
		int workingNode = node->data;
		free(node);
		workWith(graph,visited,workingNode);
	}
}

/*
 * Starting from a vertex, finds the path to the
 * root of the spanning tree
 */
void findParent( SPARSE *graph, DLL *dll, int vertex ) {
	NODE *edge = graph->rowHeads[vertex];
	while ( edge not_eq NULL ) {
		if( edge->status == true ) {
			if ( vertex not_eq root ) {
				insertDll( dll, edge->vkey, edge->hkey );
				insertDll( dll, edge->hkey, edge->vkey );
				findParent( graph, dll, edge->p );
			}
			break;
		}

		if ( not sparseHasNext(edge) ) {
			break;
		}
		sparseNext(&edge);
	}
}

/*
 * To find circles in a graph we start from a deactivated
 * edge, we find the path to the root for both vertices
 * and then we find the edges that form a circle
 * (Union(pathA, pathB)-Intesect(pathA, pathB))
 */
void findCircles( SPARSE *graph, NODE *edge ) {
	if ( edge->status not_eq false ) {
		puts("The edge you chose does not create cycles");
	}
	else {
		DLL *setA = malloc(sizeof(QUEUE));
		DLL *setB = malloc(sizeof(QUEUE));
		findParent( graph, setA ,edge->vkey);
		findParent( graph, setB, edge->hkey);
		DLL *setU = dllUnion(setA, setB);
		DLL *setI = dllIntersect(setA, setB);
		DLL *setM = dllMinus(setU, setI);
		clearDll(setU);free(setU);
		clearDll(setI);free(setI);
		printf("The circle has the following edges :\n%d->%d ",edge->vkey, edge->hkey);
		printDllAll(setM);
		clearDll(setM);free(setM);
	}
}

/*
 * Prints all the edges of the graph wich are active,
 * i.e. prints the spanning tree of the graph
 */
void printTree( SPARSE *graph ) {
	int counter;
		for ( counter = 0; counter<30; counter++ ) {
			NODE *aux = graph->rowHeads[counter];
			while ( aux not_eq NULL ) {
				if(aux->status == true ) {
					printf("%d->%d\n",aux->vkey, aux->hkey );
				}
				if ( not sparseHasNext(aux) ) {
					break;
				}
				sparseNext(&aux);
			}
			if ( aux not_eq NULL ) {
				puts("");
			}
		}
}

/*
 * Prints all the edges of the graph twich are deactivated
 * i.e. prints the edges tha form circles in the graph
 */
void printDeactivatedEdges( SPARSE *graph ) {
	int counter;
	for ( counter = 0; counter<31; counter++ ) {
		NODE *aux = graph->rowHeads[counter];
		while ( aux not_eq NULL ) {
			if(aux->status not_eq true ) {
				printf("%d->%d\n",aux->vkey, aux->hkey );
			}
			if ( not sparseHasNext(aux) ) {
				break;
			}
			sparseNext(&aux);
		}
		if ( aux not_eq NULL ) {
			puts("");
		}
	}
}

/*
 * The menu to insert an edge in the graph
 */
void menuInsertEdges( SPARSE *graph ) {
	int vertexi, vertexj;
	vertexi = vertexj = -1;
	while ( (vertexi <= 0 or vertexi >= 31) or (vertexj <= 0 or vertexj >= 31) ) {
		puts("Type the edge you want to insert(va-vb)");
		scanf("%d-%d", &vertexi, &vertexj );
		getchar();
	}
	insertEdge( graph, vertexi, vertexj );
}

/*
 * The menu to delete an edge from the graph
 */
void menuDeleteEdges( SPARSE *graph ) {
	int vertexi, vertexj;
	vertexi = vertexj = -1;
	while ( (vertexi <= 0 or vertexi >= 31) or (vertexj <= 0 or vertexj >= 31) ) {
		puts("Type the edge you want to insert(va-vb)");
		scanf("%d-%d", &vertexi, &vertexj );
		getchar();
	}
	deleteSparse( graph, vertexi, vertexj );
}

/*
 * The menu to find circles in the graph
 */
void menuCircles( SPARSE *graph ) {
	int nodei, nodej;
	puts("Choose an edge from below to find the circle in the graph(va-vb)");
	printDeactivatedEdges( graph );
	scanf("%d-%d", &nodei, &nodej );
	getchar();
	NODE *edge = searchSparse( graph, nodei, nodej );
	findCircles( graph, edge );
}

/*
 * Menu with printing options
 */
void menuPrint( SPARSE *graph ) {
	int subchoice = -1;
	while ( subchoice not_eq 0 ) {
		puts("Please Choose :\n\t1. Graph\n\t2. Tree\n\t0. Back");
		scanf("%d",&subchoice);
		getchar();
		switch( subchoice ) {
		case 1 : {
			printSparseAll( graph ); break;
		}
		case 2 : {
			printTree( graph ); break;
		}
		}
	}
}

int main() {

	SPARSE *graph = malloc(sizeof(SPARSE));
	QUEUE *visited = malloc(sizeof(QUEUE));

	int choice;

	for ( choice = 0; choice<30; choice++) {
		graph->rowHeads[choice] = NULL;
		graph->colHeads[choice] = NULL;
	}

	while ( choice not_eq 0) {
		printf("Please Choose :\n\t1. Insert an edge\n\t2. Delete an edge\n\t3. BFS\n\t4. Cicles\n\t"
				"5. Print\n\t0. Quit\n");
		scanf("%d",&choice);
		getchar();
		switch( choice ) {
		case 1 : {
			menuInsertEdges(graph); break;
		}
		case 2 : {
			menuDeleteEdges(graph); break;
		}
		case 3 : {
			bfs( graph, visited ); break;
		}
		case 4 : {
			menuCircles( graph ); break;
		}
		case 5 : {
			 menuPrint( graph ); break;
		}
		}
	}
	return EXIT_SUCCESS;
}
