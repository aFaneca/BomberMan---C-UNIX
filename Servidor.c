#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define NMAXPLAY 20

typedef struct Labirinto{
	char paredes[20][30];
} labirinto;

typedef struct Login{
	const char username[100];
	const char password[100];
} login;

typedef struct Cliente{
	login l;
	double pontuacao;
	int objetos_por_apanhar;
} cliente;


char ** processaComando(char *comando, int *tamCMD){

	char ** cmd  = NULL;
	char *  p    = strtok (comando, " ");
	int n_espacos = 0, i;
	
	/* divide a string em palavras */
	while (p) {
	 cmd = realloc (cmd, sizeof (char*) * ++n_espacos);

	  if (cmd == NULL)
		exit (-1); /* se alocação de memória falhar */

	  cmd[n_espacos-1] = p;

	  p = strtok (NULL, " ");
	}

	/* realoca um elemento extra para o "NULL" final */

	cmd = realloc (cmd, sizeof (char*) * (n_espacos+1));
	cmd[n_espacos] = 0;

	*tamCMD = n_espacos;
	return cmd;		
  }


void main(int argc, char *argv[]){
	char *comando = NULL; 
	comando = malloc(sizeof(char)*20);
	char **cmd;
	int *tamCMD, i;
	
	while(1){
		fgets(comando, 25, stdin);
	
		cmd = processaComando(comando, tamCMD);
		
		if(strncmp(cmd[0], "game", 4) == 0){
			
			if(*tamCMD != 3)
				printf("Erro de Sintaxe.");
			else
				printf("Username: %s\tPassword: %s", cmd[1], cmd[2]);
			
		}
		if(strncmp(cmd[0], "users", 5) == 0){
			if(*tamCMD != 1)
				printf("Erro de Sintaxe.");
			else
				printf("Lista de Users: ...");
		}
		if(strncmp(cmd[0], "kick", 4) == 0){
			if(*tamCMD != 2)
				printf("Erro de Sintaxe. kick <username>");
			else
				printf("User kickado: ...");
		}
		
		if(strncmp(cmd[0], "map", 3) == 0){
			if(*tamCMD != 2)
				printf("Erro de Sintaxe. kick <nome-ficheiro>");
			else
				printf("Mapa Carregado ...");
		}
		if(strncmp(cmd[0], "game", 4) == 0){
			if(*tamCMD != 1)
				printf("Erro de Sintaxe.");
			else
				printf("Game: ...");
		}
		if(strncmp(cmd[0], "shutdown", 8) == 0){
			printf("%d", sizeof(cmd[0]));
			if(*tamCMD != 1 && (sizeof(cmd[0]) != sizeof(char) * 8))
				printf("Erro de Sintaxe.");
			else
				break;
		}
	}
	
	
}