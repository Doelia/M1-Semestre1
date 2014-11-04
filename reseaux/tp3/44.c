#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/types.h>

int tableau[4] = {0};
pthread_mutex_t verrou = PTHREAD_MUTEX_INITIALIZER; 
pthread_cond_t condi = PTHREAD_COND_INITIALIZER;

void* T1(){
	int i;

	for (i=0; i<4; i++){
		printf("Début de traitement de la zone %i par T1\n", i);
		sleep(1);
		pthread_mutex_lock(&verrou);
		tableau[i] = 1;
		pthread_mutex_unlock(&verrou);

		printf("Zone %d traitée par T1\n", i);
		pthread_cond_broadcast(&condi);
	}
	pthread_exit(NULL);
}

void* T2(){
	int j;

	for (j=0; j<4; j++){
		pthread_mutex_lock(&verrou);
		while(tableau[j] != 1) {
			pthread_cond_wait(&condi, &verrou);
		}
		pthread_mutex_unlock(&verrou);

		printf("Début de traitement de la zone %i par T2\n", j);
		sleep(3);
		pthread_mutex_lock(&verrou);
		tableau[j] = 2;
		pthread_mutex_unlock(&verrou);
		printf("Zone %d traitée par T2\n", j);
	}
	pthread_exit(NULL);
}

void main(){
	pthread_t id1;
	pthread_t id2;

	if (pthread_create(&id2, NULL, T2, NULL) != 0){
			perror("Erreur T1");
	}

	if (pthread_create(&id1, NULL, T1, NULL) != 0){
			perror("Erreur T1");
	}

	pthread_join(id2, NULL);
	pthread_join(id1, NULL);
}
