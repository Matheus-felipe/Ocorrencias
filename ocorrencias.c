/*
*	Projeto final de Lógica de Programação e Algoritmos I
*		    	Controle de Ocorrências
*	Alunos: João Neto, Matheus Ferreira e Anderson dos Santos
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Dados{
	unsigned int num_controle;
	char local[40];
	char tipo[20];
};

/* protótipo das funções */
int validacaoInteiro(char *str);
void registro(FILE *fp, struct Dados *ocorrencias);
void consulta(FILE *fp, int numero, struct Dados *ocorrencias);
//int probabilidade(FILE *fp);
int size_arq(FILE *fp, struct Dados teste);
int city_ocorrencias(FILE *fp, char *cidade, struct Dados teste);

int main(int argc, char **argv){

	struct Dados info;
	FILE *arq = NULL;

	/* inicio do escopo de verificações */
	if(argc != 5){
		printf("Insira os parâmetros corretos!\n");
		printf("<operação> <numero_controle> <local> <tipo>\n");
		return 1;		
	}

	if(!validacaoInteiro(argv[2]) || atoi(argv[2]) < 0){
		printf("Entre com um número de controle válido.\n");
		return 2;
	}
	/* fim do escopo de verificações */
	
	/* passando dados dos parâmetros de main para a estrutura */
	info.num_controle = atoi(argv[2]);
	strcpy(info.local,argv[3]);
	strcpy(info.tipo, argv[4]);

	if(!strcmp(argv[1],"reg")){
		//arq = fopen("data.bin", "ab");
		printf("Operação solicitada: %s\n", argv[1]);
		registro(arq, &info);
	}
	if(!strcmp(argv[1],"cons")){
		printf("Operação solicitada: %s\n", argv[1]);
		consulta(arq, info.num_controle, &info);
	}
	if(!strcmp(argv[1],"dados")){
		printf("Operação solicitada: %s\n", argv[1]);
		size_arq(arq,info);
	}
	
	//printf("%d", city_ocorrencias(arq, "Caruaru", info));

	printf("Número: %d\n", info.num_controle);
	printf("Local: %s\n", info.local);
	printf("Tipo: %s\n", info.tipo);

	return 0;
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

void registro(FILE *fp, struct Dados *ocorrencias){

	fp = fopen("data.bin", "ab");
	
	if(fp == NULL){
		printf("O arquivo não pode ser aberto!\n");	
	}
	
	fwrite(ocorrencias, 1, sizeof(struct Dados), fp);
	fclose(fp);
}

void consulta(FILE *fp, int numero, struct Dados *ocorrencias){
	
	fp = fopen("data.bin", "rb");
	
	if(fp == NULL){
		printf("O arquivo não pode ser aberto!\n");		
	}
	
	fseek(fp, numero*sizeof(struct Dados), SEEK_SET);
	fread(ocorrencias, 1, sizeof(struct Dados), fp);
	fclose(fp);
}

int size_arq(FILE *fp, struct Dados a){
	
	int pos, size;
	fp = fopen("data.bin", "rb");
	
	if(fp == NULL){
		printf("O arquivo não pode ser aberto!\n");
	}
	
	fseek(fp, 0, SEEK_END);
	pos = ftell(fp);
	size = pos / sizeof(struct Dados);

	fclose(fp);
	
	return size;
}

int city_ocorrencias(FILE *fp, char *cidade, struct Dados teste){
	
	int i;
	int j = 4;
	int num = 0;
	char city[40];
	fp = fopen("data.bin", "rb");
	
	if(fp == NULL){
		printf("O arquivo não pode ser aberto!\n");
	}
	
	for(i = 0; i < size_arq(fp,teste); ++i){
		
		fseek(fp, 4, SEEK_CUR);
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

/* float probabilidade(FILE *fp, int qtd_cidade, int qtd_total, char *cidade, struct Dados teste){
	
	return city_ocorrencias(fp, cidade, teste);
	
} */
