#include "calculadora.h"

int main(int argc, char *argv[]) {

	PILHA *pilha = criaPilha();
	
	empilhar(pilha, 17);
	empilhar(pilha, 24);
	empilhar(pilha, 32);
	empilhar(pilha, 7);
	
	imprimePilha(pilha);

	desempilhar(pilha);
	imprimePilha(pilha);

	desempilhar(pilha);
	imprimePilha(pilha);
		

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
