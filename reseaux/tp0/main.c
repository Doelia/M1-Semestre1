#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>

int* extract(int* T, int n, int a, int b) {

	int i = 0;
	int newSize = 0;
	for (i = 0; i < n; i++) {
		if (T[i] >= a && T[i] <= b) {
			newSize++;
		}
	}

	int* out = (int*) malloc(newSize*sizeof(int));
	int j = 0;
	for (i = 0; i < n; i++) {
		if (T[i] >= a && T[i] <= b) {
			out[j++] = T[i];
		}
	}

	return out;
}

int recSum(int*T, int size) {
	if (size <= 0) {
		return 0;
	}
	return T[size-1] + recSum(T, size-1);
}

void forkHeritage(int n) {
	int i =0;
	for (i=0; i < n; i++) {
		int idFils = 0;
		if ((idFils = fork()) == 0) { // Fils
			printf("Lancement proc fils...\n");
			sleep(2);
			printf("Fin proc fils...\n");
			break;
		} else {
			printf("Programme - Attente Processus %d\n", idFils);
			//wait(idFils);
		}
	}
}

void forkLineaire(int n) {
	int i =0;
	for (i=0; i < n; i++) {
		int idFils = 0;

		char string[] = "Hello";
		int fd[2];
		pipe(fd);

		if ((idFils = fork()) == 0) { // Fils
			printf("Lancement proc fils...\n");
			sleep(2);
			char readbuffer[80];
			read(fd[0], readbuffer, sizeof(readbuffer));
			printf("message = %s\n", readbuffer);
			printf("Fin proc fils...\n");
			close(fd[1]);
		} else {
			write(fd[1], string, strlen(string));
			close(fd[0]);
			printf("Programme - Attente Processus %d\n", idFils);
			wait(idFils);

			return;
		}
	}
}

void forkBinary(int n, char* string) {
	int i = 0;
	for (i=0; i < n; i++) {
		int idFils = 0;
		int fd[2];
		pipe(fd);
		int j;
		for (j=0; j < 2; j++) {
			if ((idFils = fork()) == 0) { // Fils
				printf("Lancement proc fils #%d \n", getpid());
				sleep(2);
				char readbuffer[80];
				read(fd[0], readbuffer, sizeof(string)+1);
				printf("Fils #%d terminé. Message reçu = %s\n", getpid(), readbuffer);
				break;
			} else if (j==1) {
				printf("Programme - Attente Processus %d\n", idFils);
				write(fd[1], string, strlen(string)+1);
				write(fd[1], string, strlen(string)+1);
				close(fd[0]);
				wait(idFils);
				return;
			}
		}
	}
}


int main() {

	printf("Hello\n");
	int tab[] = {10, 2, 2, 2, 4};
	/*
	int i =0;
	int* out = extract(tab, 5, 2, 4);
	for (i=0; i < 3; i++) {
		printf("%d ", out[i]);
	}*/

	/*
	printf("Somme = %d\n", recSum(tab, 5));
	*/

	//forkHeritage(10);
	//forkLineaire(3);

	char string[] = "Hello";
	forkBinary(10, string);
}

