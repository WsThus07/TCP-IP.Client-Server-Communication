#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include <stdbool.h>
#include "crc.h"
#include "Encapsulation_Decapsulation.h"
#include "exception.h"
#define portNumS  8080






//Decapsulation

int main()
{
 
  int sockfd,newsockfd,portNum,n;
   char buffer[80];
  struct sockaddr_in serv_addr, cli_addr;
  socklen_t clilen;
  
   sockfd=socket(AF_INET,SOCK_STREAM,0);
  if(sockfd<0){
      error("ERROR opening socket");
  }
  else{
    printf("Server created successfully...\n");
  }
  bzero((char*) &serv_addr, sizeof(serv_addr));
  
  
   serv_addr.sin_family=AF_INET;
   serv_addr.sin_addr.s_addr=htonl(INADDR_ANY);
   serv_addr.sin_port=htons(portNumS);
  
  if(bind(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr))<0)
  {
  error("Binding Failed..\n");
  }
  else{
  printf("Server Binding successfully...\n");
  }
  
  listen(sockfd,5);
  clilen=sizeof(cli_addr);
  
  newsockfd=accept(sockfd,(struct sockaddr*) &cli_addr,&clilen);
  if(newsockfd<0){
  error("Error on Accept");
  }else{
  
  printf("Server is Listening successfully...\n");}
  
  
  int i;
  
  //char trame_recu[80], trameD[50], data[20];
  char paquet[97];
  //data_CRC[0] = '\0';
  
  bzero(buffer,sizeof(buffer));
        
  bzero(paquet,97);
  n=read(newsockfd,paquet,97);
  if(n<0){
     error("Error on Reading");
  }
  printf("Client : %s\n",paquet);
  
  decapsulation(newsockfd,paquet);
  
  close(newsockfd);
  close(sockfd);
   
  
  return 0;
  }
  
  
  
 
