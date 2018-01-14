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

void terminaJogo(){
	move(55,1);
	printw("Terminou o jogo. Cliquem em 'q' para sair.");
}


bool estaNaSaida(int x, int y){
	int colunas = sizeof(msg.lab.maze[0]) / sizeof(char);
	int linhas = sizeof(msg.lab.maze) / colunas;
	
	for(int i = 0; i < linhas * colunas; i++){
			int posx = msg.lab.elementos[i].x;
			int posy = msg.lab.elementos[i].y;
			char avatar = msg.lab.elementos[i].avatar;
			if(posx == x && posy == y && avatar == 'Z')
				return true;
	}
	
	return false;
}

void mostraLabirinto(){

	//erase();
	int colunas = sizeof(lab.maze[0]) / sizeof(char);
	int linhas = sizeof(lab.maze) / colunas;
	int nJogadores = sizeof(msg.lab.jogadores)/sizeof(msg.lab.jogadores[0]);
	//printf("\n%d %d", linhas, colunas);
	start_color();
	init_pair(1, COLOR_MAGENTA, COLOR_MAGENTA); // PAREDES
	init_pair(2, COLOR_BLACK, COLOR_WHITE); //NORMAL
	init_pair(3, COLOR_BLUE, COLOR_BLUE); // PAREDES DESTRUIVEIS
	init_pair(4, COLOR_RED, COLOR_RED); // SAIDA
	init_pair(5, COLOR_WHITE, COLOR_WHITE); // SAIDA ABERTA
	
	
	move(5,40);
	
	printw("OBJETOS APANHADOS: %d/%d", msg.lab.numObjetosPontos, msg.lab.totalObjetos);	
	move(6,40);
	printw("Bombinhas: %d", msg.lab.jogadores[0].bombinhas);
	move(7,40);
	printw("Megabombas: %d", msg.lab.jogadores[0].megabombas);
	//IMPRIME MUNDO
	for(int i = 0; i < linhas*colunas; i++){
		int posx = msg.lab.elementos[i].x;
		int posy = msg.lab.elementos[i].y;
		char avatar = msg.lab.elementos[i].avatar;
		if(avatar == '0'){
			attron(COLOR_PAIR(1));
			move(posy, posx);
			printw("%c", avatar);
			
			attroff(COLOR_PAIR(1));
		}else if(avatar == 'D'){
			attron(COLOR_PAIR(3));
			move(posy, posx);
			printw("%c", avatar);
			
			attroff(COLOR_PAIR(3));
		}else if(avatar == 'S'){
			attron(COLOR_PAIR(4));
			move(posy, posx);
			printw("%c", avatar);
			attroff(COLOR_PAIR(4));
		}else if(avatar == 'Z'){
			attron(COLOR_PAIR(5));
			move(posy, posx);
			printw("%c", avatar);
			
			attroff(COLOR_PAIR(5));
		}
		else{
			attron(COLOR_PAIR(2));
			//attron(COLOR_PAIR(1));
			move(posy, posx);
			printw("%c", avatar);
			//mvaddch(posy,posx,avatar);
			attroff(COLOR_PAIR(2));
		}
	}
	//IMPRIME JOGADORES NO MUNDO
	for(int i = 0; i < 1; i++){
		int posx = msg.lab.jogadores[i].x;
		int posy = msg.lab.jogadores[i].y;
		char avatar = msg.lab.jogadores[i].avatar;
		mvaddch(posy,posx,avatar);	
		if(estaNaSaida(posx, posy))
		   terminaJogo();
	}
	
	
	
}

bool validaMovimento (char mov){
	char str[2];
	str[0] = mov;
	str[1] = '\0';
	strcpy(msg.op1, "movimento"); 	
	strcpy(msg.op2, str);
    write(fd_servidor, &msg, sizeof(msg)); 		// ENVIAR PEDIDO PARA "CP" DO SERVIDOR (write) 	
    fd_cliente = open(msg.endereco, O_RDONLY); 	// ABRIR "CP" DO CLIENTE (open - O_RDONLY)
	read(fd_cliente, &msg, sizeof(msg));		// RECEBER RESPOSTA NA "CP" DO CLIENTE (read)
	close(fd_cliente);
	if(strcmp(msg.resposta, "s") == 0)
		return true;
	else
		return false;
    
}
bool posLivre(int x, int y){
	int colunas = sizeof(msg.lab.maze[0]) / sizeof(char);
	int linhas = sizeof(msg.lab.maze) / colunas;
	
	for(int i = 0; i < linhas * colunas; i++){
			int posx = msg.lab.elementos[i].x;
			int posy = msg.lab.elementos[i].y;
			char avatar = msg.lab.elementos[i].avatar;
			if(posx == x && posy == y && (avatar == '0' || avatar == 'S' || avatar == 'D'))
				return false;
	}
	
	return true;
	
}

void lancaBombinha(){
	int posx = msg.lab.jogadores[0].x;
	int posy = msg.lab.jogadores[0].y;
	int bX, bY;
	int movimento = msg.lab.jogadores[0].ultimoMovimento;
	bool podeLancar = false;
	
	if(movimento == 'w'){
		bX = posx; bY = posy - 1;
		if(posLivre(bX, bY))
		   podeLancar = true;
	}
	else if(movimento == 's'){
		bX = posx; bY = posy + 1;
		if(posLivre(bX, bY))
		   podeLancar = true;
	}
	else if(movimento == 'a'){
		bX = posx - 1; bY = posy;
		if(posLivre(bX, bY))
		  podeLancar = true;
	}
	else if(movimento == 'd'){
		bX = posx + 1; bY = posy;
		if(posLivre(bX, bY))
		   podeLancar = true;
	}
	
	if(podeLancar){
		int colunas = sizeof(msg.lab.maze[0]) / sizeof(char);
		int linhas = sizeof(msg.lab.maze) / colunas;
	
		for(int i = 0; i < linhas * colunas; i++){
			int posx1 = msg.lab.elementos[i].x;
			int posy1 = msg.lab.elementos[i].y;
			char avatar = msg.lab.elementos[i].avatar;
			if(posx1 == bX && posy1 == bY)
				msg.lab.elementos[i].avatar = 'b';
		}
	}
}

void iniciarJogo(){
	/*
	//ThrDados tdados[2];
    pthread_t jogo;
	//strcpy(tdados[0].qual, msg.endereco); 
	//tdados[0].fd = fd_cliente;
	
	if(pthread_create(&jogo, NULL, &jogadas, NULL) != 0)
			printf("Erro a criar a thread...");
	*/
	bool continuar = true;
	WINDOW * janela;
	fflush(stdout);
    msg.lab.numObjetosPontos = 0;
    /*  Initialize ncurses  */

    if ( (janela = initscr()) == NULL ) {
	fprintf(stderr, "Erro a inicializar o nCurses.\n");
	exit(EXIT_FAILURE);
    }
	noecho();
	clear();
	curs_set(0);
	move(1,1);
    /*  Display "Hello, world!" in the centre of the
	screen, call refresh() to show our changes, and
	sleep() for a few seconds to get the full screen effect  */
	while(continuar){
		clear();
		mostraLabirinto();
		refresh();
		while(1){
			
			char c = wgetch(janela);
			if(c == 'q'){continuar = false; break;}
			if(c == 'w'){
				if(validaMovimento('w')){
					msg.lab.jogadores[0].y--; 
					msg.lab.jogadores[0].ultimoMovimento = 'w';	
					break;
				}
			}
			if(c == 's'){
				if(validaMovimento('s')){
					msg.lab.jogadores[0].y++; 
					msg.lab.jogadores[0].ultimoMovimento = 's';	
					break;
				}
			}
			if(c == 'a'){
				if(validaMovimento('a')){
					msg.lab.jogadores[0].x--;
					msg.lab.jogadores[0].ultimoMovimento = 'a';	
					break;
				}
			}
			if(c == 'd'){
				if(validaMovimento('d')){
					msg.lab.jogadores[0].x++;
					msg.lab.jogadores[0].ultimoMovimento = 'd';	
					break;
				}
			}
			if(c == 'b'){
				if(validaMovimento('b')){
					//msg.lab.jogadores[0].x++;
					lancaBombinha();
					break;
				}
			}
		}
	}


    /*  Clean up after ourselves  */

    delwin(janela);
    endwin();
    refresh();
}
