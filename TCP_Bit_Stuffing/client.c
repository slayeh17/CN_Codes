#include <sys/socket.h>
#include <sys/un.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <netinet/in.h>
#include <netinet/ip.h>

#define PORT 4567
#define IP_ADDR "127.0.0.1"

void unstuffBits(char *bitStream) {
	int i, oneCount = 0, k = 0;
	char unstuffed[100];
	for(i=0; i<strlen(bitStream); i++) {
		if(bitStream[i] == '1') {
			oneCount++;
			unstuffed[k++] = bitStream[i];
		}
		else {
			oneCount = 0;
			unstuffed[k++] = bitStream[i];
		}


		if(oneCount == 5) {
			i++;
			oneCount = 0;
		}
		
	}
	unstuffed[k] = '\0';
	strcpy(bitStream, unstuffed);
}

int main() {
	int cfd;
	cfd = socket(AF_INET, SOCK_STREAM, 0);
	perror("socket");
		
	struct sockaddr_in caddr;
	caddr.sin_family = AF_INET;
	caddr.sin_addr.s_addr = INADDR_ANY;	
	caddr.sin_port = htons(PORT);

	connect(cfd, (struct sockaddr *)&caddr, sizeof(caddr));
	perror("connect");

	while(1) {
		char bitStream[1000], stuffed[1000];

		printf("Enter a bit stream: ");
		scanf("%s", bitStream);

		if(strcmp(bitStream, "exit")==0)
			break;

		send(cfd, bitStream, strlen(bitStream)+1, 0);

		recv(cfd, stuffed, sizeof(stuffed), 0);

		printf("Stuffed Bits Recieved: %s\n", stuffed);
		unstuffBits(stuffed);

		printf("Unstuffed Bits %s\n", stuffed);
	}
}
