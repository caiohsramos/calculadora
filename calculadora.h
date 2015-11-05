#ifndef _CALCULADORA_H_
#define _CALCULADORA_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define FALSE 0
#define TRUE 1

#define MUL 1
#define DIV 2
#define SOM 3
#define SUB 4

#define ERRO 9999

typedef struct pilha_ PILHA;
typedef struct no_ NO;
typedef struct item_ ITEM;

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
