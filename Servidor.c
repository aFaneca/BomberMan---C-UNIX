#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>

#define NMAXPLAY 20

typedef struct Labirinto {
	char paredes[20][30];
} labirinto;

typedef struct Login {
	char username[100];
	char password[100];
} login;

typedef struct Cliente {
	login l;
	bool online;
	double pontuacao;
	int objetos_por_apanhar;
	int p_id;
} cliente;


char ** processaComando(char *comando, int *tamCMD) {

	char ** cmd = NULL;
	char *  p = strtok(comando, " ");
	int n_espacos = 0, i;


	while (p) { 	/* divide a string em palavras */
		cmd = realloc(cmd, sizeof(char*) * ++n_espacos);

		if (cmd == NULL)
			exit(-1); /* se alocação de memória falhar */

		cmd[n_espacos - 1] = p;
		p = strtok(NULL, " ");
	}

	/* realoca um elemento extra para o "NULL" final */
	cmd = realloc(cmd, sizeof(char*) * (n_espacos + 1));
	cmd[n_espacos] = 0;

	*tamCMD = n_espacos;
	return cmd;
}


login* add(login* v, char *cmd[], int *conta) {

	int i = 0;
	int flag = 0;

	for (i = 0; i < *conta; i++) {
		if (strcmp(cmd[1], v[i].username) == 0) {
			printf("Username existente!!\n");
			flag = 1;
		}
	}
	if (flag == 0) {
		*conta = *conta + 1;
		login *temp = realloc(v, sizeof(login)*(*conta));
		printf("Adicionado User No. %d --> %s\n", *conta, cmd[1]);
		strcpy(temp[*conta - 1].username, cmd[1]);
		strcpy(temp[*conta - 1].password, cmd[2]);
		return temp;
	}
	else {
		return v;
	}



	return v;
}

int contaLinhas() {

	int conta = 0;
	char linha[256];
	FILE *f = fopen("logs.txt", "r");
	if (f == NULL) {
		printf("Erro a abrir ficheiro 1.");
		return 1;
	}
	while (fgets(linha, sizeof(linha), f) != NULL) {
		conta++;
	}

	conta = conta / 2;
	printf("Pessoas a jogar = %d\n", conta);

	fclose(f);
	return conta;
}

void buscaLogs(login *v) {

	int k = 0;
	FILE *f = fopen("logs.txt", "r");
	if (f == NULL) {
		printf( "Erro a abrir ficheiro2.");
		return 1;
	}
	while (!feof(f)) {
		fscanf(f, "%s", v[k].username);
		fscanf(f, "%s", v[k].password);
		k++;
	}
	fclose(f);
}

void users(login *v, int conta) {

	int k = 0;
	if (conta == 0) {
		printf("Nao existem Users a jogar\n");
	}
	for (k = 0; k < conta; k++) {
		printf("%s\n", v[k].username);
	}
}


void main(int argc, char *argv[]) {
	char *comando = NULL;
	comando = malloc(sizeof(char) * 20);
	char **cmd;
	int tamCMD = 0, i;

	login *v;
	int total = contaLinhas();
	v = malloc(sizeof(login)*total);
	buscaLogs(v);


	while (1) {
		if (stdin == NULL) {
			printf("Erro a abrir ficheiro3.");
			return 1;
		}
		fgets(comando, 25, stdin);

		cmd = processaComando(comando, &tamCMD);
		//printf("%s %d", cmd[0], tamCMD);

		if (strncmp(cmd[0], "add", 3) == 0) {
			if (tamCMD == 3) {
				v = add(v, cmd, &total);
				users(v, total);

			}
			else {
				printf("Sintaxe ERROR");
			}
		}

		if (strncmp(cmd[0], "game", 4) == 0) {
			if (tamCMD != 3)
				printf("Erro de Sintaxe.");
			else
				printf("Username: %s", cmd[1]);
		}

		if (strncmp(cmd[0], "users", 5) == 0) {
			if (tamCMD == 1)
				users(v, total);
			else
				printf("Erro de Sintaxe.");
		}

		if (strncmp(cmd[0], "kick", 4) == 0) {
			if (tamCMD != 2)
				printf("Erro de Sintaxe. kick <username>");
			else
				printf("User kickado: ...");
		}

		if (strncmp(cmd[0], "map", 3) == 0) {
			if (tamCMD != 2)
				printf("Erro de Sintaxe. kick <nome-ficheiro>");
			else
				printf("Mapa Carregado ...");
		}
		if (strncmp(cmd[0], "game", 4) == 0) {
			if (tamCMD != 1)
				printf("Erro de Sintaxe.");
			else
				printf("Game: ...");
		}
		if (strncmp(cmd[0], "shutdown", 8) == 0) {
			if (tamCMD != 1 || strlen(cmd[0]) != 9)
				printf("Erro de Sintaxe.");
			else
				break;
		}
	}
}
