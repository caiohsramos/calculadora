#include "calculadora.h"

struct pilha_ {
	NO *topo;
	int tamanho;
};

struct item_ {
	//int tipo; |Acho que esse 'tipo' nao sera necessario,
	//			|pois empilharemos simbolos (char) ou numeros (float), nao os
	//			|dois ao mesmo tempo. Simbolos na hora da transformacao e numeros
	//			|na hora do calculo.
	float num;
	char op;
};

struct no_ {
	ITEM item; // aqui pensei em usar void para guardar qualquer coisa, ai a gente pode guardar tudo, parenteses etc na mesma variavel.
	struct no_ *anterior;
};

PILHA *criaPilha() {
	
	PILHA *pilha = (PILHA *) malloc(sizeof(PILHA));
	
	if(pilha != NULL) {
		pilha->topo = NULL;
		pilha->tamanho = 0;
	}
	
	return pilha;
}
/*
	entao, coloquei int aqui so por questao de teste, mas pensei em colocarmos void * e ir tratando os casos, o que voce acha?, ou acha melhor botar unsigned char mesmo e tratar so os inteiros?

	deixa comentado algo depois so pra mim saber se voce viu isso porque nao sei se to fazendo certo la no git hahaha.*/
int empilhar(PILHA *pilha, ITEM item) {
	
	NO *novoNo = (NO *) malloc(sizeof(NO));

	if(novoNo != NULL) {
		//como eu disse la, eh so um esboco, depois a gente trata os casos e faz os casts caso usemos void mesmo.
		novoNo->item = item;
		novoNo->anterior = pilha->topo;
		pilha->topo = novoNo;
		pilha->tamanho++;
		return TRUE;
	};
	return FALSE;
}
/*coloquei void * porque acho que vamos usar o item que desempilhar, certo? conforme vai desempilhando vai fazendo as operacoes da calculadora acho*/
int desempilhar(PILHA *pilha, ITEM *item) {

	NO *noAux = NULL;


	if(!vazia(pilha)) {
		(*item) = pilha->topo->item;
		noAux = pilha->topo;
		pilha->topo = pilha->topo->anterior;
	//fazendo isso eu nao to setando null tambem pro pilha->topo->anterior?		
	//->>>>	noAux->anterior = NULL;
		free(noAux);
		noAux = NULL;
		
		return TRUE;
	}
	return FALSE;

}

int vazia(PILHA *pilha) {
	return(pilha->topo == NULL);
}
/*aqui so fiz pra testar o conteudo da pilha pra ver se deu tudo certo
void imprimePilha(PILHA *pilha) {
	
	NO *noAux = pilha->topo;

	while(noAux != NULL) {
		printf("%d\t", noAux->item);
		noAux = noAux->anterior;
	}
}
*/


float calculaResultado(char *expressao) {
	//essa funcao deve transformar a expressao infixa para posfixa, e calcular o resultado...
	int tam = (strlen(expressao)-1);
	ITEM item;
	float res;
	PILHA *pilha = criaPilha();
	//...
	return res;
}

