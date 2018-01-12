#include "cliente.h"

void trata(int sinal){
	
	
	if(sinal == SIGUSR1){
		printf("O servidor foi encerrado. A terminar sessão... %d \n", sinal);
		unlink(msg.endereco); // REMOVER "CP" DO CLIENTE
    	exit(0);	
	}
	
	if(sinal == SIGUSR2){
		printf("Sessao Terminada. %d \n", sinal);
		unlink(msg.endereco); // REMOVER "CP" DO CLIENTE
    	exit(0);
	}
	
	if(sinal == SIGHUP || sinal == SIGINT){
		printf("Tentativa de forçar o fecho do terminal. A garantir uma saída segura...\n");
	    printf("[CLIENTE] CLIENTE DESLIGADO\n");
		strcpy(msg.op1, "sair");	
        write(fd_servidor, &msg, sizeof(msg)); 		// ENVIAR PEDIDO PARA "CP" DO SERVIDOR (write)
        fd_cliente = open(msg.endereco, O_RDONLY); 	// ABRIR "CP" DO CLIENTE (open - O_RDONLY)
		read(fd_cliente, &msg, sizeof(msg));		// RECEBER RESPOSTA NA "CP" DO CLIENTE (read)
        close(fd_cliente);							// FECHAR "CP" DO CLIENTE - MINHA (close)	
    	raise(SIGUSR2);		
    	unlink(msg.endereco); // REMOVER "CP" DO CLIENTE
    	exit(0);	
	}
}

int login(){
	
	char user[50], pass[50];
	
	printf("\nUser: ");
    fgets(user, 50, stdin);
    user[strlen(user)-1]='\0';

    printf("Password: ");
    fgets(pass, 50, stdin);
    pass[strlen(pass)-1]='\0';

    strcpy(msg.op1, "login");
    strcpy(msg.op2, user);
    strcpy(msg.op3, pass);
	
    write(fd_servidor, &msg, sizeof(msg)); 		// ENVIAR PEDIDO PARA "CP" DO SERVIDOR (write)
    fd_cliente = open(msg.endereco, O_RDONLY); 	// ABRIR "CP" DO CLIENTE (open - O_RDONLY)
	read(fd_cliente, &msg, sizeof(msg));		// RECEBER RESPOSTA NA "CP" DO CLIENTE (read)
    close(fd_cliente); 							// FECHAR "CP" DO CLIENTE - MINHA (close)
    printf("%s\n", msg.resposta);     			//FAZER RECEBIMENTO
	if(strcmp(msg.op4, "n") == 0)
		return 0;
	else
		return 1;
}

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