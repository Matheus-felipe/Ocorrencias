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
	char data [16];
	char nome [40];
	
};
	/* 120 bytes */	

/* protótipo das funções */

int validacaoInteiro(char *str);
void registro(FILE *fp, struct Dados *ocorrencias);
void consulta(FILE *fp, int numero, struct Dados *ocorrencias);
int num_registros(FILE *fp);
int city_ocorrencias(FILE *fp, char *cidade);
float probabilidade(FILE *fp, char *cidade);
void imprime_dados(FILE *fp, char *str);
char * diminuir (char * str);
int erro_str(char * str); 

	
int main(int argc, char **argv){

	struct Dados info[1];
	FILE * arq = NULL;

	/* inicio do escopo de verificações */
	if(argc != 7){
		printf("Insira os parametros corretos!\n");
		printf("<operacao> <numero_controle> <local> <tipo> <data> <nome> \n");
		return 1;		
	}
	if(!validacaoInteiro(argv[2]) || atoi(argv[2]) < 0){
		
		printf("Entre com um numero de controle valido.\n");
		
		return 2;
	}
	if (!erro_str (argv [1]) || !erro_str (argv [3]) || !erro_str (argv [4]) || !erro_str (argv [6])){
		
		printf ("Verifique as informacoes passadas \n");
		
		return 3;
	}
		
	/* fim do escopo de verificações */
	
	/* passando dados dos parâmetros de main para a estrutura */
	
	info[0].num_controle = atoi(argv[2]);
	
	strcpy(info[0].local,argv[3]);
	
	strcpy(info[0].tipo, argv[4]);
	
	strcpy (info[0].data , argv [5]);
	
	strcpy (info[0].nome , argv [6]);

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
		
		printf ("Data: %s\n ",info[0].data);
		
		printf ("Nome: %s\n", info[0].nome);
		
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

void consulta(FILE *fp, int numero, struct Dados * ocorrencias){
	
	fseek(fp, numero*sizeof(struct Dados), SEEK_SET);
	
	fread(ocorrencias, 1, sizeof(struct Dados), fp);
	
	fclose(fp);
}

int num_registros(FILE *fp){
	
	int pos, tamanho;
	
	fseek(fp, 0, SEEK_END);
	pos = ftell(fp);
	tamanho = pos / sizeof(struct Dados);


	return tamanho;
}

int city_ocorrencias(FILE *fp, char *cidade){
	
	int i;
	int j = 4;
	int num = 0;
	char city[40];

	
	for(i = 0; i < num_registros(fp); ++i){
		
		fseek(fp, j, SEEK_SET);
		fread(&city, 1, 40, fp);
		
		if(!strcmp(city, cidade)){
			++num;
			j += 120;
		}else{
			
			j += 120;
			
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
	fclose (fp);	
}

char * diminuir(char *string){

    int indice;
	
    for(indice = 0; indice < strlen(string); ++indice){
        
		if(string[indice] >= 65 && string[indice] <= 90){
            
			string[indice] += 32;
			
        }
    }
	
    return string;
}

int erro_str(char * str){
	
	int i;
	
	diminuir (str);
	
	for (i = 0; i < strlen (str) ; ++i){
		
		if (str [i] < 'a'  || str [i] > 'z'){
			
			return 0;
		}	
	}
		 return 1;
}
