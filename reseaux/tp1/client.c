#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

struct my_msgbuf {
	long mtype;
	int op1;
	int op2;
};

int main() {
	printf("Client\n");

	struct my_msgbuf buf;
	int msqid;
	key_t key;

	if ((key = ftok("pipe", 10)) == -1) {
		perror("ftok");
		exit(1);
	}

	if ((msqid = msgget(key, 0644)) == -1) {
		perror("msgget");
		exit(1);
	}

	while(1) {
		printf("Recevoir : msgrcv()...\n");
		long etiquette = 2;
		if (msgrcv(msqid, &buf, sizeof(int)*2, etiquette, 0) == -1) {
			perror("msgrcv");
			exit(1);
		}
		int result = buf.op1 + buf.op2;
		printf("Message: \"%d\"\n", result);
	}

}
