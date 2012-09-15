#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

int shmid;
int *variable=NULL;

void terminar(){
shmdt((char*)variable);  // desvinculamos la memoria compartida del proceso
shmctl(shmid,IPC_RMID,0);  //eliminamos el sector de memoria (lo borramos)
exit(0);
}

int main(int argc,char *argv[]){
	pid_t pid;
	shmid=shmget(IPC_PRIVATE,sizeof(int),IPC_CREAT|0666);  // Creamos el segmento de memoria compartida
	switch(fork()){
	case -1: printf("Error en Fork\n");
		 exit(-1);
	break;
	case 0: variable=(int*)shmat(shmid,0,0);  // vinculamos la memoria compartida al proceso
		*variable=atoi(argv[1]);
		while(*variable<=atoi(argv[4])){ // si la variable no ha llegado al maximo
			if(*variable+atoi(argv[3])<=atoi(argv[4])){
				*variable=*variable+atoi(argv[3]); // incremento hijo
				printf("Hijo (%d): variable=%d\n",getpid(),*variable);
			}
			if(*variable==atoi(argv[4])){
				shmdt((char*)variable);  // desvinculamos la memoria compartida del proceso
				exit(0);
			}
			else{
				sleep(1);
			}
		}
	break;
	default: variable=(int*)shmat(shmid,0,0);  // vinculamos la memoria compartida al proceso
		 while(*variable<=atoi(argv[4])){
		 	if(*variable+atoi(argv[2])<=atoi(argv[4])){
				*variable=*variable+atoi(argv[2]); // incremento padre
				printf("Padre (%d): variable=%d\n",getpid(),*variable);
			}
			signal(SIGCHLD,terminar);
			sleep(1);
		 }
	}
return 0;
}
