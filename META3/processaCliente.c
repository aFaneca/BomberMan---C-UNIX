#include "cliente.h"

void trata(int sinal){
	
	
	if(sinal == SIGUSR1){
		printf("O servidor foi encerrado. A terminar sessão... \n");
		unlink(msg.endereco); // REMOVER "CP" DO CLIENTE
    	exit(0);	
	}
	
	if(sinal == SIGUSR2){
		printf("Sessao Terminada. \n");
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
void mostraLabirinto(){
	erase();
	int colunas = sizeof(lab.maze[0]) / sizeof(char);
	int linhas = sizeof(lab.maze) / colunas;
	int nJogadores = sizeof(msg.lab.jogadores)/sizeof(msg.lab.jogadores[0]);
	printf("\n%d %d", linhas, colunas);
	
	//IMPRIME MUNDO
	for(int i = 0; i < linhas*colunas; i++){
		int posx = msg.lab.elementos[i].x;
		int posy = msg.lab.elementos[i].y;
		char avatar = msg.lab.elementos[i].avatar;
		mvaddch(posy,posx,avatar);	
	}
	
	//IMPRIME JOGADORES NO MUNDO
	for(int i = 0; i < nJogadores; i++){
		int posx = msg.lab.jogadores[i].x;
		int posy = msg.lab.jogadores[i].y;
		char avatar = msg.lab.jogadores[i].avatar;
		mvaddch(posy,posx,avatar);	
	}
	
	
}
	
void iniciarJogo(){
	
    bool fim = false;
	//clear();
	
    //cbreak();
    
    
	//keypad(janela1, TRUE);
	//nodelay(janela1, TRUE);
    //scrollok(janela1, TRUE);
	char c;
	int x,y;
    /*  Initialize ncurses  */
/*	
    if ( (initscr()) == NULL ) {
		fprintf(stderr, "Erro a inicializar nCurses...\n");
	exit(EXIT_FAILURE);
    }

	while(!fim){
		werase(janela1);
		mostraLabirinto();
		refresh();
		if(c == 27){
			fim = true;
		}

  */      
    initscr();
	//keypad(stdscr, TRUE);
	noecho();
	mostraLabirinto();
	refresh();
	
		
        
 /*
 	    case KEY_RIGHT:
        {
            x++;
            move(y,x);
        }
        case KEY_LEFT:
        {
            x--;
            move(y,x);
        }
        case KEY_UP:
        {
            y--;
            move(y,x);
        }
        case KEY_DOWN:
        {
            y++;
            move(y,x);
        }
        case KEY_EXIT:
        {
            printf("Bye");
			fim = true;
        }
        default:
        {
            printw("%c",c);
        }
*/
    
   			 
	//}
	
	
	
    /*  Display "Hello, world!" in the centre of the
	screen, call refresh() to show our changes, and
	sleep() for a few seconds to get the full screen effect  */
	

    
   // sleep(10);
	
	// LIMPEZA
	//delwin();
	//endwin();
    
	
}
