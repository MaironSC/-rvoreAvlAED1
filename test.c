#include "simplegrade.h"
#include "arvore.h"
#include <stdlib.h>



void test_criacao(){
	struct nodo * raiz;
	int val;

	DESCRIBE("Testes simples de criar árvore");

	WHEN("Crio uma árvore com número de entradas em zero ou negativo ou sem dados");
	THEN("Deve retornar NULL");

	isNull(inicializa_arvore(-1, NULL),1);
	isNull(inicializa_arvore(0, NULL),1);
	isNull(inicializa_arvore(10, NULL),1);

	WHEN("Crio uma árvore com um elemento");
	THEN("Devo ter só a raiz");
	val = 5;
	raiz = inicializa_arvore(1,&val);
	isNotNull(raiz, 1);
	if (raiz){
		isEqual(raiz->valor, 5, 1);
		free(raiz);
	} else isNotNull(raiz, 1);
}


void test_tres_elementos(){
	struct nodo * raiz;
	int balanceada[] = {2, 1 , 3};
	int caminhamento[3];

	DESCRIBE("Testes com criação de três elementos");
	
	WHEN("Crio uma árvore balanceada");
	THEN("Altura deve ser dois");

	raiz = inicializa_arvore(3, balanceada);
	infix(raiz, caminhamento);
	imprime(caminhamento, 3);
	isNotNull(raiz, 1);
	if (raiz){
		isEqual(altura(raiz), 2, 1);
		remove_todos(raiz);
	} else isNotNull(raiz, 1);


}	

void test_15_elementos(){
	struct nodo * raiz;
	int balanceada[] = {50, 20, 100, 10, 25, 70, 150, 5, 15, 22, 30, 60, 90, 120, 170};
	//            50
	//      20         100
	//  10    25     70     150
	// 5  15 22 30  60 90 120  170      
	int caminhamento[15];
	int i;

	DESCRIBE("Testes com criação de quinze elementos");
	
	WHEN("Crio uma árvore balanceada");
	THEN("Altura deve ser 4");

	raiz = inicializa_arvore(15, balanceada);
	abrangencia(raiz, caminhamento);
	imprime(caminhamento, 15);
	isNotNull(raiz, 1);
	if (raiz){
		isEqual(altura(raiz), 4, 2);
	} else isNotNull(raiz, 2);

	THEN("Caminhamento em abrangência deve ser igual à entrada");
	if (raiz){
		for(i=0; (i<15) && (balanceada[i]==caminhamento[i]); i++);
		isEqual(i,15,5);
	} else isNotNull(raiz,5);

	IF("Tirar uma folha");
	THEN("Não deve mudar a raiz");
	if (raiz){
		struct nodo * nova_raiz = remove_nodo(raiz, 170);
		if (nova_raiz == raiz){
			THEN("Percorrer em abrangencia deve funcionar");
			for(i=0; i<15;i++)
				caminhamento[i] = 0;
			abrangencia(nova_raiz, caminhamento);
			imprime(caminhamento, 15);
			for(i=0; (i<14) && (balanceada[i]==caminhamento[i]); i++);
			if (caminhamento[14]==0)
				isEqual(i,14,2);
			else isNotNull(NULL,2);
		} else isNotNull(NULL, 2);
		remove_todos(raiz);

	} else isNotNull(raiz,3);


	IF("Tirar a raiz");
	THEN("Próxima raiz deve ser menor da subarvore direita (como nos slides)");
	raiz = inicializa_arvore(15, balanceada);
	if (raiz){
		raiz = remove_nodo(raiz, 50);
		infix(raiz, caminhamento);
		imprime(caminhamento, 15);
		abrangencia(raiz, caminhamento);
		imprime(caminhamento, 15);

		if(raiz){
			isEqual(raiz->valor, 60, 3);
			remove_todos(raiz);
		}
		else isNotNull(raiz,3);

	} else isNotNull(raiz, 3);


}


void test_rotacao_simples(){
	struct nodo * raiz;
	int elementos[] = {10,5,15,20};
	int elementos_2[] = {10,5,15,3};
	int caminhamento[20];
	int  i;
	/**
	        10                     10
	      5    15                5    15
	              20            3  
	*/

	DESCRIBE("Testes de rotação simples");

	WHEN("Eu insiro um elemento que crie desbalanço na direita");
	THEN("Devo fazer uma rotação simples à esquerda");

	raiz = inicializa_arvore(4, elementos);
	if (raiz){
		int esperado[] = {10, 5, 20, 15, 25};
		insere_nodo(raiz, 25);
		/** 
	        10                            10
	      5    15         ---->        5       20
	              20                         15   25
	                  25
	    */
		abrangencia(raiz, caminhamento);
		for(i=0; (i<5)&&(esperado[i]==caminhamento[i]); i++);
		isEqual(i,5,1);
		remove_todos(raiz);

	} else isNotNull(raiz,1);



	WHEN("Eu insiro um elemento que crie desbalanço na esquerda");
	THEN("Devo fazer uma rotação simples à direita");


	raiz = inicializa_arvore(4, elementos_2);
	if (raiz){
		int esperado[] = {10, 3, 15, 1, 5};
		insere_nodo(raiz, 1);
		/** 
	        10                            10
	      5    15         ---->         3     15
	    3                             1   5                            
	  1                           	                 
	    */
		abrangencia(raiz, caminhamento);
		for(i=0; (i<5)&&(esperado[i]==caminhamento[i]); i++);
		isEqual(i,5,1);
		remove_todos(raiz);

	} else isNotNull(raiz,1);

}

void test_rotacao_dupla(){
	struct nodo * raiz;
	int elementos[] = {10,5,15,13};
	int elementos_2[] = {10,5,15,3};
	int caminhamento[20];
	int  i;
	/**
	        10                     10
	      5     15               5    15
	          13               3  
	*/

	DESCRIBE("Testes de rotação duplas");

	WHEN("Eu insiro um elemento que crie desbalanço na direita");
	THEN("Devo fazer uma rotação dupla à esquerda");

	raiz = inicializa_arvore(4, elementos);
	if (raiz){
		int esperado[] = {10, 5, 14, 13, 15};
		insere_nodo(raiz, 14);
		/** 
	        10                            10
	      5      15         ---->       5     14
	           13                           13   15
	             14
	    */
		abrangencia(raiz, caminhamento);
		for(i=0; (i<5)&&(esperado[i]==caminhamento[i]); i++);
		isEqual(i,5,1);
		remove_todos(raiz);

	} else isNotNull(raiz,1);



	WHEN("Eu insiro um elemento que crie desbalanço na esquerda");
	THEN("Devo fazer uma rotação dupla à direita");


	raiz = inicializa_arvore(4, elementos_2);
	if (raiz){
		int esperado[] = {10, 4, 15, 3, 5};
		insere_nodo(raiz, 4);
		/** 
	         10                            10
	       5    15         ---->         4     15
	    3                             3     5                            
	      4                       	                 
	    */
		abrangencia(raiz, caminhamento);
		for(i=0; (i<5)&&(esperado[i]==caminhamento[i]); i++);
		isEqual(i,5,1);
		remove_todos(raiz);

	} else isNotNull(raiz,1);
}





void test_7_elementos(){
	struct nodo * raiz;
	int balanceada[] = {50, 20, 100, 10, 25, 70, 150, 5, 15, 22, 30, 60, 90, 120, 170};
	//            50
	//      20         100
	//  10    25     70     150
	// 5  15 22 30  60 90 120  170      
	int caminhamento[15];
	int i;

	DESCRIBE("Testes com criação de quinze elementos");
	
	WHEN("Crio uma árvore balanceada");
	THEN("Altura deve ser 4");

	raiz = inicializa_arvore(15, balanceada);
	abrangencia(raiz, caminhamento);
	imprime(caminhamento, 15);
	isNotNull(raiz, 1);
	if (raiz){
		isEqual(altura(raiz), 4, 2);
	} else isNotNull(raiz, 2);

	THEN("Caminhamento em abrangência deve ser igual à entrada");
	if (raiz){
		for(i=0; (i<15) && (balanceada[i]==caminhamento[i]); i++);
		isEqual(i,15,5);
	} else isNotNull(raiz,5);

	IF("Tirar uma folha");
	THEN("Não deve mudar a raiz");
	if (raiz){
		struct nodo * nova_raiz = remove_nodo(raiz, 170);
		if (nova_raiz == raiz){
			THEN("Percorrer em abrangencia deve funcionar");
			for(i=0; i<15;i++)
				caminhamento[i] = 0;
			abrangencia(nova_raiz, caminhamento);
			imprime(caminhamento, 15);
			for(i=0; (i<14) && (balanceada[i]==caminhamento[i]); i++);
			if (caminhamento[14]==0)
				isEqual(i,14,2);
			else isNotNull(NULL,2);
		} else isNotNull(NULL, 2);
		remove_todos(raiz);

	} else isNotNull(raiz,3);


	IF("Tirar a raiz");
	THEN("Próxima raiz deve ser menor da subarvore direita (como nos slides)");
	raiz = inicializa_arvore(15, balanceada);
	if (raiz){
		raiz = remove_nodo(raiz, 50);
		infix(raiz, caminhamento);
		imprime(caminhamento, 15);
		abrangencia(raiz, caminhamento);
		imprime(caminhamento, 15);

		if(raiz){
			isEqual(raiz->valor, 60, 3);
			remove_todos(raiz);
		}
		else isNotNull(raiz,3);

	} else isNotNull(raiz, 3);


}

void test_7_elementos_linear(){
	struct nodo * raiz;
	int naobalanceada[] = {1,2,3,4,5,6,7};
	int caminhamento[20];
	int i;

	DESCRIBE("Testes com criação de sete elementos à direita");
	
	WHEN("Crio uma árvore com inserão não balanceada");
	THEN("Altura deve ser mínima por ser AVL");

/**
	1

	1
	  2

	1*                  2
	  2       -->     1   3 
        3 

      2
    1   3
          4
 
      2                     2
    1   3*           ->  1     4 
          4                  3   5
            5

	   2*                        4
	1     4                  2        5
	    3   5      ->      1   3        6 
	          6 

        4                           4
     2     5*                  2        6
    1  3     6      ->        1  3    5    7
               7
*/


	raiz = inicializa_arvore(7, naobalanceada);
	abrangencia(raiz, caminhamento);
	imprime(caminhamento, 7);
	isNotNull(raiz, 1);
	if (raiz){
		isEqual(altura(raiz), 3, 2);
	} else isNotNull(raiz, 2);

	THEN("Caminhamento em abrangência deve ser 4 2 6 1 3 5 7");
	if (raiz){
		int esperado[7]={4,2,6,1,3,5,7};

		for(i=0; (i<7) && (esperado[i]==caminhamento[i]); i++);
		isEqual(i,7,5);
	} else isNotNull(raiz,5);



	IF("Tirar uma folha");
	THEN("Não deve mudar a raiz");
	if (raiz){
		int esperado[6]={4,2,6,1,3,5};

		struct nodo * nova_raiz = remove_nodo(raiz, 7);
		if (nova_raiz == raiz){
			THEN("Percorrer em abrangencia deve funcionar");
			for(i=0; i<7;i++)
				caminhamento[i] = 0;
			abrangencia(nova_raiz, caminhamento);
			imprime(caminhamento, 7);
			for(i=0; (i<6) && (esperado[i]==caminhamento[i]); i++);
			if (caminhamento[6]==0)
				isEqual(i,6,2);
			else isNotNull(NULL,2);
		} else isNotNull(NULL, 2);
		remove_todos(raiz);

	} else isNotNull(raiz,3);


	IF("Tirar a raiz");
	THEN("Próxima raiz deve ser menor da subarvore direita (como nos slides)");
/**

        4                  5             
     2     6    -->     2     6               
    1  3  5  7        1  3      7
*/

	raiz = inicializa_arvore(7, naobalanceada);
	if (raiz){
		raiz = remove_nodo(raiz, 4);
		infix(raiz, caminhamento);
		imprime(caminhamento, 6);
		abrangencia(raiz, caminhamento);
		imprime(caminhamento, 6);

		if(raiz){
			isEqual(raiz->valor, 5, 3);
			remove_todos(raiz);
		}
		else isNotNull(raiz,3);

	} else isNotNull(raiz, 3);


}








int main(){

	test_criacao();
	test_tres_elementos();
	test_15_elementos();
	test_rotacao_simples();
	test_rotacao_dupla();
	test_7_elementos();
	test_7_elementos_linear();


	GRADEME();

	if (grade==maxgrade)
		return 0;
	else return grade;

}
