#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <fcntl.h>
#include <string.h>

/*
void itoa(int num,char *proceso){
	int i,tam=1,aux;
	aux=num;
	while(aux/10>0){
	tam++;
	aux=aux/10;
	}
	char res[tam];
	for(i=tam-1;i>=0;i--)
		res[i]=((char)(num%10))+48;
	printf("%s",res);
	strcpy(proceso,res);
}*/


int main(int argc,char *argv[]){
	pid_t pid;
	int i,archivo,nuevo,leido,escrito,estado;
	int tuberia[2];
	char texto[32],mensaje1[]="Hijo con PID ",mensaje2[]=". Archivo ",mensaje3[]=" creado correctamente\n";
	//char *proceso;
	pipe(tuberia);
	for(i=0;i<argc-2;i++){
		switch(fork()){
		case -1: //printf("Error en Fork\n");
			 exit(-1);
		break;
		case 0: nuevo=creat(argv[i+2],7777);
			do{
				leido=read(tuberia[0],texto,32);
				if(leido!=32) texto[leido+1]=0;
				escrito=write(nuevo,texto,strlen(texto)-1);
			}while(leido==32);
			close(nuevo);
			//itoa(3521,proceso);
			write(1,mensaje1,strlen(mensaje1));
			//write(1,proceso,4);
			write(1,mensaje2,strlen(mensaje2));
			write(1,argv[i+2],strlen(argv[i+2]));
			write(1,mensaje3,strlen(mensaje3));
			sleep(2);
			exit(0);
		break;
		default: archivo=open(argv[1],O_RDONLY);
			 do{
				leido=read(archivo,texto,32);
				if(leido!=32) texto[leido+1]=0;
				escrito=write(tuberia[1],texto,strlen(texto)-1);
			}while(leido==32);
			close(archivo);
		}
	}
	for(i=0;i<argc-2;i++){
		wait(&estado);
	}
return 0;
}


