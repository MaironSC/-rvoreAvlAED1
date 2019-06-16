#ifndef _ARVORE_H_
#define _ARVORE_H_
#include <stdio.h>
#include <stdlib.h>



/* IMPLEMENTAÇÃO DE ÁRVORE BINÁRIA DE PESQUISA */

struct nodo {
	int valor; 
	struct nodo * dir, * esq;
	int bal;
};

struct vetorstruct{
	int indice;
	int qte;
	struct nodo **elemento;
};

struct nodo * inicializa_arvore(int entradas, int * valores);

struct nodo * insere_nodo(struct nodo * raiz, int valor);

struct nodo * remove_nodo(struct nodo * raiz, int valor);

int altura(struct nodo * raiz);

struct nodo * busca(struct nodo * raiz, int valor);

int balanceada(struct nodo * raiz);

int numero_elementos(struct nodo * raiz);

int abrangencia(struct nodo * raiz, int * resultado);

void imprime(int * valores, int tamanho);

void remove_todos(struct nodo * raiz);

int prefix(struct nodo * raiz, int * resultado);

int postfix(struct nodo * raiz, int *resultado);

int infix(struct nodo * raiz, int * resultado);

//Funções de rotação, AVL.

struct nodo *definerotacao(int testebal, int val, struct nodo *raiz);
struct nodo *rotacaohorario(struct nodo *raiz);
struct nodo *rotacaoantihorario(struct nodo *raiz);
struct nodo *duplahorario(struct nodo *raiz);
struct nodo *duplaanthorario(struct nodo *raiz);

// ---------

//Funções de fila.

struct vetorstruct *novovetor();
struct nodo* dequeue(struct vetorstruct *p);
int get(struct vetorstruct *p);
void novafunc (struct vetorstruct *f);
void inserefim(struct vetorstruct *p, struct nodo *raiz);
void novafunc (struct vetorstruct *f);

// --------


#endif 
