#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>


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

char ** processaComando(char *comando, int *tamCMD);
void users(login *v, int conta);
int contaLinhas();
void buscaLogs(login *v);
login* add(login* v, char *cmd[], int *conta);
