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

void checkBitStream(char* data) {
	int i=0, count=0;
	for(; i<strlen(data); i++) {
		if(data[i] == '1')
			count++;
	}

	//printf("\nNo. of 1s in modified bit stream: %d\n", count);

	if(count%2 == 0) 
		printf("\nCORRECT\n");
	else
		printf("\nWRONG!!!\n");
}

 int
 main(int argc, char *argv[])
 {
     int sfd, cfd;
     struct sockaddr_un my_addr, peer_addr;
     socklen_t peer_addr_size;

     cfd = socket(AF_UNIX, SOCK_STREAM, 0);
     if (cfd == -1)
         handle_error("socket");

     //memset(&my_addr, 0, sizeof(struct sockaddr_un));
                         /* Clear structure */
     my_addr.sun_family = AF_UNIX;
     strncpy(my_addr.sun_path, MY_SOCK_PATH,
             sizeof(my_addr.sun_path) - 1);

     if (connect(cfd, (struct sockaddr *) &my_addr,
             sizeof(struct sockaddr_un)) == -1)
         handle_error("bind");


     /* Now we can accept incoming connections one
        at a time using accept(2) */

     peer_addr_size = sizeof(struct sockaddr_un);
     

     /* Code to deal with incoming connection(s)... */
	while(1) {
		printf("Enter a bit-stream: ");
	
		char data[DATASIZE];
		scanf("%s", data);
		
		if(strcmp(data, "exit")==0)
			break;

		write(cfd, (void*)data, strlen(data)+1);
		
		read(cfd, (void*)data, DATASIZE);

		checkBitStream(data);

		printf("\nRecieved data as a client: %s\n", data);
	}

}
     /* When no longer required, the socket pathname, MY_SOCK_PATH
        should be deleted using unlink(2) or remove(3) */

