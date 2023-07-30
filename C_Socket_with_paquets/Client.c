#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include <arpa/inet.h>
#include<netdb.h>
#include <stdbool.h>
#include "crc.h"
#include "Encapsulation_Decapsulation.h"
#include "exception.h"
#define MAX_BUFFER 80
#define portNumC 8091
//8091

char generator[]="1011";



int main()
{
  int sockfd,n;
  struct sockaddr_in serv_addr;
  struct hostent *server;
  char buffer[MAX_BUFFER];
  sockfd =socket(AF_INET,SOCK_STREAM,0);
  if(sockfd<0)
     error("ERROR opening socket"); 
  printf("Socket created successfully...\n");   
  bzero((char *) &serv_addr,sizeof(serv_addr));
  serv_addr.sin_family=AF_INET;
  serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
  serv_addr.sin_port=htons(portNumC);
  if(connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr))<0)
  {
      error("Connecting Failed...");
  }
   printf("Client is connecting...\n");
    int i;
    char trame[MAX_BUFFER];
    char paquet[97];
    bzero(buffer,sizeof(buffer));
    bzero(trame,sizeof(trame));
    bzero(paquet,sizeof(paquet));
    
    char Data[17]; 
    printf("Enter a Data: ");
    scanf("%s",Data);
    //Data[strcspn(Data, "\n")] = '\0';
    printf("Data : %s",Data);
    
    printf("---------------------------------\n");
    
    char IPsource[9]; 
    printf("Enter a IPsource of Client: ");
    scanf("%s",IPsource); 
    //IPsource[strcspn(IPsource, "\n")] = '\0';
    printf("@Ip Source : %s",IPsource);
    
    printf("---------------------------------\n");  
     
    char IPdest[9]; 
    printf("Enter a IPdest of Client: ");
    scanf("%s",IPdest); 
    //IPdest[strcspn(IPdest, "\n")] = '\0';  
    printf("@Ip Destination : %s",IPdest);
    
    printf("---------------------------------\n");  
    
    encapsulation(sockfd,Data,trame,paquet,IPsource,IPdest,generator);
    
    char buf[255];   
    bzero(buf,255);
    n=read(sockfd,buf,255);
    if(n<0) 
       error("ERROR reading from socket");
    printf("---------------------------------\n");   
    printf("Server : %s\n",buf);
    close(sockfd);
  return 0;
  
  }
  
    
/*
    strcat(trame, Delimiteur);
    strcat(trame, Adresse_Source);
    strcat(trame, Adresse_Destinateur);
   
 

 Trame = Size 80 bits = 16 bits x 5 champs
 (1 octets = 8bits)
 
 champs 1: Delimiteur de trame (16 bits) 
 champs 2: Adresse source (16 bits) 
 champs 3: Adresse destination (16 bits) 
 champs 4: Données (16 bits) 
 champs 5: CRC (3 bits) */
 
  

