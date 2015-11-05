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


void apaga_pilha(PILHA **p) {
	ITEM aux;
	while(!vazia((*p))) desempilhar((*p), &aux);
	free(*p);
}

void topo(PILHA *p, ITEM *item) {
	(*item) = p->topo->item;
}

float calculaResultado(char *expressao) {
	//essa funcao deve transformar a expressao infixa para posfixa, e calcular o resultado...
	printf("Infixa = %s\n", expressao);
	char *pos_fixa = transforma_pos_fixa(expressao);
	float res;
	//res = calculaResultado(pos_fixa);
	printf("Pos_fixa = %s\n", pos_fixa);
	free(pos_fixa);
	return 0.0;
}

char *transforma_pos_fixa(char *expressao) {
	char *pos_fixa = (char*)malloc(50*sizeof(char));
	char val;
	int tam = (strlen(expressao)-1), i, j;
	PILHA *pilha = criaPilha();
	ITEM item;
	j = 0;
	for(i = 0; i < tam; i++) {
		val = expressao[i];
		if(isdigit(val) || val == '.') {
			pos_fixa[j] = val;
			j++;
		} else if(val == ' ' || val == '\t') {
			pos_fixa[j] = val;
			j++;
		} else if(vazia(pilha)) {
			item.op = val;
			empilhar(pilha, item);
		} else {
			topo(pilha, &item);
			if(item.op == '(') {
				item.op = val;
				empilhar(pilha, item);
			} else if(val == '(') {
				item.op = val;
				empilhar(pilha, item);
			} else if(val == ')') {
				do {
					desempilhar(pilha, &item);
					if(item.op != '(') {
						pos_fixa[j] = item.op;
						j++;
					}
				} while(item.op != '(');
			} else {
				topo(pilha, &item);
				if(val == '*' || val == '/') {
						if(item.op == '+' || item.op == '-') {
							item.op = val;
							empilhar(pilha, item);
						} else {
							desempilhar(pilha, &item);
							pos_fixa[j] = item.op;
							j++;
							item.op = val;
							empilhar(pilha, item);
						}
				} else {
					topo(pilha, &item);
					if(val == '+' || val == '-') {
						if(item.op == '*' || item.op == '/') {
							//passo 7...
							while(item.op == '*' || item.op == '/') {
								desempilhar(pilha, &item);
								pos_fixa[j] = item.op;
								j++;
								if(!vazia(pilha)) topo(pilha, &item);
								else break;
							}
							item.op = val;
							empilhar(pilha, item);
						} else {
							desempilhar(pilha, &item);
							pos_fixa[j] = item.op;
							j++;
							item.op = val;
							empilhar(pilha, item);
						}
					}
				}
			}
		}
	}
	//estou fazendo os casos na ordem que aparece no final do site que eu te mandei...
	
	//passo 8 entra aqui......
	while(!vazia(pilha)) {
		desempilhar(pilha, &item);
		pos_fixa[j] = item.op;
		j++;
	}
	pos_fixa[j] = '\0';
	apaga_pilha(&pilha);
	return pos_fixa;
}

char retornaOperacao(char op) {
	if(op == '*') return 1;
	if(op == '/') return 2;
	if(op == '+') return 3;
	if(op == '-') return 4;
	return 0;
}

int calculaRes(char *exp) {
	
	PILHA *pilha = criaPilha();
	int i;
	float a, b;

	for(i = 0; i < strlen(exp); i++) {
		while(exp[i] > 0 && exp[i] < 9) {
			// aqui empilha-se os numeros ateh que se reconheca alguma operacao
			empilhar(pilha, atoi(&(exp[i])));
			i++;
			/*
				depois..
				a = desempilhar;
				b = desempilhar;
				res = a op b;	
				empilhar res;
			*/
		} 
	}
	

}



