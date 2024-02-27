#include "data.h"

#define SOCKET_PATH "./mysocket"
#define L_BACKLOG 10

int main() {
	unlink(SOCKET_PATH);

	int sfd, cfd;
	struct sockaddr_un saddr, caddr;
	socklen_t caddr_size;

	sfd = socket(AF_UNIX, SOCK_STREAM, 0);
	perror("socket");

	saddr.sun_family = AF_UNIX;
	strncpy(saddr.sun_path, SOCKET_PATH, sizeof(saddr.sun_path));
	bind(sfd, (struct sockaddr*) &saddr, sizeof(saddr));
	perror("bind");

	listen(sfd, L_BACKLOG);
	perror("listen");
	
	caddr_size = sizeof(caddr);
	cfd = accept(sfd, (struct sockaddr*) &caddr, &caddr_size);
	perror("accept");

	while(1) {
		
		data_struct msg;

		recv(cfd, &msg, sizeof(msg), 0);

		printf("bits: %s\n", msg.bits);
		printf("divisor: %s\n", msg.divisor);
		
		char remainder[1000];

		crcDivision(msg.bits, msg.divisor, remainder);
		printf("remainder: %s\n", remainder);

		char total_bits[1000];
		strcpy(total_bits, msg.bits);
		strcat(total_bits, remainder);

		printf("Sending... %s\n", total_bits);
		send(cfd, total_bits, strlen(total_bits)+1, 0);
		
		// break;
	}

	close(cfd);
}
