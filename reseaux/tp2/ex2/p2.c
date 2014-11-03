#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <fcntl.h>
#include <sys/shm.h>// pour le SHM_RDONLY

#include <sys/sem.h>//pour les sémaphores
#define ZONES 5

void main(){
	key_t cle = ftok("./test2",10);
	if (cle == -1){
		perror("problème ftok");
	}
	//sémaphore création
	int sem = semget(cle, ZONES, 0666);
	if (sem == -1){
		perror("pb semget");
	}
	int i;
	struct sembuf sempar;
	for(i=0; i<ZONES; i++){
		printf("Zone %d\n", i);
		sempar.sem_num = i ;
		sempar.sem_op = -2 ; //on prend un jeton
		sempar.sem_flg = 0 ;
		semop(sem,&sempar,1);
		sleep(1);//traitement
		sempar.sem_op = 3; // pcq p2 demande 2 jetons
		semop(sem, &sempar, 1);
	}
}
