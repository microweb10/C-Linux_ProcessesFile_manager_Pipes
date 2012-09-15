#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

void alarma(){
	printf("El tiempo de ejecucion de la orden ha vencido.\n");
	exit(0);
}

void tiempo(){
	printf("Ejecucion de la orden satisfactoria.\n");
	exit(0);
}


int main(int argc,char *argv[]){
	pid_t pid;
	int i,estado,proceso;
	pid=fork();
	switch(pid){
	case -1: printf("Error en Fork\n");
		 exit(-1);
	break;
	case 0: execvp(argv[2],argv+2);
		exit(0);
	break; 
	default: signal(SIGALRM,alarma); // programa la captura de una senyal
		 signal(SIGCHLD,tiempo); // programa la captura de una senyal
		 alarm(atoi(argv[1]));
		 pause(); 
	}
return 0;
}


