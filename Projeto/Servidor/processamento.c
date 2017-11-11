#include "header.h"

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
