/*
*	Projeto final de Lógica de Programação e Algoritmos I
*		    	Controle de Ocorrências
*	Alunos: João Neto, Matheus Ferreira e Anderson dos Santos
*/

#include <stdio.h>

int validacaoInteiro(char *str);
int registro(FILE *fp, int numero, char *local, char *tipo);
int consulta(FILE *fp, int numero);
int probabilidade(FILE *fp);
int imprime_dados(FILE *fp, char *nome);

struct dados{
	int num_controle;
	char local[40];
	char tipo[20];
};

int main(int argc, char **argv){

}

int validacaoInteiro(char *str){

	int i = 0;

	while(str[i]){
		if(str[i] < '0' || str[i] > '9'){
			return 0;
		}
		++i;
	}
	return 1;
}

int registro(FILE *fp, int numero, char *local, char *tipo){
}

int consulta(FILE *fp, int numero){
}

int probabilidade(FILE *fp){
	
}

float imprime_dados(FILE *fp, char *local){
}
