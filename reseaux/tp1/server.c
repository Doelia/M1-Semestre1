#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

struct my_msgbuf {
	long mtype;
	int op1;
	int op2;
};

int main(void)
{
	struct my_msgbuf buf;
	int msqid;
	key_t key;

	if ((key = ftok("pipe", 10)) == -1) {
		perror("ftok");
		exit(1);
	}

	if ((msqid = msgget(key, 0644 | IPC_CREAT)) == -1) {
		perror("msgget");
		exit(1);
	}
	
	buf.mtype = 2;
	buf.op1 = 3;
	buf.op2 = 4;

	if (msgsnd(msqid, &buf, sizeof(int)*2, 0) == -1)
		perror("msgsnd");

	printf("Message envoyé\n");
	return 0;
}

