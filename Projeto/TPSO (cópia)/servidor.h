#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <signal.h>
#include <pthread.h>
#define TAM 25



typedef struct Labirinto {
	char maze[20][30];
	int numObjetosPontos;
	int numObjetosDest;
} labirinto;

typedef struct Jogador {
	char username[100];
	char password[100];
	int online;
	int pontuacao;
} jogador;

typedef struct mensagem{
	char op1[TAM], op2[TAM], op3[TAM], op4[TAM], op5[TAM];
	char resposta[2000];
    char endereco[20];
    struct campo *campojogo;
    int desliga;
	int nJogadores;
}MENSAGEM;

typedef struct dados_pipes{
	char qual[10];
	int fd;
} ThrDados;

int fd_servidor, fd_cliente, n;
MENSAGEM msg;
char ** processaComando(char *comando, int *tamCMD);
void users(jogador *v, int conta);
void buscaLogs(jogador *v, char ficheiroLogin[]);
void gameInfo(jogador *v,labirinto *mv, int conta, int nMapas);
int contaPlayers();
jogador* add(jogador* v, char *cmd[], int *conta);
jogador* kick(jogador *v, char *cmd[], int conta);

void buscaMapInfo(labirinto *mv, int nMapas);
void *processaPedidos();