/*
 * Sparse.c
 *
 *  Created on: 15 Οκτ 2010
 *      Author: P. Skordilakis
 */

#include "../includes/sparse.h"

/*
 * Check if a list in the sparse array has nodes
 */
int sparse_is_empty( NODE *head ) {
	if ( head != NULL ) {
		return 0;
	}
	return 1;
}

/*
 * check if a node points to another (np)
 */
int sparse_has_next( NODE *aux ) {
	if ( aux->np != NULL ) {
		return 1;
	}
	return 0;
}

/*
 * check if a node points to another (pp)
 */
int sparse_has_previous( NODE *aux ) {
	if ( aux->pp != NULL ) {
		return 1;
	}
	return 0;
}

/*
 * check if a node points to another (up)
 */
int sparse_has_up( NODE *aux ) {
	if ( aux->up != NULL ) {
		return 1;
	}
	return 0;
}

/*
 * check if a node points to another (dp)
 */
int sparse_has_down( NODE *aux ) {
	if ( aux->dp != NULL ) {
		return 1;
	}
	return 0;
}

/*
 * Move aux to the next node
 */
void sparse_next( NODE **aux ) {
	*aux = (*aux)->np;
}

/*
 * Move aux to the previous node
 */
void sparse_previous( NODE **aux ) {
	*aux = (*aux)->pp;
}

/*
 * Move aux up
 */
void sparse_up( NODE **aux ) {
	*aux = (*aux)->up;
}

/*
 * Move aux down
 */
void sparse_down(NODE **aux) {
	*aux = (*aux)->dp;
}

/*
 * Check if a node exist in the sparse array
 */
int sparse_node_exist( NODE *aux, int i, int j ) {
	if ( aux != NULL 
            && aux->vkey == i 
            && aux->hkey == j
        ) {
		return 1;
	}
	return 0;
}

/*
 * Find a specific node in the sparse array
 */
NODE *sparse_search( SPARSE *s, int i, int j ) {
	NODE *aux = s->rowHeads[i];
	while (  aux != NULL 
                && sparse_has_next(aux) 
                && aux->hkey < j 
        ) {
		sparse_next(&aux);
	}
	return aux;
}

/*
 * Insert a node in the array
 */
int sparse_insert( SPARSE *s, int i, int j ) {

	NODE *aux = s->rowHeads[i];
	while ( aux != NULL 
                && sparse_has_next(aux) 
                && aux->hkey < j 
        ) {
		sparse_next(&aux);
	}

	if ( sparse_node_exist( aux, i, j ) ) {
            return 0;
	}
	else {
		NODE *newNode = malloc(sizeof(NODE));
		newNode->vkey = i;
		newNode->hkey = j;
		newNode->ci = newNode->cj = 0;
		newNode->status=1;

		if ( aux == NULL ) {
			s->rowHeads[i] = newNode;
			newNode->np = NULL;
			newNode->pp = NULL;
		}
		else {
			if ( !sparse_has_previous(aux) 
                            && aux->hkey > j 
                        ) {
				s->rowHeads[i] = newNode;
				newNode->pp = NULL;
				newNode->np = aux;
				aux->pp = newNode;
			}
			else {
				if ( !sparse_has_next( aux ) 
                                && aux->hkey < j 
                                ) {//Insert at the end
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
		while (  aux != NULL 
                    && sparse_has_down(aux) 
                    && aux->vkey < i 
                ) {
			sparse_down(&aux);
		}

		if ( aux == NULL ) {
			s->colHeads[j] = newNode;
			newNode->dp = NULL;
			newNode->up = NULL;
		}
		else {
			if ( !sparse_has_up(aux) && aux->vkey > i ) {
				s->colHeads[j] = newNode;
				newNode->up = NULL;
				newNode->dp = aux;
				aux->up = newNode;
			}
			else {
				if ( !sparse_has_down( aux ) 
                                && aux->vkey < i 
                                ) {//Insert at the end
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
        return 1;
}

/*
 * Delete a node from the array
 */
int sparse_delete( SPARSE *s, int i, int j ) {

	NODE *aux = sparse_search( s, i, j );

	if( !sparse_node_exist( aux, i, j ) ) {
            return 0;
	}
	else {
		if ( !sparse_has_next(aux) 
                     && !sparse_has_previous(aux) 
                ) {//if the list has only one node
			s->rowHeads[i] = NULL;
		}
		else if ( !sparse_has_next(aux) ) {//Delete last node
			aux->pp->np = NULL;
		}
		else if ( !sparse_has_previous(aux)) {//delete first node
			s->rowHeads[i] = aux->np;
			aux->np->pp = NULL;
		}
		else {
			aux->pp->np = aux->np;
			aux->np->pp = aux->pp;
		}

		if ( !sparse_has_down(aux) 
                    && ! sparse_has_up(aux) 
                ) {//if the list has only one node
			s->colHeads[j] = NULL;
		}
		else if ( !sparse_has_down(aux) ) {//Delete last node
			aux->up = NULL;
		}
		else if ( !sparse_has_up(aux)) {//delete first node
			s->colHeads[j] = aux->dp;
			aux->dp->up = NULL;
		}
		else {
			aux->up->dp = aux->dp;
			aux->dp->up = aux->up;
		}
		free(aux);
	}
        
        return 1;
}

/*
 * Delete every node from the array
 */
void sparse_clear() {

}

/*
 * Print a specific node in the array
 */
void sparse_print_node( SPARSE *s, int i, int j ) {
	NODE *vaux, *haux;
	vaux = sparse_search( s, i,j);
	haux = sparse_search( s, j,i);
	if ( haux != NULL 
            && haux->hkey == j 
            && vaux != NULL 
            && vaux->vkey == i 
        ) {
            printf( "%d->%d\n", vaux->vkey, vaux->hkey );
	}
	else {
            puts("The node do not exist");
	}
}

/*
 * Print all nodes in the array
 */
void sparse_print_all( SPARSE *s ) {
	int counter;
	for ( counter = 0; counter<31; counter++ ) {
		NODE *vaux = s->rowHeads[counter];
		while ( vaux != NULL ) {
			printf("%d->%d; ",vaux->vkey, vaux->hkey );
			if ( !sparse_has_next(vaux) ) {
				break;
			}
			sparse_next(&vaux);
		}
		if ( vaux != NULL ) {
			puts("");
		}
	}
}
