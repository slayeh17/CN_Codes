#include<string.h>
#include<sys/ipc.h>
#include "msgq.h"
#include<stdio.h>
#include<sys/msg.h>

int decToBin(int num, char *result) {
	int k=0;
	while(num>0) {
		int rem = num & (2-1);
		result[k++] = 48+rem;
		num=num>>1;
	}
	result[k] = '\0';
	return k;
}

int decToOct(int num, char *result) {
	int k=0;
	while(num>0) {
		int rem = num & (8-1);
		result[k++] = 48+rem;
		num=num>>3;
	}
	result[k] = '\0';
	return k;
}

int decToHex(int num, char *result) {	
	int k=0;
	while(num>0) {
		int rem = num & (16-1);
		if(rem>10) {
			result[k++] = 55+rem;
		}
		else {
			result[k++] = 48+rem;
		}
		num=num>>4;
	}
		return k;
}

void display(char *result, int size) {
	int i = size-1;
	for(; i>=0; i--) {
		printf("%c", result[i]);
	}
	printf("\n");
}

int main() {
	MQ msg1, msg2, msg3;

	int num;
	printf("Enter the decimal number: ");
	scanf("%d", &num);
	
	
	char bin[1000];
	int binLen = decToBin(num, bin);
	printf("Binary: "); 
	display(bin, binLen);

	char octal[1000];
	int octLen = decToOct(num, octal);
	printf("Octal: ");
	display(octal, octLen);

	char hex[1000];
	int hexLen = decToHex(num, hex);
	printf("Hexa-Decimal: ");
	int i=hexLen-1;
	for(; i>=0; i--) {
		printf("%c", hex[i]);
	}
	printf("\n");

	int msgid = msgget(MQKEY, IPC_CREAT | 0666);


	msg1.type = 1;
 	strcpy(msg1.data, bin);	
	msgsnd(msgid, &msg1, DATASIZE, 0);

	msg2.type = 2;
	strcpy(msg2.data, octal);
	msgsnd(msgid, &msg2, DATASIZE, 0);

	msg3.type = 3;
	strcpy(msg3.data, hex);
	msgsnd(msgid, &msg3, DATASIZE, 0);

}

