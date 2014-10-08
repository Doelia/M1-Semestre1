#include "commun.h"

void main() {

	key_t key;
	struct str* v; 
	struct sembuf op;

	if ((key = ftok("./keyaa", 10)) == -1) {
		perror("ftok");
		exit(1);
	}

	int idSeg;
	if ((idSeg = shmget(key, (size_t) 8*30, IPC_CREAT | 0666)) == -1) {
		perror("shmget");
		exit(1);
	}


	int semid = semget(key, 2, IPC_CREAT | IPC_EXCL | 0666);
	if (semid < 0) {
		printf("La sémaphore existe déjà, on la récupère...\n");
		semid = semget(key, 2, 0666);
	}
	printf("Initialisation de la sémaphore...\n");
	semctl(semid, 0, SETVAL, 0);
	semctl(semid, 1, SETVAL, 0);


    // Ecriture d'un message
    v = (struct str *) shmat(idSeg, NULL, 0);
	v->s[0] = 's';
	v->s[1] = 'a';
	v->s[2] = 'l';
	v->s[3] = 'u';
	v->s[4] = 't';
	v->s[5] = '\0';
	printf("Message écrit : %s\n", v->s);

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
