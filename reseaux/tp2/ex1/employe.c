#include "commun.h"

void main() {

	printf("Je suis un employé\n");
	key_t key;
	struct str* v; 
	struct sembuf op;

	if ((key = ftok("./keyaa", 10)) == -1) {
		perror("ftok");
		exit(1);
	}

	int semid = semget(key, 2, IPC_CREAT | IPC_EXCL | 0666);

	int idSeg;
	if ((idSeg = shmget(key, 0, O_RDONLY)) == -1) {
		perror("shmget");
		exit(1);
	}

	if (semid < 0) {
		printf("La samaphore existe déjà. On la récupère\n");
		semid = semget(key, 2, 0666);
	} else {
		printf("La samaphore n'existait pas, initilisation à zéro...\n");
		semctl(semid, 0, SETVAL, 0);
		semctl(semid, 1, SETVAL, 0);
	}

	printf("Attente d'un message du chef...\n");
	op.sem_num = 0;
    op.sem_op = -1;
    op.sem_flg = 0;
    semop(semid, &op, 1);

    printf("Fin P()\n");

	v = (struct str *) shmat(idSeg, NULL, 0);
	printf("Message du chef reçu = %s\n", v->s);

	printf("On prévient le chef...\n");
	op.sem_num = 1;
    op.sem_op = 1; 
    op.sem_flg = 0;
    semop(semid, &op, 1);
    printf("Le chef a été prévenu.\n");

}

