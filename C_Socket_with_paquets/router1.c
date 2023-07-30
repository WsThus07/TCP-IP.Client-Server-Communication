#include <netinet/in.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include "crc.h"
#include "Encapsulation_Decapsulation.h"
#include "exception.h"
#define Packet_Size 97
#define PORTCLIENT 8091



/*table Port has three dimentions the first and the second for the routers and the third for the number of port between them*/

int Port[3]={8094,8092};
	     


// Function designed for chat between client and server.
void Server_Communication(int newsockfd,char *packet)
{
                int n;
	        char buffer[Packet_Size];
		n=read(newsockfd,buffer,Packet_Size);
		if(n<0){
		     error("Error on Reading");
		}
		printf("Client : %s\n",buffer);
		 
		decapsulation(newsockfd,buffer);
		//printf("\n ..packet Router 1 %s ",buff);
		
		strcpy(packet,buffer);
		bzero(buffer, Packet_Size);
	
}
void Client_Communication(int sockfd,char *buffer)
{	

		printf("Message received from client: %s \n",buffer);
                //encapsulation(sockfd,Data,trame,generator);
		write(sockfd, buffer, Packet_Size); 

}

// Driver function
int main()
{

 
    

////@Server_side

	int sockfd, connfd, len;
	char paquet[Packet_Size];
	struct sockaddr_in servaddr, cli;
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd == -1) {
		printf("socket creation failed...\n");
		exit(0);
	}
	printf("Socket created successfully ..\n");
	bzero(&servaddr, sizeof(servaddr));
	// assign IP, PORT as server side(receiver)
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(PORTCLIENT);
	if ((bind(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr))) != 0) {
		printf("Binding failed...\n");
		exit(0);
	}
        printf("Router 1 Binding successfully...\n");
	if ((listen(sockfd, 5)) != 0) {
		printf("Listen failed...\n");
		exit(0);
	}
	printf("Router 1 is Listening successfully...\n");
	len = sizeof(cli);
	connfd = accept(sockfd, (struct sockaddr*)&cli, &len);
	if (connfd < 0) {
		printf("server accept failed...\n");
		exit(0);
	}
	printf("Router 1 is Listening to Client...\n");

	Server_Communication(connfd,paquet);

	
	close(sockfd);

////@Client_side

        int sockfd2, connfd2;
	struct sockaddr_in servaddr2, cli2;

	// socket create and verification
	sockfd2 = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd2 == -1) {
		printf("socket creation failed...\n");
		exit(0);
	}
	else
		printf("Socket successfully created..\n");
	bzero(&servaddr2, sizeof(servaddr2));

	// assign IP, PORT
	servaddr2.sin_family = AF_INET;
	servaddr2.sin_addr.s_addr = inet_addr("127.0.0.1");
	servaddr2.sin_port = htons(Port[1]);


	// connect the client socket to server socket
	if (connect(sockfd2, (struct sockaddr*)&servaddr2, sizeof(servaddr2)) != 0) {
		printf("connection with the router failed...\n");
		exit(0);
	}
	else
		printf("connected to the router..\n");

	
	Client_Communication(sockfd2,paquet);

	// close the socket
	
	close(sockfd2);
}

