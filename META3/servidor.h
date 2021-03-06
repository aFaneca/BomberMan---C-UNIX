#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <signal.h>
#include <pthread.h>
#include <stdbool.h>
#include <time.h>

#define INIMIGOS 5
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
	elemento jogadores[10];
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

jogador *v;
int fd_servidor, fd_cliente, n;
const char nomeFicheiro[100];
MENSAGEM msg;
labirinto lab;

void shutdown();
void sinalizaKick();
void trata(int sinal);
void grava();
jogador* updateSaida();
int validaLogin(char user[], char pass[], char end[]);
char ** processaComando(char *comando, int *tamCMD);
int usersOn();
void buscaLogs(char ficheiroLogin[]);
void gameInfo(labirinto *mv, int conta, int nMapas);
int contaPlayersRegistados();
jogador* add(char *cmd[], int *conta);
jogador* kick(char *cmd[], int conta);

bool temObjeto(int x, int y);
void esvaziarPosicao(int x, int y);
void mudaChar(int x, int y, char avatar);
void *processaPedidos();
void updateLabirinto();
void criaInimigos();
void lancaMegaBomba();