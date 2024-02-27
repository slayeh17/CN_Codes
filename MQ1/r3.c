#include<stdio.h>
#include "msgq.h" 
#include<sys/ipc.h>
#include<sys/msg.h>

int main() {
	MQ msg;

	int msgid = msgget(MQKEY, IPC_CREAT | 0666);
	perror("msgget");
	
	msgrcv(msgid, &msg, DATASIZE, 3, 0);


	
	printf("HEXA-DECIMAL: ");

	int size=0;
	int i=0;
	
	while(msg.data[i]) {
		size++;
		i++;
	}

	for(; i>=0; i--) 
		printf("%c", msg.data[i]);

	printf("\n");
	
}
