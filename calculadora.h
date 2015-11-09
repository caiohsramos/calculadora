/*	Caio Henrique Silva Ramos	9292991	
	Igor Martinelli			9006336*/
#ifndef _CALCULADORA_H_
#define _CALCULADORA_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
/*defines utilizados ao longo do programa.*/
#define FALSE 0
#define TRUE 1

#define MUL 1
#define DIV 2
#define SOM 3
#define SUB 4
/*codigo de erro para retorno de operacoes mal sucedidas.*/
#define ERRO 9999
/*typedefs das estruturas de dados utilizadas ao longo do programa.*/
typedef struct pilha_ PILHA;
typedef struct no_ NO;
typedef struct item_ ITEM;
/*escopo das funcoes que foram utilizadas ao longo do programa, tais funcoes serao explicadas posteriormente no arquivo .c.*/
PILHA *criaPilha();
int empilhar(PILHA *, ITEM);
int desempilhar(PILHA *, ITEM *);
int vazia(PILHA *);
void imprimePilha(PILHA *);
float calculaResultado(char *);
char *transforma_pos_fixa(char *);
void topo(PILHA *, ITEM *);
char retornaOperacao(char op);
float calcula_pos_fixa(char *);
void apaga_pilha(PILHA **);
int testeInvalida(char*);

#endif
