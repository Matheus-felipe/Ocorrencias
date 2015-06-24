/*
*	Projeto final de Lógica de Programação e Algoritmos I
*		    	Controle de Ocorrências
*	Alunos: João Neto, Matheus Ferreira e Anderson dos Santos
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Dados{
	int num_controle;
	char local[40];
	char tipo[20];
};

/* protótipo das funções */
int validacaoInteiro(char *str);
void registro(FILE *fp, struct Dados *ocorrencias);
void consulta(FILE *fp, int numero, struct Dados *ocorrencias);
int num_registros(FILE *fp);
int city_ocorrencias(FILE *fp, char *cidade);
float probabilidade(FILE *fp, char *cidade);
void imprime_dados(FILE *fp, char *str);
	
int main(int argc, char **argv){

	struct Dados info[1];
	FILE *arq = NULL;

	/* inicio do escopo de verificações */
	if(argc != 5){
		printf("Insira os parametros corretos!\n");
		printf("<operacao> <numero_controle> <local> <tipo>\n");
		return 1;		
	}
	if(!validacaoInteiro(argv[2]) || atoi(argv[2]) < 0){
		printf("Entre com um numero de controle valido.\n");
		return 2;
	}
	/* fim do escopo de verificações */
	
	/* passando dados dos parâmetros de main para a estrutura */
	info[0].num_controle = atoi(argv[2]);
	strcpy(info[0].local,argv[3]);
	strcpy(info[0].tipo, argv[4]);

	/*condicoes para os tipos de operações */
	if(!strcmp(argv[1],"reg")){
		registro(arq, &info[0]);
		printf("Ocorrencia registrada!\n");
	}
	if(!strcmp(argv[1],"cons")){
		consulta(arq, info[0].num_controle, &info[0]);
		printf("Número: %d\n", info[0].num_controle);
		printf("Local: %s\n", info[0].local);
		printf("Tipo: %s\n", info[0].tipo);
	}
	if(!strcmp(argv[1],"dados")){
		imprime_dados(arq, argv[3]);
	}
	
	return 0;
}

/* funcao que serve para validar o numero de controle */
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

void registro(FILE *fp, struct Dados *ocorrencias){

	fp = fopen("data.bin", "ab");
	
	fwrite(ocorrencias, 1, sizeof(struct Dados), fp);
	fclose(fp);
	
}

void consulta(FILE *fp, int numero, struct Dados *ocorrencias){
	
	fp = fopen("data.bin", "rb");
	
	fseek(fp, numero*sizeof(struct Dados), SEEK_SET);
	fread(ocorrencias, 1, sizeof(struct Dados), fp);
	
	fclose(fp);
}

int num_registros(FILE *fp){
	
	int pos, tamanho;
	fp = fopen("data.bin", "rb");
	
	fseek(fp, 0, SEEK_END);
	pos = ftell(fp);
	tamanho = pos / sizeof(struct Dados);

	fclose(fp);

	return tamanho;
}

int city_ocorrencias(FILE *fp, char *cidade){
	
	int i;
	int j = 4;
	int num = 0;
	char city[40];
	fp = fopen("data.bin", "rb");
	
	for(i = 0; i < num_registros(fp); ++i){
		
		fseek(fp, j, SEEK_SET);
		fread(&city, 1, 40, fp);
		
		if(!strcmp(city, cidade)){
			++num;
			j += 64;
		}else{
			j += 64;
		}		
	}
	
	return num;
	
}

float probabilidade(FILE *fp, char *cidade){
	
	return ((float)city_ocorrencias(fp, cidade) / num_registros(fp))*100;
	
} 

void imprime_dados(FILE *fp, char *str){
	
	printf("Total de ocorrencias registradas: %d\n", num_registros(fp));
	
	if(strcmp(str, "none") != 0){
		printf("%s teve %d ocorrencias. \n", str, city_ocorrencias(fp,str));
		printf("Essa cidade possui %.2f %% de chance para que ocorra outra ocorrencia.\n", probabilidade(fp,str));
	}
	
}
