#include <stdio.h>
#include <unistd.h>
#include <sys/msg.h>
#include <sys/wait.h>

#define MQ_KEY		0x1234

typedef struct msg {
	long type;
	int data[2];
} msg_t;

int main() {
	int mqid, ret, s;

	// create message queue
	mqid = msgget(MQ_KEY, IPC_CREAT | 0600);
	if(mqid < 0) {
		perror("msgget() failed");
		_exit(1);
	}

	ret = fork();
	if(ret == 0) {
		// child: initialize and send the message
		msg_t m1;
		m1.type = 1;
		printf("sender: enter a numbers: ");
		scanf("%d%d",& m1.data[0],&m1.data[1]);
		ret = msgsnd(mqid, &m1, sizeof(m1.data), 0);
		printf("sender: message sent: %d\n", ret);
	}
	else {
		// parent: receive the message and print it
		msg_t m2;
		int sum;
		printf("receiver: waiting for the message...\n");
		ret = msgrcv(mqid, &m2, sizeof(m2.data), 1, 0);
		sum=(m2.data[0]+m2.data[1]);
		printf("sum of 2 numbers=%d\n",sum);
	//	printf("receiver: message received: %d --\n", ret);
	
		// wait for child and clean it up
		wait(&s);

		// destroy the message queue
		msgctl(mqid, IPC_RMID, NULL);
	}
	return 0;
}








