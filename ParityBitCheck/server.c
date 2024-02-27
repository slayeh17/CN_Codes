#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MY_SOCK_PATH "./mysocket"
#define LISTEN_BACKLOG 50
#define DATASIZE 1000

#define handle_error(msg) \
     do { perror(msg); exit(EXIT_FAILURE); } while (0)

/* void reverse(char *data) {
	char rev[DATASIZE];
	int k=0;
	int i=strlen(data)-1;
	for(;i>=0; i--) 
		rev[k++] = data[i];

	rev[k++] = '\0';
	strcpy(data, rev);
} */

void addParity(char *data) {
	//EVEN PARITY
	int count=0; 
	int num = atoi(data);
	int len = strlen(data);
	int i=0;
	for(; i<len; i++) {
		if(data[i] == '1') 
			count++;
	}

	printf("\nNo. of 1s: %d\n", count);

	if(count % 2) {
		//NO. OF 1s IS ODD SO PARITY BIT = 1
		data[len] = '1';
		data[len+1] = 0;
		return;
	}
	data[len] = '0';
	data[len+1] = 0;
}

 int
 main(int argc, char *argv[])
 {
     unlink("./mysocket");
     int sfd, cfd;
     struct sockaddr_un my_addr, peer_addr;
     socklen_t peer_addr_size;

     sfd = socket(AF_UNIX, SOCK_STREAM, 0);
     if (sfd == -1)
         handle_error("socket");

     //memset(&my_addr, 0, sizeof(struct sockaddr_un));
                         /* Clear structure */
     my_addr.sun_family = AF_UNIX;
     strncpy(my_addr.sun_path, MY_SOCK_PATH,
             sizeof(my_addr.sun_path) - 1);

     if (bind(sfd, (struct sockaddr *) &my_addr,
             sizeof(struct sockaddr_un)) == -1)
         handle_error("bind");

     if (listen(sfd, LISTEN_BACKLOG) == -1)
         handle_error("listen");

     /* Now we can accept incoming connections one
        at a time using accept(2) */

     peer_addr_size = sizeof(struct sockaddr_un);
     
     // cfd is ts
     cfd = accept(sfd, (struct sockaddr *) &peer_addr,
                  &peer_addr_size);
     if (cfd == -1)
         handle_error("accept");

     /* Code to deal with incoming connection(s)... */
	while(1) {
		char data[DATASIZE];
		read(cfd, (void*)data, DATASIZE);
		
		if(strcmp(data, "exit") == 0)
			break;

		printf("\nRecieved data as a server: %s\n", data);

		//reverse(data);

		addParity(data);

		write(cfd, (void*)data, strlen(data)+2);
	}
	close(cfd);
     /* When no longer required, the socket pathname, MY_SOCK_PATH
        should be deleted using unlink(2) or remove(3) */
 }
