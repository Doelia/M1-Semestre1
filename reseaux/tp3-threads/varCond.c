#include <stdio.h>
#include <pthread.h>
#include <sys/types.h>
#include <stdlib.h>

pthread_cond_t condi = PTHREAD_COND_INITIALIZER;
pthread_mutex_t verrou = PTHREAD_MUTEX_INITIALIZER;

int i = 0;
int nbrOk = 0;
int tot = 3;

void* thread() {
	int iThread = ++i;
	printf("[thread %d] lock()\n", iThread);

	pthread_mutex_lock(&verrou);
	nbrOk++;
	printf("[thread %d] lancé\n", iThread);
	sleep(iThread-1);

	// On attends les autres
	pthread_cond_broadcast(&condi);
	while (nbrOk < tot) {
		printf("[thread %d] pthread_cond_wait()\n", iThread);
		pthread_cond_wait(&condi, &verrou); // unlock(), puis attends signal, puis lock()
	}
	pthread_mutex_unlock(&verrou);

	printf("RDV OK %d\n", iThread);

}

int main() {
	pthread_t id;
	pthread_create(&id, NULL, thread, NULL);
	pthread_create(&id, NULL, thread, NULL);
	pthread_create(&id, NULL, thread, NULL);
	sleep(20);
}

