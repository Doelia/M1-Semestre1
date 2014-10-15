#include <stdio.h>
#include <pthread.h>
#include <sys/types.h>
#include <stdlib.h>

int nbThreadsOk = 0;
int nbrThreadsAAttendre = 3;
pthread_mutex_t verrou = PTHREAD_MUTEX_INITIALIZER;

void attendreToutLeMonde() {
	pthread_mutex_lock(&verrou);
	while (nbThreadsOk < nbrThreadsAAttendre) {
		pthread_mutex_unlock(&verrou);
		printf("boucle\n");
		pthread_mutex_lock(&verrou);
	}
	pthread_mutex_unlock(&verrou);
}

void* fct1() {
	pthread_mutex_lock(&verrou);
	printf("J'attends 3 secondes\n");
	sleep(3);
	printf("J'ai finis d'attendre 3 secondes. J'attends les autres.\n");
	pthread_mutex_unlock(&verrou);
	nbThreadsOk++;
	attendreToutLeMonde();
	printf("OK\n");
}

void* fct2() {
	pthread_mutex_lock(&verrou);
	printf("J'attends 5 secondes\n");
	sleep(5);
	printf("J'ai finis d'attendre 5 secondes. J'attends les autres.\n");
	pthread_mutex_unlock(&verrou);
	nbThreadsOk++;
	attendreToutLeMonde();
	printf("OK\n");
}

void* fct3() {
	pthread_mutex_lock(&verrou);
	printf("J'attends 10 secondes\n");
	sleep(10);
	printf("J'ai finis d'attendre 10 secondes. J'attends les autres.\n");
	pthread_mutex_unlock(&verrou);
	nbThreadsOk++;
	attendreToutLeMonde();
	printf("OK\n");
}

int main() {
	pthread_t idTh;
	pthread_create(&idTh, NULL, fct1, NULL);
	pthread_create(&idTh, NULL, fct2, NULL);
	pthread_create(&idTh, NULL, fct3, NULL);
	sleep(50);
	printf("end\n");
}

