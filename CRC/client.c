#include "data.h"

#define SOCKET_PATH "./mysocket"

int main() {

	int cfd;
	struct sockaddr_un saddr, caddr;

	cfd = socket(AF_UNIX, SOCK_STREAM, 0);
	perror("socket");

	caddr.sun_family = AF_UNIX;
	strncpy(caddr.sun_path, SOCKET_PATH, sizeof(caddr.sun_path));
	connect(cfd, (struct sockaddr*) &caddr, sizeof(caddr));
	perror("connect");

	while(1) {

		data_struct msg;
		printf("Enter message bits: ");
		scanf("%s", msg.bits);
		printf("Enter polynomial coeff (divisor): ");
		scanf("%s", msg.divisor);

		// strcpy(msg.bits, "1010101010");
		// strcpy(msg.divisor, "11001");

		send(cfd, &msg, sizeof(msg), 0);

		char total_bits[1000], remainder[1000];;

		recv(cfd, total_bits, sizeof(total_bits), 0);

		crcDivision(total_bits, msg.divisor, remainder);

		puts(remainder);

		for(int i=0; i<strlen(remainder); i++) {
			if(remainder[i] != '0' ) {
				printf("\nERROR IN MESSAGE!!!\n");
				exit(1);
			}
		}
		printf("remainder is %s\nALL CORRECT\n", remainder);

	}
	
}
