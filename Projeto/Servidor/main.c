#include "header.h"
#define NMAXPLAY 20





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

		if (strncmp(cmd[0], "add", 3) == 0) {
			if (tamCMD == 3 || strlen(cmd[0]) != 4) {
				v = add(v, cmd, &total);
				users(v, total);

			}
			else {
				printf("Erro de Sintaxe. <add 'username' 'password'>\n");
			}
		}

		else if (strncmp(cmd[0], "users", 5) == 0) {
			if (tamCMD == 1 || strlen(cmd[0]) != 6)
				users(v, total);
			else
				printf("Erro de Sintaxe. <users>\n");
		}

		else if (strncmp(cmd[0], "kick", 4) == 0) {
			if (tamCMD != 2 || strlen(cmd[0]) != 5)
				printf("Erro de Sintaxe. kick <username>\n");
			else
				printf("User kickado: ...");
		}

		else if (strncmp(cmd[0], "map", 3) == 0) {
			if (tamCMD != 2 || strlen(cmd[0]) != 4)
				printf("Erro de Sintaxe. map <nome-ficheiro>\n");
			else
				printf("Mapa Carregado ...");
		}
		else if (strncmp(cmd[0], "game", 4) == 0) {
			if (tamCMD != 1 || strlen(cmd[0]) != 5)
				printf("Erro de Sintaxe. <game>\n");
			else
				printf("Game: ...");
		}
		else if (strncmp(cmd[0], "shutdown", 8) == 0) {
			if (tamCMD != 1 || strlen(cmd[0]) != 9)
				printf("Erro de Sintaxe. <shutdown>\n");
			else
				break;
		}
		else{
            printf("Erro de Sintaxe.\n");
		}
	}
}
