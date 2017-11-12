#include "header.h"
#define NMAXPLAY 20


int main(int argc, char *argv[]) {
	char **cmd;
	char *comando = NULL;
	comando = malloc(sizeof(char) * 20);
	int tamCMD = 0;

	jogador *v;
	int total = contaPlayers();
	v = malloc(sizeof(jogador)*total);
	buscaLogs(v);

	
	labirinto *mv;
	mv = malloc(sizeof(labirinto));
	int nMapas = 1;
	buscaMapInfo(mv, nMapas);
	
	int flag = 0;

	while (flag == 0) {
		if (stdin == NULL) {
			printf("Erro a abrir ficheiro3.");
			flag = 1;
		}
        printf("\n> ");
		fgets(comando, 25, stdin);
		cmd = processaComando(comando, &tamCMD);

		if (strcmp(cmd[0], "add") ==0) {
			if (tamCMD == 3) {
				v = add(v, cmd, &total);
			}
			else {
				printf("Erro de Sintaxe. <add 'username' 'password'>\n");
			}
		}
		else if (strcmp(cmd[0], "users") == 0) {
			if (tamCMD == 1){
				users(v, total);
			}else{
				printf("Erro de Sintaxe. <users>\n");
			}
		}
		else if (strcmp(cmd[0], "kick") == 0) {
			if (tamCMD == 2){
				v = kick(v, cmd, total);
			}else{
				printf("Erro de Sintaxe. kick <username>\n");
			}
		}
		else if (strcmp(cmd[0], "map") == 0) {
			if (tamCMD == 2){
				//map();
			}else{
				printf("Erro de Sintaxe. map <nome-ficheiro>\n");
			}
		}else if (strcmp(cmd[0], "game") == 0) {
			if (tamCMD == 1){
				gameInfo(v, mv, total, nMapas);
			}else{
				printf("Erro de Sintaxe. <game>\n");
			}
		}
		else if (strcmp(cmd[0], "shutdown") == 0) {
			if (tamCMD == 1){
				free(v);
				free(mv);
				break;
			}
			else{
				printf("Erro de Sintaxe. <shutdown>\n");
			}
		}else{
            printf("Erro de Sintaxe.\n");
		}
	}
}
