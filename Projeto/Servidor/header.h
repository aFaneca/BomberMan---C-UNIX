#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

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

char ** processaComando(char *comando, int *tamCMD);
void users(jogador *v, int conta);
void buscaLogs(jogador *v);
void gameInfo(jogador *v, int conta);
int contaPlayers();
jogador* add(jogador* v, char *cmd[], int *conta);
jogador* kick(jogador *v, char *cmd[], int conta);

// void buscaMapInfo(labirinto *mv);
