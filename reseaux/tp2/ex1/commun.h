#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/shm.h>
#include <fcntl.h>
#include <sys/sem.h>

int const NB_EMPLOYE = 4;
#define NB_ZONE 10

struct str {
	char s[30];
	int nombre;
	struct var *next;
};

