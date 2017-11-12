#include "header.h"

char ** processaComando(char *comando, int *tamCMD) {

	char ** cmd = NULL;
	char *  p = strtok(comando, " ");
	int n_espacos = 0;
	int i = 0;


	while (p) { 	/* divide a string em palavras */
		cmd = realloc(cmd, sizeof(char*) * ++n_espacos);

		if (cmd == NULL)
			exit(-1); /* se alocação de memória falhar */

		cmd[n_espacos - 1] = p;
		p = strtok(NULL, " ");
	}

	// Está feio?! Está lindo porque funciona!!! <3

	char lastWord[25];
	char lastWord2[25];
	strcpy(lastWord, cmd[n_espacos -1]);

	for(i=0;i < strlen(lastWord) - 1; i++){
		lastWord2[i] = lastWord[i];
	}
	strcpy(cmd[n_espacos - 1], lastWord2);
	*tamCMD = n_espacos;

	return cmd;
}

void buscaLogs(jogador *v) {

	int k = 0;
	FILE *f = fopen("logs.txt", "r");
	if (f == NULL) {
		printf( "Erro a abrir ficheiro2.");
	}
	while (!feof(f)) {
		fscanf(f, "%s", v[k].username);
		fscanf(f, "%s", v[k].password);
		fscanf(f, "%d", &v[k].online);
		fscanf(f, "%d", &v[k].pontuacao);
		k++;
	}
	fclose(f);
}

int contaPlayers() {

	int conta = 0;
	char linha[256];
	FILE *f = fopen("logs.txt", "r");
	if (f == NULL) {
		printf("Erro a abrir ficheiro dos logs");
		return 1;
	}
	while (fgets(linha, sizeof(linha), f) != NULL) {
		conta++;
	}

	conta = conta / 4;

	fclose(f);
	return conta;
}

void users(jogador *v, int conta) {

	int k = 0;
	if (conta == 0) {
		printf("Nao existem Users a jogar\n");
	}
	printf("USERS ONLINE: \n");
	for (k = 0; k < conta; k++) {
		if(v[k].online){
			printf("%s\n", v[k].username);
		}
	}
}

jogador* add(jogador* v, char *cmd[], int *conta) {

	int i = 0;
	int flag = 0;
	char lastWord[25];

	for (i = 0; i < *conta; i++) {
		if (strcmp(cmd[1], v[i].username) == 0) {
			printf("Username existente!!\n");
			flag = 1;
		}
	}

	strcpy(lastWord, cmd[2]);

	if (flag == 0) {
		*conta = *conta + 1;
		jogador *temp = realloc(v, sizeof(jogador)*(*conta));
		printf("Adicionado User No. %d --> %s\n", *conta, cmd[1]);
		strcpy(temp[*conta - 1].username, cmd[1]);
		strcpy(temp[*conta - 1].password, lastWord);
		temp[*conta-1].online = 0;
		temp[*conta-1].pontuacao = 0;

		remove("logs.txt");

		FILE * f = fopen("logs.txt", "w");
		for(i = 0; i < *conta ; i++){
			fprintf(f, "%s\n", temp[i].username);
			fprintf(f, "%s\n", temp[i].password);
			fprintf(f, "%d\n", temp[i].online);
			fprintf(f, "%d\n", temp[i].pontuacao);
		}

		fclose(f);
		return temp;
	}
	else {
		return v;
	}
	return v;
}

jogador* kick(jogador* v, char *cmd[], int conta){

	int i = 0;

	for(i = 0; i < conta ; i++){
		if(strcmp(cmd[1], v[i].username)==0 && v[i].online == 1){
			v[i].online = 0;
			printf("%s --> Foi Kickado.\n" , v[i].username);
			return v;
		}

		if(strcmp(cmd[1], v[i].username) == 0 && v[i].online == 0){
			printf("%s --> O utilizador a kickar está offline\n", v[i].username);
			return v;
			}
		}

	printf("Não existe nenhum user com o nome de %s\n", cmd[1]);
	return v;
}

void gameInfo(jogador *v, labirinto *mv,int conta, int nMapas){

	int i = 0;
	printf("-----------GAMEINFO-----------\n");
	printf("OBJETOS POR APANHAR: %d\n", mv[nMapas - 1].numObjetosPontos);
	for(i = 0; i < conta ; i++){
		if(v[i].online == 1){
			printf("USER:  %-15s", v[i].username);
			printf("SCORE: %d\n", v[i].pontuacao);
		}
	}

}

void buscaMapInfo(labirinto *mv, int nMapas){

	int i = 0;
	int k = 0;
	int pos = (nMapas - 1);
	char c;
	FILE *f = fopen("mapa1.txt", "r");

	if(f == NULL){
		printf("Erro a abrir ficheiro");
	}

	while((c = getc(f)) != EOF){
		if(k == 30 && i == 19){
			break;
		}
		
		if(k == 30){
			i++;
			k=0;
		}
		
		if(c != '\n'){
			mv[0].maze[i][k] = c;
			k++;
		}
		
		if(c == 'P'){
			mv[pos].numObjetosPontos++;
		}
		if(c == 'D'){
			mv[pos].numObjetosDest++;
		}
	}
	fclose(f);
}
