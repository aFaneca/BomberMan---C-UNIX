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
	int bombinhas;
	int megabombas;
	char ultimoMovimento;
} elemento;

typedef struct Labirinto {
	char maze[20][30];
	int numObjetosPontos;
	int totalObjetos;
	int numObjetosDest;
	elemento elementos[1000];
	elemento jogadores[25];
} labirinto;

typedef struct Jogador {
	char username[100];
	char password[100];
	int online;
	int pontuacao;
	char nomeDoFicheiro[100];
} jogador;


typedef struct mensagem{
	char op1[TAM], op2[TAM], op3[TAM], op4[TAM], op5[TAM];
	char resposta[200];
    char endereco[20];
	labirinto lab;
}MENSAGEM;

typedef struct dados_pipes{
	char qual[10];
	int fd;
} ThrDados;


typedef struct expBomba{
	int x;
	int y;
	char tipo;
	
} argsBomba;

int fd_servidor, fd_cliente;
MENSAGEM msg;
labirinto lab;
elemento elem;

int login();
char ** processaComando(char *comando, int *tamCMD);
void trata(int sinal);
void mostraLabirinto();
void iniciarJogo();
bool validaMovimento (char mov);
bool estaNaSaida(int x, int y);
void terminaJogo();
void lancaBombinha();
void* explodeBomba(void * dados);
