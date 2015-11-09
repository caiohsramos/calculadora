/*	Caio Henrique Silva Ramos	9292991	
	Igor Martinelli			9006336*/
#include "calculadora.h"

int main(int argc, char *argv[]) {
	char *expressao = NULL, val;
	int tam;
	float res;
	
	do {
		expressao = (char*)malloc(sizeof(char)*300);
		scanf("%[^\n]s", expressao);
		getchar();
		tam = strlen(expressao);
		val = expressao[tam-1];
		res = calculaResultado(expressao);
		if(res == ERRO) printf("Expressao incorreta.\n");
		else printf("Resultado = %.2f\n", res);
		free(expressao);
	} while(val != '.');

	return 0;
}
