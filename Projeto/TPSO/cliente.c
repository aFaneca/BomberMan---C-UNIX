#include "cliente.h"


int main(int argc, char *argv[]) {
	char **cmd;
	char *comando = NULL;
	comando = malloc(sizeof(char) * 20);
	int tamCMD = 0;
	printf("\n[CLIENTE] BEM-VINDO AO CLIENTE!\n");
	
	/* VERIFICAR SE EXISTE "CP" NO SERVIDOR(access) */
    if(access("CPservidor", F_OK)!=0){
        printf("[ERRO] O servidor nao esta em execucao!\n");
        exit(1);
    }
		

	
	sprintf(msg.endereco, "CPcliente %d", getpid()); /* CRIAR "CP" DO CLIENTE */
    mkfifo(msg.endereco, 0600); //0600 READ && WRITE
	fd_servidor = open("CPservidor", O_WRONLY); /* ABRIR "CP" DO SERVIDOR (open - O_WRONLY) */
	
	//login();
	strcpy(msg.op1, "novo");
	sprintf(msg.op2, "O Cliente %s acabou de se connectar", msg.endereco);
	write(fd_servidor, &msg, sizeof(msg));
	/* ABRIR "CP" DO CLIENTE (open - O_RDONLY) */
    fd_cliente = open(msg.endereco, O_RDONLY);
     /* RECEBER RESPOSTA NA "CP" DO CLIENTE (read) */
	read(fd_cliente, &msg, sizeof(msg));//ver recebimento.
    /* FECHAR "CP" DO CLIENTE - MINHA (close) */
    close(fd_cliente);
     //FAZER RECEBIMENTO - PERGUNTAR AO ZÉ A IMPLEMENTACAO
     printf("%s\n", msg.resposta);//ver recebimento
	while(login() != 1){}
	while(0 == 0){
		printf("\n> ");
		fgets(comando, 25, stdin);
		cmd = processaComando(comando, &tamCMD);
		if (strcmp(cmd[0], "test") ==0) {
			strcpy(msg.op1, cmd[0]);	
			/* ENVIAR PEDIDO PARA "CP" DO SERVIDOR (write) */
            write(fd_servidor, &msg, sizeof(msg));
			/* ABRIR "CP" DO CLIENTE (open - O_RDONLY) */
            fd_cliente = open(msg.endereco, O_RDONLY);
            /* RECEBER RESPOSTA NA "CP" DO CLIENTE (read) */
			read(fd_cliente, &msg, sizeof(msg));//ver recebimento.
            /* FECHAR "CP" DO CLIENTE - MINHA (close) */
            close(fd_cliente);
            //FAZER RECEBIMENTO - PERGUNTAR AO ZÉ A IMPLEMENTACAO
            printf("%s\n", msg.resposta);//ver recebimento
		}else if (strcmp(cmd[0], "sair") ==0) {
			strcpy(msg.op1, cmd[0]);	
			/* ENVIAR PEDIDO PARA "CP" DO SERVIDOR (write) */
            write(fd_servidor, &msg, sizeof(msg));
			/* ABRIR "CP" DO CLIENTE (open - O_RDONLY) */
            fd_cliente = open(msg.endereco, O_RDONLY);
            /* RECEBER RESPOSTA NA "CP" DO CLIENTE (read) */
			read(fd_cliente, &msg, sizeof(msg));//ver recebimento.
            /* FECHAR "CP" DO CLIENTE - MINHA (close) */
            close(fd_cliente);
            //FAZER RECEBIMENTO - PERGUNTAR AO ZÉ A IMPLEMENTACAO
			printf("[SERVIDOR] SERVIDOR DESLIGADO\n");
    	    /* REMOVER "CP" DO CLIENTE */
    		unlink(msg.endereco);
			exit(0);
		}
		
	}
}