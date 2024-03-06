#include <sys/socket.h>
#include <sys/un.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <unistd.h>

#define PORT 4567
#define IP_ADDR "127.0.0.1"

void stuffBit(char *bitStream) {
	int i, oneCount = 0, k = 0;
	char stuffedBits[100];
	for(i=0; i<strlen(bitStream); i++) {
		if(bitStream[i] == '1') {
			oneCount++;
			stuffedBits[k++] = bitStream[i];
		}
		else {
			oneCount = 0;
			stuffedBits[k++] = bitStream[i];
		}


		if(oneCount == 5) {
			stuffedBits[k++] = '0';
			oneCount = 0;
		}
		
	}
	stuffedBits[k] = '\0';
	strcpy(bitStream, stuffedBits);
}

int main() {
	int sfd, cfd;
	sfd = socket(AF_INET, SOCK_STREAM, 0);
	perror("socket");
	
	struct sockaddr_in saddr, caddr;
	saddr.sin_family = AF_INET;
	saddr.sin_addr.s_addr = INADDR_ANY;	
	saddr.sin_port = htons(PORT);

	bind(sfd, (struct sockaddr *)&saddr, sizeof(saddr));
	perror("bind");

	listen(sfd, 10);
	perror("listen");

	socklen_t caddr_size = sizeof(struct sockaddr_in);
	cfd = accept(sfd, (struct sockaddr *) &caddr, &caddr_size);
	perror("accept");

	while(1) {
		char bitStream[100];
		recv(cfd, bitStream, sizeof(bitStream), 0);
		
		if(strcmp(bitStream, "exit")==0)
			break;

		printf("Recieved Bit Stream: %s\n", bitStream);	
		stuffBit(bitStream);

		send(cfd, bitStream, strlen(bitStream)+1, 0);
	}
	close(cfd);
}
