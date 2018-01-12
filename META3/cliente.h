#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <signal.h>
#include <curses.h>
#include <stdbool.h>

#define TAM 25


typedef struct Elemento {
	int x, y;
	char avatar;
} elemento;

typedef struct Labirinto {
	char maze[20][30];
	int numObjetosPontos;
	int numObjetosDest;
	elemento *elementos;
	elemento *jogadores;
} labirinto;

typedef struct mensagem{
	char op1[TAM], op2[TAM], op3[TAM], op4[TAM], op5[TAM];
	char resposta[200];
    char endereco[20];
	labirinto lab;
}MENSAGEM;

int fd_servidor, fd_cliente;
MENSAGEM msg;
labirinto lab;

int login();
char ** processaComando(char *comando, int *tamCMD);
void trata(int sinal);
void mostraLabirinto();
void iniciarJogo();
