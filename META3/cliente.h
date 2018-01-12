#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <signal.h>
#define TAM 25

typedef struct mensagem{
	char op1[TAM], op2[TAM], op3[TAM], op4[TAM], op5[TAM];
	char resposta[200];
    char endereco[20];
}MENSAGEM;

int fd_servidor, fd_cliente;
MENSAGEM msg;

int login();
char ** processaComando(char *comando, int *tamCMD);
void trata(int sinal);