#include "arvore.h"

struct vetorstruct *novovetor(){
	struct vetorstruct *l;
	l = malloc(sizeof(struct vetorstruct));
	l -> elemento = malloc(sizeof(struct nodo *)*100); // *nodo
	l->indice = 0;
	l->qte = 0;
	return l;
}

void novafunc (struct vetorstruct *f){
	free(f->elemento);
	free(f);
}

void inserefim(struct vetorstruct *p, struct nodo *raiz){
	if(p == NULL){
		return;
	}
	else if(raiz == NULL){
		return;
	}
	else{
		p->elemento[p->qte] = raiz; 
		p->qte++;
	}
}

struct nodo* dequeue(struct vetorstruct *p){
	if(p == NULL){
		return NULL;
	}else{
		p->indice++;
		return p->elemento[p->indice-1];
	}
}


int get(struct vetorstruct *p)
{
	if(p&&(p->indice>=0))	
		return p->elemento[p->indice]->valor;
	else return -1;
}

