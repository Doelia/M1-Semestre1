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
	int sem = semget(cle, ZONES, IPC_CREAT | 0666);
	if (sem == -1){
		perror("pb semget");
	}

	//récupération jeton
	struct sembuf sempar;
	//on initialise toutes les sem à 0
	int i;
	for (i=0; i<ZONES; i++){
		int ctrl = semctl(sem, i, SETVAL, 1);
		if (ctrl == -1){
			perror("pb semctl");
		}
	}
}
