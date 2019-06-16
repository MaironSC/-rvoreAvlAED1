#include "arvore.h"

struct nodo *insere_nodo(struct nodo *raiz, int valor){
	if(raiz == NULL){							
		struct nodo *x;
		x = malloc(sizeof(struct nodo));
		x->valor = valor;
		x->bal = 0;
		x->esq = NULL;
		x->dir = NULL;
		return x;
	}
	else{
		int testebalance=0;
		if(valor > raiz->valor){
			raiz->dir = insere_nodo(raiz->dir, valor); //Desloca-se até o lugar do elemento recursivamente.
			if(raiz->dir != NULL){
				testebalance=balanceada(raiz);
				raiz = definerotacao(testebalance, valor, raiz);
			}
		}
		else if(valor < raiz->valor){
			raiz->esq = insere_nodo(raiz->esq, valor);
			if(raiz->esq != NULL){
				testebalance=balanceada(raiz);
				raiz = definerotacao(testebalance, valor, raiz);
			}
		}
	}
	return raiz;
}

struct nodo * remove_nodo(struct nodo * raiz, int valor){
	if(raiz == NULL){
		return NULL;
	}
	if(valor > raiz->valor){
		raiz->dir = remove_nodo(raiz->dir, valor);
	}
	else{
		if(valor < raiz->valor){
			raiz->esq = remove_nodo(raiz->esq, valor);
		}
		else{
			if(raiz->valor == valor){
				if(raiz->esq == NULL && raiz->dir == NULL){ //Folha
					free(raiz);
					return NULL;
				}
				else if(raiz->esq == NULL && raiz->dir != NULL){ //1 filho a direita
						raiz = raiz->dir;
				}
				else if(raiz->dir == NULL && raiz->esq != NULL){ //1 filho a esquerda.
						raiz = raiz->esq;
				}
				else{ //2 filhos
					struct nodo *aux;
					struct nodo *aux2;
					aux = raiz->dir;
					aux2 = aux->esq; // é necessário pegar o elemento mais a esquerda da sub arvore a direita da raiz.
					while(aux2 != NULL){
						aux = aux2;
						aux2 = aux2->esq;
					}
					raiz->valor = aux->valor;
					raiz->dir = remove_nodo(raiz->dir, raiz->valor);
				}
			}
		}
	}
	return raiz;
}


int altura(struct nodo * raiz){
	if(raiz == NULL){
		return 0; //Caso base da recursão.
	}
	else{
		int arvoreesq = 0 ; 
		int arvoredir = 0 ; 
		arvoredir=altura(raiz->dir)+1; //Altura sub arvore direita
		arvoreesq=altura(raiz->esq)+1; //Altura da sub arvore esq
		if(arvoreesq > arvoredir){
			return arvoreesq;
		}else{
			return arvoredir; 
		}
	return arvoredir+arvoreesq; 
	}
}

void remove_todos(struct nodo * raiz){
	struct nodo *auxdir, *auxesq;
	auxesq = raiz->esq;
	auxdir = raiz->dir;
	if(raiz != NULL){
		free(raiz); //base
		if(auxesq != NULL){
			remove_todos(auxesq); //Libera todos da esquerda
		}else{
			if(auxdir !=NULL){
				remove_todos(auxdir); //Libera todos da direita
			}	
		}
	}else{
		return;
	}
}

struct nodo * inicializa_arvore(int entradas, int *valores){
	int i;
	struct nodo *raiz=NULL;
	if(entradas<=0){
		return NULL;
	}
	if(valores == NULL){
		return NULL;
	}
	for(i=0; i<entradas; i++){
		if(valores[i] <= 0){
			return NULL;
		}
		else{
			raiz = insere_nodo(raiz, valores[i]);
		}
	}	
	return raiz;
}


void imprime(int * valores, int tamanho){
	int i;
	for(i=0; i<tamanho; i++){
		if(i%10 == 0 && i!=0){
			printf("\n");
		}
		printf("%d ", valores[i]);
	}
}


int abrangencia(struct nodo * raiz, int * resultado){
	int contador=0;
	struct nodo *aux;
	struct vetorstruct *f = NULL;
	f=novovetor();
	inserefim(f, raiz);
	resultado[contador] = get(f);
	contador++;
	while(f->indice < f->qte){ //qte = Elementos inseridos; //indice = Quantade de elementos retirados
		aux = dequeue(f);	
		if(aux->esq != NULL){
			inserefim(f, aux->esq);
		}
		if(aux->dir != NULL){
			inserefim(f, aux->dir);
		}
		if (f->qte == f->indice){
			novafunc(f);
			break;
		}
		resultado[contador] = get(f);
		contador++;
	}	
		return 0;
}	


int balanceada(struct nodo * raiz){
	if(raiz==NULL){
		return 0; //Se não existir nodo, retorna 0.
	}
	else{
		int alturaesq, alturadir, alturaresult;
		alturaesq=altura(raiz->esq); //Indentifico a diferença das alturas das subárvores.
		alturadir=altura(raiz->dir);
		alturaresult = alturadir - alturaesq; //Define o fator de balanceamento, seguindo o padrão dos slides
		return alturaresult; // Dir + & esquerda -, Se a altura for >=2 e <=-2
	}
}

struct nodo *definerotacao(int testebal, int val, struct nodo *raiz){
	if(testebal >=2){ //Define qual o tipo de desbalanceamento.
		if(val > raiz->dir->valor){ // O lado do desbalanceamento e tipo de rotação
			raiz = rotacaoantihorario(raiz);
		}
		else{
			raiz = duplaanthorario(raiz);
		}
	}else{
		if(testebal <= -2){
			if(val < raiz->esq->valor){
				raiz = rotacaohorario(raiz);
			}
			else{
				raiz = duplahorario(raiz);
			}
		}
	}
	return raiz;
}	

struct nodo *rotacaohorario(struct nodo *raiz){                                                                                   
    struct nodo *aux; 
    aux = raiz->esq;
    raiz->esq = aux->dir;
    aux->dir = raiz;
    aux->bal = balanceada(aux);
    raiz->bal = balanceada(raiz);
    return aux;
}
/*
	3      2    
   2  ->  1 3  -> raiz = 3, aux = 2
  1	   		 
*/

struct nodo *rotacaoantihorario(struct nodo *raiz){ 
	//printf("%d\n", raiz->valor);
	struct nodo *aux;
	aux = raiz->dir;
	raiz->dir = aux->esq;
	aux->esq = raiz;
	aux->bal = balanceada(aux);
	raiz->bal = balanceada(raiz); //Altera o fator de balanceamento, depois de balanceada.
	return aux;
}
/*
	4              5
	 5    ->     4   6  => 5 gira no sentido antihorário
	  6  
*/

struct nodo *duplahorario(struct nodo *raiz){ 
	struct nodo *aux;
	aux = raiz;
	aux->esq = rotacaoantihorario(aux->esq);
	aux = rotacaohorario(aux);
	return aux;
}
/*		rotação anti
	80       80       60
  40   ->   60   -> 40	80 -> rotacão horária 	
    60     40
*/

struct nodo *duplaanthorario(struct nodo *raiz){ 
	struct nodo *aux;
	aux = raiz;
	aux->dir = rotacaohorario(aux->dir);
	aux = rotacaoantihorario(aux);
	return aux;
}
/*

	40        40    rotação horária        45     antihorária
	  50  ->    45	               ->    40  50 
	 45			  50
*/
int numero_elementos(struct nodo * raiz){
	int numero = 0;
	if(raiz->esq != NULL){
		numero = numero + numero_elementos(raiz->esq); //Percorre a sub arvore esq
	}
	if(raiz->dir != NULL){
		numero = numero +  numero_elementos(raiz->dir); //Percorre a sub arvore dir	
	}
	else{
		return 1; //Caso base
	}
	return numero+1; // +1 = elemento raiz
}


struct nodo * busca(struct nodo * raiz, int valor){
	if(raiz == NULL){ 			//Funciona no mesmo princípio que o insert, percorrendo a subárvore conforme o valor
		return NULL;
	}
	else{
		if(raiz->valor == valor){
			return raiz;
		}
		else{
			if(raiz->valor > valor){
				if(raiz->esq == NULL){
					return NULL;
				}else{ 
					return busca(raiz->esq, valor);
				}
			}
			else{
				if(raiz->dir == NULL){
					return NULL;
				}else{
					return busca(raiz->dir, valor);
				}
			}
		}
	}
}

int prefix(struct nodo * raiz, int * resultado){
	static int jj=0;
	if(raiz!=NULL){
		resultado[jj] = raiz->valor;
		jj++;
		jj = prefix(raiz->esq, resultado);
		jj = prefix(raiz->dir, resultado);
		return jj;
	}	
	else{
		return jj;
	}
}

int infix(struct nodo * raiz, int * resultado){
	int i=0;
	if(raiz == NULL){
		return 0; //Caso ache um null, volta uma para a mesma posição em i.
	}	
	else{
		infix(raiz->esq, resultado);
		resultado = &raiz->valor;
		resultado++;
		i++;
		infix(raiz->dir, resultado);
		return i;
	}
}

int postfix(struct nodo * raiz, int *resultado){
	static int ii=0;
	if(raiz == NULL){
		return ii;
	}else{
		ii = postfix(raiz->esq, resultado);
		ii = postfix(raiz->dir, resultado);
		resultado[ii] = raiz->valor;
		ii++;
		return ii;
	}
}
