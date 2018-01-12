#include "servidor.h"

unsigned int getPid(char *frase){
	int pid;
	char *palavra;
	strtok(frase, " ");
	palavra = strtok(NULL, " ");

	pid =  atoi(palavra);
	printf("%d", (pid_t)pid);
	return pid;
}

//---------VETOR-DINÂMICO-------//

int validaLogin(char user[], char pass[], char end[]){
	int total = contaPlayersRegistados();
	
	for(int i = 0; i < total; i++){
		if(!strcmp(user, v[i].username)){
			if(!strcmp(pass, v[i].password)){
				if(v[i].online == 0){
					v[i].online = 1;
					strcpy(v[i].nomeDoFicheiro, end);
					grava();
					strcpy(msg.resposta,"Credenciais validas.");
					return 1;
				}else{
					strcpy(msg.resposta,"User já se encontra a jogar");
					return 0;
				}
			}
			else
				strcpy(msg.resposta,"Credenciais invalidas.");
				return 0;
		}
	}
	strcpy(msg.resposta,"Credenciais invalidas.");
	return 0;
}

int usersOn() {

	int conta = contaPlayersRegistados();
	int k = 0;
	int on=0;
	
	printf("USERS ONLINE: \n");
	for (k = 0; k < conta; k++) {
		if(v[k].online){
			printf("%s\n", v[k].username);
			on++;
		}
	}
	return on;
}

void buscaLogs(char ficheiroLogin[]) {

	int k = 0;
	FILE *f = fopen(ficheiroLogin, "r");
	if (f == NULL) {
		printf( "Erro a abrir ficheiro.");
	}
	while (!feof(f)) {
		fscanf(f, "%s", v[k].username);
		fscanf(f, "%s", v[k].password);
		fscanf(f, "%d", &v[k].online);
		fscanf(f, "%d", &v[k].pontuacao);
		strcpy(v[k].nomeDoFicheiro, "");
		k++;
	}
	fclose(f);
}

jogador* add( char *cmd[], int *conta) {

	int i = 0;
	int flag = 0;

	for (i = 0; i < *conta; i++) {
		if (strcmp(cmd[1], v[i].username) == 0) {
			printf("Username existente!!\n");
			flag = 1;
		}
	}
	
	//printf("Pass:%s Tamanho: %d\n", cmd[2], strlen(cmd[2]));
	
	if (flag == 0) {
		*conta = *conta + 1;
		jogador *temp = realloc(v, sizeof(jogador)*(*conta));
		printf("Adicionado User No. %d --> %s\n", *conta, cmd[1]);
		strcpy(temp[*conta - 1].username, cmd[1]);
		strcpy(temp[*conta - 1].password, cmd[2]);
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

jogador* kick(char *cmd[], int conta){

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

jogador* updateSaida(char end[]){
	
	int i;
	int total = contaPlayersRegistados();
	printf("%d\n", total);
	
	for(i = 0; i < total; i++){
		if(strcmp(v[i].nomeDoFicheiro, end)==0){
			v[i].online = 0;
			printf("Confirmed");
			grava();
			return v;
		}
	}
	return v;
}

void gameInfo(labirinto *mv,int conta, int nMapas){

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


//-----------FICHEIRO-----------//

void grava(){
	
	int total = contaPlayersRegistados();
	remove("logs.txt");
	int i = 0;
	
	FILE *f = fopen("logs.txt", "w");
	
		for(i = 0; i < total; i++){ 
			fprintf(f, "%s\n", v[i].username);
			fprintf(f, "%s\n", v[i].password);
			fprintf(f, "%d\n", v[i].online);
			fprintf(f, "%d\n", v[i].pontuacao);
		}
	
	total = contaPlayersRegistados();
	fclose(f);
}

int contaPlayersRegistados() {

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


//---------------SINAIS-------------//

void sinalizaFim(){
	
	pid_t pid;
	int conta = contaPlayersRegistados();
	int k = 0;
	
	printf("AQUI");
	if (conta == 0) {
		printf("Nao existem Users a jogar\n");
	}
	
	for (k = 0; k < conta; k++) {
		if(v[k].online){
			pid = getPid(v[k].nomeDoFicheiro);
			kill(pid, SIGUSR1);
			v[k].online = 0;	
		}
	}
	printf("AQUI");
	grava();
}

void sinalizaKick(){
	pid_t pid;
	
	printf("\nClientes Ativos: \n");
	int conta = contaPlayersRegistados();
	int i = 0;

	
	if (conta == 0) {
		printf("Nao existem Users a jogar\n");
	}

	for (i = 0; i < conta; i++) {
		if(strcmp(msg.op1, v[i].username)==0){
			v[i].online = 0;
			pid = getPid(v[i].nomeDoFicheiro);
			kill(pid, SIGUSR2);
		}
	}
	grava();
}

void trata(int sinal){
	
	if(sinal == SIGUSR1){
		printf("AQUI");
		printf("A terminar o programa. A informar clientes ativos...\n");
		printf("\nAQUI2");
		
		if(usersOn() > 0){
			sinalizaFim();
		}
		free(v);
    	exit(0);	
	}
	
	if(sinal == SIGHUP || sinal == SIGINT){
		sinalizaFim();
		printf("Tentativa de forçar o fecho do terminal. A garantir uma saída segura...");
	    printf("[SERVIDOR] SERVIDOR DESLIGADO\n");
    	
		close(fd_servidor); 	// FECHAR "CP" DO SERVIDOR
    	unlink("CPservidor"); 	
	}
}


//---------PROCESSAMETO-DE-PEDIDOS---------//

void *processaPedidos(void *arg){
	
	while(1){
		
		n = read(fd_servidor, &msg, sizeof(msg)); /* RECEBER PEDIDO NA "CP" DO SERVIDOR - MINHA (n = read();) */	
			printf("----%s----", msg.op1);	
		
		if(n == -1)
				perror("\n[SERVIDOR] Erro a ler pedidos...\n");

		if(strcmp(msg.op1,"test")==0){
			strcpy(msg.resposta,"FUNCIONA\n");
			printf("[SERVIDOR] Teste funcionou [%s]\n", msg.endereco);
			
		}else if(strcmp(msg.op1,"sair")==0){
			strcpy(msg.resposta,"O Jogador abandonou o jogo.\n");
			
			v = updateSaida(msg.endereco);
			printf("[SERVIDOR] Servidor confirma que o jogador [%s] abandonou o jogo\n", msg.endereco);
			
			
		}else if(strcmp(msg.op1,"novo")==0){
			strcpy(msg.resposta,"Bem-vindo ao jogo.\n");
			printf("[SERVIDOR] [%s] entrou no jogo.\n", msg.endereco);
			
		}else if(strcmp(msg.op1,"login")==0){
			if(validaLogin(msg.op2, msg.op3, msg.endereco) == 1){
				printf("[SERVIDOR] Credenciais do cliente [%s] validadas com sucesso.\n", msg.endereco);

				strcpy(msg.op4, "s");
				
			}else{
				printf("[SERVIDOR] Credenciais do cliente %s invalidas.\n", msg.endereco);
				strcpy(msg.op4, "n");
			}
		}
			
		fd_cliente = open(msg.endereco, O_RDWR); 	// ABRIR "CP" DO CLIENTE (open - O_WRONLY)
		write(fd_cliente, &msg, sizeof(msg)); 		// ENVIAR RESPOSTA PARA A "CP" DO CLIENTE (write)
		close(fd_cliente); 							// FECHAR "CP" DO CLIENTE (close)
	}
}


//---------PROCESSAMETO-DE-COMANDOS---------//

char ** processaComando(char *comando, int *tamCMD) {

	char ** cmd = NULL;
	char *  p = strtok(comando, " ");
	int n_espacos = 0;
	
	while (p) { 	/* divide a string em palavras */
		cmd = realloc(cmd, sizeof(char*) * ++n_espacos);

		if (cmd == NULL)
			exit(-1); /* se alocação de memória falhar */

		cmd[n_espacos - 1] = p;
		p = strtok(NULL, " ");
	}
	
	*tamCMD = n_espacos;
	
	return cmd;
}


//------------MAPA------------------//

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

