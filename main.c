#include "calculadora.h"

int main(int argc, char *argv[]) {
	char *expressao = NULL, val;
	int tam;
	float res;
	
	do {
		expressao = (char*)malloc(sizeof(char)*30);
		scanf("%[^\n]s", expressao);
		getchar();
		tam = strlen(expressao);
		val = expressao[tam-1];
		res = calculaResultado(expressao);
		if(res == 37000.45) printf("Expressao incorreta.\n");
		else printf("Resultado = %.2f\n", res);
		free(expressao);
	} while(val != '.');

	/*Entao, quando abri o projeto tambem ja vi que era a notacao polonesa, meio adaptada por causa dos parenteses mas vi que era ela haha,
	mas tambem acredito que a melhor alternativa seja uma pilha, inclusive se eu nao me engano eu tenho pronto um programa ja com calculadora
	em notacao polonesa reversa, posso te enviar pra voce dar uma olhada, eh ate feito com pilha porque meu amigo teve esse trabalho e pra ajudar
	ele eu mandei o de lab de icc do semestre passado ai quando ele terminou o com pilha ele me enviou pra eu ver, ai se voce achar que ajuda posso enviar
	mas nao vou garantir que esta certo ou bonito porque nem olhei hahaha.*/

	
	/* Uma das ideias que tive pra esse trabalho era ler uma linha
	 * 	inteira da conta e converter para "polonesa reversa". Desse
	 * 	jeito, poderiamos usar o TAD Pilha para dar o resultado final
	 */
	return 0;
}
