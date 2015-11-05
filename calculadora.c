#include "calculadora.h"

struct pilha_ {
	NO *topo;
	int tamanho;
};

struct item_ {
	float num;
	char op;
};

struct no_ {
	ITEM item; 
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

int empilhar(PILHA *pilha, ITEM item) {
	
	NO *novoNo = (NO *) malloc(sizeof(NO));

	if(novoNo != NULL) {
		novoNo->item = item;
		novoNo->anterior = pilha->topo;
		pilha->topo = novoNo;
		pilha->tamanho++;
		return TRUE;
	};
	return FALSE;
}

int desempilhar(PILHA *pilha, ITEM *item) {

	NO *noAux = NULL;


	if(!vazia(pilha)) {
		(*item) = pilha->topo->item;
		noAux = pilha->topo;
		pilha->topo = pilha->topo->anterior;
		free(noAux);
		noAux = NULL;
		
		return TRUE;
	}
	return FALSE;

}

int vazia(PILHA *pilha) {
	return(pilha->topo == NULL);
}


void apaga_pilha(PILHA **p) {
	ITEM aux;
	while(!vazia((*p))) desempilhar((*p), &aux);
	free(*p);
}

void topo(PILHA *p, ITEM *item) {
	(*item) = p->topo->item;
}

float calculaResultado(char *expressao) {
	char *pos_fixa = transforma_pos_fixa(expressao);
	float res;
	if(testeInvalida(expressao)) return ERRO;
	printf("Infixa: %s\n", expressao);
	printf("Pos_fixa: %s\n", pos_fixa);
	res = calcula_pos_fixa(pos_fixa);
	free(pos_fixa);
	return res;
}

char *transforma_pos_fixa(char *expressao) {
	char *pos_fixa = (char*)malloc(300*sizeof(char));
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
		} else {
			pos_fixa[j] = ' ';
			j++;
			if(vazia(pilha)) {
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
	}
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

float calcula_pos_fixa(char *exp) {
	
	PILHA *pilha = criaPilha();
	int i, tam;
	float a, b;
	ITEM item;
	tam = strlen(exp);
	for(i = 0; i < tam; i++) {
		while(exp[i] == ' ' || exp[i] == '\t') i++;
		while(retornaOperacao(exp[i]) == 0) {
			sscanf(&exp[i], "%f", &a);
			printf("Float lido: %.2f\n", a);
			item.num = a;
			empilhar(pilha, item);
			while(exp[i] == ' ' || exp[i] == '\t') i++;
	
			if(!retornaOperacao(exp[i])) {
				while(exp[i] != ' ' && exp[i] != '\t') {
					if(retornaOperacao(exp[i])) break;
					i++;
				}
				while(exp[i] == ' ' || exp[i] == '\t') i++;
			}
		}
		desempilhar(pilha, &item);
		b = item.num;
		desempilhar(pilha, &item);
		a = item.num;
		switch(retornaOperacao(exp[i])) {
			case MUL:
				item.num = a*b;
				break;
			case DIV:
				item.num = a/b;
				break;
			case SOM:
				item.num = a+b;
				break;
			case SUB:
				item.num = a-b;
				break;
		};
		empilhar(pilha, item);
		topo(pilha, &item);
		printf("Topo: %.2f\n", item.num);
	}
	desempilhar(pilha, &item);
	apaga_pilha(&pilha);
	return item.num; 

}

int testeInvalida(char *exp) {
	int i, tam, esq = 0, dir = 0;
	tam = strlen(exp);
	for(i = 0; i < tam; i++) {
		if(exp[i] == '(') esq++;
		if(exp[i] == ')') dir++;
	}
	if(esq == dir) return 0;
	return 1;
}

