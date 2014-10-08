#include "commun.h"

void main() {

	key_t key;
	struct sembuf op;

	if ((key = ftok("./zones", 10)) == -1) {
		perror("ftok");
		exit(1);
	}

	int semid = semget(key, NB_ZONE, IPC_CREAT | IPC_EXCL | 0666);
	if (semid < 0) {
		printf("La sémaphore existe déjà, on la récupère...\n");
		semid = semget(key, NB_ZONE, 0666);
	}
	printf("Initialisation de la sémaphore...\n");
	semctl(semid, 0, SETVAL, 0);
	semctl(semid, 1, SETVAL, 0);


	// Ouverture pour les employés
    op.sem_num = 0;
    op.sem_op = NB_EMPLOYE; 
    op.sem_flg = 0;
    semop(semid, &op, 1);
    printf("Employés prévenus !");

    printf("Attente des employés...\n");
    op.sem_num = 1;
    op.sem_op = - NB_EMPLOYE; 
    op.sem_flg = 0;
    semop(semid, &op, 1);
    printf("Tous les employés ont lu le message.\n");

}
