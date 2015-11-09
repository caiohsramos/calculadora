/*	Caio Henrique Silva Ramos	9292991	
	Igor Martinelli			9006336*/

#include "calculadora.h"
/*estruturas utilizadas para o calculo da notacao aritmetica.*/
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
/*Funcao criarPilha :

	funcao responsavel por inicializar a estrutura de dados pilha.*/
PILHA *criaPilha() {
	
	PILHA *pilha = (PILHA *) malloc(sizeof(PILHA));
	
	if(pilha != NULL) {
		pilha->topo = NULL;
		pilha->tamanho = 0;
	}
	
	return pilha;
}
/*Funcao empilhar :

	funcao do TAD pilha responsavel por empilhar um item.*/
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
/*Funcao desempilhar :

	funcao do TAD pilha responsavel por desempilhar um item e retornar o mesmo.*/
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
/*Funcao vazia :

	funcao responsavel por verificar se a pilha esta vazia ou nao.*/
int vazia(PILHA *pilha) {
	return(pilha->topo == NULL);
}
/*Funcao apaga_pilha :

	funcao responsavel por apagar a estrutura de dados pilha.*/
void apaga_pilha(PILHA **p) {
	ITEM aux;
	while(!vazia((*p))) desempilhar((*p), &aux);
	free(*p);
}
/*Funcao topo :

	funcao responsavel por tornar o item como o topo da pilha*/
void topo(PILHA *p, ITEM *item) {
	(*item) = p->topo->item;
}
/*Funcao calculaResultado :

	funcao responsavel por calcular o resultado da expressao dada via stdin pela chamada das funcoes que auxiliarao no processo.*/
float calculaResultado(char *expressao) {
	char *pos_fixa = transforma_pos_fixa(expressao);
	float res;
	if(testeInvalida(expressao)) return ERRO;
	res = calcula_pos_fixa(pos_fixa);
	free(pos_fixa);
	return res;
}
/*Funcao transforma_pos_fixa :

	funcao responsavel por transformar a expressao infixa dada via stdin para a forma posfixa da mesma para que sejam realizados os calculos posteriomente pela funcao calcula_pos_fixa.*/
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
/*Funcao retornaOperacao :

	funcao responsavel por retornar um inteiro identificador do operador.*/
char retornaOperacao(char op) {
	if(op == '*') return 1;
	if(op == '/') return 2;
	if(op == '+') return 3;
	if(op == '-') return 4;
	return 0;
}
/*Funcao calcula_pos_fixa :

	funcao responsavel por calcular a expressao em notacao polonesa reversa, a funcao tem alguns lacos while para que os espacos e as tabulacoes sejam ignorados e utiliza uma pilha para o calculo da operacao, a mesma ira empilhar os numeros ate que uma operacao seja identificada, quando esta for, entao serao desempilhados os dois ultimos numeros empilhados e neles realizada a operacao, seguindo a ordem proposta via stdin.*/
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
	}
	desempilhar(pilha, &item);
	apaga_pilha(&pilha);
	return item.num; 

}
/*Funcao testeInvalida :

	funcao responsavel por testar se uma expressao aritmetica eh invalida ou nao, tal funcao conta o numero de ( e de ), caso sejam iguais, esta eh valida, caso sejam diferentes, invalida.*/
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
