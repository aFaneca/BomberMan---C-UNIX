#include <pthread.h>
#include <stdio.h>
#include <unistd.h> //sleep
#include <string.h>
#include <ncurses.h>

#define N 2

int CONTINUAR = 1;

typedef struct {

	char letra;
	int intervalo;
	int coluna;
}

dados_thread;
dados_thread estruturas[N]={{'.',1,0},{'-',2,10}};

void * executa(void *p){
	
	int indice = (int)p;
	int pos_c=estruturas[indice].coluna, pos_l=0;

	while(CONTINUAR){
		//
		write(1,&estruturas[indice].letra,1);
		mvprintw(pos_l++,pos_c,"%c",estruturas[indice].letra);	
		refresh();	
		sleep(estruturas[indice].intervalo);
	}	
	return NULL;
}


int main(void){
	
	char str[100];
	pthread_t tid0, tid1;
	int pos_l=0, pos_c=20;
	int i=0;

	printf("Vou entrar em modo gráfico\n");
	sleep(1);
//-----------
	
	initscr();
	clear();
	noecho();

	if(pthread_create(&tid0,NULL,executa,(void *)i) != 0)
		perror("Erro de criação thread");
		i=1;
	
		if(pthread_create(&tid1,NULL,executa,(void *)i) != 0)
			perror("Erro de criação thread");
	
	do{	
	//printf("Frase:\n");
		
		mvprintw(pos_l++,pos_c, "Frase:");
		//fgets(str, 99, stdin);
		scanw("%[^\n]s",str);
		mvprintw(pos_l++,pos_c, "[%s]",str);
		refresh();
		
	}while(strncmp(str,"sair", 4));


	CONTINUAR = 0;
	pthread_join(tid0, NULL);
	pthread_join(tid1, NULL);
//----------
	
	endwin();
	printf("Adeus\n");
	
return 0;

}
