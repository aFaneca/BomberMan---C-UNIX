#include "cliente.h"


void login(){
	
	char str[80], *palavra[TAM], user[50], pass[50];
	MENSAGEM msg;
	
	printf("[CLIENTE] Ligado ao servidor!\nUser: ");
    fgets(user, 50, stdin);
    user[strlen(user)-1]='\0';

    printf("Password: ");
    fgets(pass, 50, stdin);
    pass[strlen(pass)-1]='\0';

    strcpy(msg.op1, "login");
    strcpy(msg.op2, user);
    strcpy(msg.op3, pass);
	
	/* ENVIAR PEDIDO PARA "CP" DO SERVIDOR (write) */
    write(fd_servidor, &msg, sizeof(msg));
    /* ABRIR "CP" DO CLIENTE (open - O_RDONLY) */
    fd_cliente = open(msg.endereco, O_RDONLY);
    /* RECEBER RESPOSTA NA "CP" DO CLIENTE  (read) */
    read(fd_cliente, &msg, sizeof(msg));//ver recebimento.
    /* FECHAR "CP" DO CLIENTE - MINHA (close) */
    close(fd_cliente);
    //FAZER RECEBIMENTO - PERGUNTAR AO ZÉ A IMPLEMENTACAO
    printf("%s\n", msg.resposta);//ver recebimento
	
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