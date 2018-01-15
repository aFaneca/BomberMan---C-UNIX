#include "servidor.h"
#define NMAXPLAY 20

int main(int argc, char *argv[]) {
	char **cmd;
	char *comando = NULL;
	comando = malloc(sizeof(char) * 20);
	char *comandoCopia = NULL;
	comandoCopia = malloc(sizeof(char) * 20);
	int tamCMD = 0;
	char ficheiroLogin[100];
	ThrDados tdados[2];
	pthread_t tpipea;
	

	if(argc != 2){	
		printf("\n[SERVIDOR] Nr. incompleto de argumentos.\n");
		exit(1);
	}
	
	signal(SIGUSR1, trata);
	signal(SIGHUP, trata);
	signal(SIGINT, trata);
	
	strcpy(ficheiroLogin,argv[1]);

	int total = contaPlayersRegistados();
	v = malloc(sizeof(jogador)*total);
	buscaLogs(ficheiroLogin);
	
	
	/* VERIFICAR SE EXISTE "CP" DO SERVIDOR -- APENAS UM!!!*/
    if(access("CPservidor", F_OK)==0){
        printf("[SERVIDOR] Ja existe um servidor!\n");
        exit(1);
    }

	if(mkfifo("CPservidor", 0600) < 0){ // CRIAR "CP" DO SERVIDOR
		perror("[SERVIDOR] Erro na criação do FIFO...");
		exit(1);
	}
	
    fd_servidor = open("CPservidor", O_RDWR);  /* ABRIR "CP" DO SERVIDOR - MINHA (open - O_RDONLY) */
    printf("[SERVIDOR] Servidor Iniciado!\n");
	
	strcpy(tdados[0].qual, msg.endereco); 
	tdados[0].fd = fd_cliente;
	
	if(pthread_create(& tpipea, NULL, &processaPedidos, tdados) != 0)
			printf("Erro a criar a thread...");
		   
	
	while (0 == 0) {
		
        printf("> ");
		fgets(comandoCopia, 25, stdin);
		int i = 0;
		
		for(i = 0; i < strlen(comandoCopia) - 1; i++){
			comando[i] = comandoCopia[i];
		}
			
			comando[strlen(comandoCopia)-1] = '\0';
		
			cmd = processaComando(comando, &tamCMD);

		
		if (strcmp(cmd[0], "add") ==0) {
			if (tamCMD == 3) {
				v = add(cmd, &total);
			}
			else {
				printf("Erro de Sintaxe. <add 'username' 'password'>\n");
			}
		}
		else if (strcmp(cmd[0], "users") == 0) {
			if (tamCMD == 1){
				usersOn();
			}else{
				printf("Erro de Sintaxe. <users>\n");
			}
		}
		else if (strcmp(cmd[0], "kick") == 0) {
			if (tamCMD == 2){
				v = kick(cmd, total);
				strcpy(msg.op1, cmd[1]);
				
				sinalizaKick();
				
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
				//gameInfo(mv, total, nMapas);
			}else{
				printf("Erro de Sintaxe. <game>\n");
			}
		}
		else if (strcmp(cmd[0], "shutdown") == 0) {
			if (tamCMD == 1){
				//free(mv);
				
				printf("[SERVIDOR] SERVIDOR DESLIGADO\n");
    			close(fd_servidor); 	// FECHAR "CP" DO SERVIDOR
    			unlink("CPservidor"); 	// REMOVER "CP" DO SERVIDOR
				raise(SIGUSR1);
			}
			else{
				printf("Erro de Sintaxe. <shutdown>\n");
			}
		}else{
            printf("Erro de Sintaxe.\n");
		}
		
		comando[0] = '\0';
		comandoCopia[0] = '\0';
	}
}