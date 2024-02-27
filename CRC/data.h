#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/un.h>

typedef struct {
	char bits[1000];
	char divisor[1000];
} data_struct;

void crcDivision(char *bits, char *divisor, char *remainder) {
	long bitsLen = strlen(bits);
	long divLen = strlen(divisor);

	char paddedBits[1000], padding[100];
	strcpy(paddedBits, bits);
	int i=0;
	for(i=0; i<divLen-1; i++) {
		padding[i] = '0';
	}
	padding[i] = '\0';

	strcat(paddedBits, padding);

	for(int i=0; i<bitsLen; i++) {
		if(paddedBits[i] == '1') {
			for(int j=0; j<divLen; j++) 
				paddedBits[i+j] = paddedBits[i+j] == divisor[j] ? '0' : '1';
		}
	}

	strncpy(remainder, &paddedBits[bitsLen], divLen - 1);
	remainder[divLen - 1] = '\0';
}