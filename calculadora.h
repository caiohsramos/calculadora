#ifndef _CALCULADORA_H_
#define _CALCULADORA_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FALSE 0
#define TRUE 1

typedef struct pilha PILHA;
typedef struct no NO;

PILHA *criaPilha();
int empilhar(PILHA *, int);
int desempilhar(PILHA *);
int vazia(PILHA *);
void imprimePilha(PILHA *);


//cabecalhos...

#endif
